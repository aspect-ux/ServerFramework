/*
* @file fiber.hpp
* @brief Э�̷�װ
*/
#ifndef __ASPECT_FIBER_H__
#define __ASPECT_FIBER_H__

#include <memory>
#include <functional>
#include <coroutine.h>

namespace aspect
{
    /**
 * @brief Э����
 */
    class Fiber : public std::enable_shared_from_this<Fiber> {
        friend class Scheduler;
    public:
        typedef std::shared_ptr<Fiber> ptr;

        /**
         * @brief Э��״̬
         */
        enum State {
            /// ��ʼ��״̬
            INIT,
            /// ��ͣ״̬
            HOLD,
            /// ִ����״̬
            EXEC,
            /// ����״̬
            TERM,
            /// ��ִ��״̬
            READY,
            /// �쳣״̬
            EXCEPT
        };
    private:
        /**
         * @brief �޲ι��캯��
         * @attention ÿ���̵߳�һ��Э�̵Ĺ���
         */
        Fiber();

    public:
        /**
         * @brief ���캯��
         * @param[in] cb Э��ִ�еĺ���
         * @param[in] stacksize Э��ջ��С
         * @param[in] use_caller �Ƿ���MainFiber�ϵ���
         */
        Fiber(std::function<void()> cb, size_t stacksize = 0, bool use_caller = false);

        /**
         * @brief ��������
         */
        ~Fiber();

        /**
         * @brief ����Э��ִ�к���,������״̬
         * @pre getState() Ϊ INIT, TERM, EXCEPT
         * @post getState() = INIT
         */
        void reset(std::function<void()> cb);

        /**
         * @brief ����ǰЭ���л�������״̬
         * @pre getState() != EXEC
         * @post getState() = EXEC
         */
        void swapIn();

        /**
         * @brief ����ǰЭ���л�����̨
         */
        void swapOut();

        /**
         * @brief ����ǰ�߳��л���ִ��״̬
         * @pre ִ�е�Ϊ��ǰ�̵߳���Э��
         */
        void call();

        /**
         * @brief ����ǰ�߳��л�����̨
         * @pre ִ�е�Ϊ��Э��
         * @post ���ص��̵߳���Э��
         */
        void back();

        /**
         * @brief ����Э��id
         */
        uint64_t getId() const { return m_id; }

        /**
         * @brief ����Э��״̬
         */
        State getState() const { return m_state; }
    public:

        /**
         * @brief ���õ�ǰ�̵߳�����Э��
         * @param[in] f ����Э��
         */
        static void SetThis(Fiber* f);

        /**
         * @brief ���ص�ǰ���ڵ�Э��
         */
        static Fiber::ptr GetThis();

        /**
         * @brief ����ǰЭ���л�����̨,������ΪREADY״̬
         * @post getState() = READY
         */
        static void YieldToReady();

        /**
         * @brief ����ǰЭ���л�����̨,������ΪHOLD״̬
         * @post getState() = HOLD
         */
        static void YieldToHold();

        /**
         * @brief ���ص�ǰЭ�̵�������
         */
        static uint64_t TotalFibers();

        /**
         * @brief Э��ִ�к���
         * @post ִ����ɷ��ص��߳���Э��
         */
        static void MainFunc();

        /**
         * @brief Э��ִ�к���
         * @post ִ����ɷ��ص��̵߳���Э��
         */
        static void CallerMainFunc();

        /**
         * @brief ��ȡ��ǰЭ�̵�id
         */
        static uint64_t GetFiberId();
    private:
        /// Э��id
        uint64_t m_id = 0;
        /// Э������ջ��С
        uint32_t m_stacksize = 0;
        /// Э��״̬
        State m_state = INIT;
        /// Э��������
        ucontext_t m_ctx;
        /// Э������ջָ��
        void* m_stack = nullptr;
        /// Э�����к���
        std::function<void()> m_cb;
    };
}

#endif // !__ASPECT_FIBER_H__
