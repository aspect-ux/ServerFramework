#ifndef __ASPECT_SINGLETON_H__
#define __ASPECT_SINGLETON_H__

#include <memory>

namespace aspect {

	/**
	* �������������ռ䣬�;�̬��������һ�����������ڣ�ֱ�������������
	* ���Һ�һ�������ռ�һ������ֻ��ͨ����ǰԴ�ļ���������ռ�
	* �ô��ǵ�ͬ��������̬����
	* ---------------PAY ATTENTION!!!----------------------
	* 1.ͬһ�ļ���������������������ͬ�ļ���������������Ա���ֿ���һ������Ϊ�ڲ�ͬ���ÿռ䣻
		������ͬ�ļ���ͬ������������������Ա������
	* 2.��������Ա���ܺ�ȫ�ֱ���ͬ���������������
	* 3.����Ƕ�ף�����ͨһ����
	* ---------------PAY ATTENTION!!!----------------------
	*/
	namespace {

		template<class T,class X,int N>
		T& GetInstanceX() {
			static T v;
			return v;
		}

		template<class T, class X, int N>
		std::shared_ptr<T> GetInstancePtr()
		{
			static std::shared_ptr<T> v(new T);
			return v;
		}

	}

	template<class T, class X = void, int N = 0>
	class Singleton {
	public:
		/**
		 * @brief ���ص�����ָ��
		 */
		static T* GetInstance() {
			static T v;
			return &v;
			//return &GetInstanceX<T, X, N>();
		}
	};

	/**
	 * @brief ����ģʽ����ָ���װ��
	 * @details T ����
	 *          X Ϊ�˴�����ʵ����Ӧ��Tag
	 *          N ͬһ��Tag������ʵ������
	 */
	template<class T, class X = void, int N = 0>
	class SingletonPtr {
	public:
		/**
		 * @brief ���ص�������ָ��
		 */
		static std::shared_ptr<T> GetInstance() {
			static std::shared_ptr<T> v(new T);
			return v;
			//return GetInstancePtr<T, X, N>();
		}
	};
}
#endif // !__SINGLETON_H__
