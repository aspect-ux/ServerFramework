#ifndef __THREAD_H__
#define __THREAD_H__

#include <string>

namespace aspect{

class Thread {
public:
    /**
     * @brief 构造函数
     * @param[in] cb 线程执行函数
     * @param[in] name 线程名称
     */
    Thread(/*std::function<void()> cb,*/ const std::string& name = "thread_name");

    /**
     * @brief 析构函数
     */
    ~Thread();

    /**
     * @brief 获取当前的线程名称
     */
    static const std::string& GetName();
private:

    std::string m_name; //线程名字
};

}
#endif // !__THREAD_H__