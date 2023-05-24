#ifndef __ASPECT_SINGLETON_H__
#define __ASPECT_SINGLETON_H__

#include <memory>

namespace aspect {

	/**
	* 无命名的命名空间，和静态变量具有一样的声明周期，直至程序结束销毁
	* 并且和一般命名空间一样，都只能通过当前源文件访问这个空间
	* 好处是等同于声明静态变量
	* ---------------PAY ATTENTION!!!----------------------
	* 1.同一文件可以有两个无命名，不同文件的两个无命名成员名字可以一样，因为在不同作用空间；
		但是相同文件不同无命名不能有重名成员！！！
	* 2.无命名成员不能和全局变量同名，会产生二义性
	* 3.可以嵌套（和普通一样）
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
		 * @brief 返回单例裸指针
		 */
		static T* GetInstance() {
			static T v;
			return &v;
			//return &GetInstanceX<T, X, N>();
		}
	};

	/**
	 * @brief 单例模式智能指针封装类
	 * @details T 类型
	 *          X 为了创造多个实例对应的Tag
	 *          N 同一个Tag创造多个实例索引
	 */
	template<class T, class X = void, int N = 0>
	class SingletonPtr {
	public:
		/**
		 * @brief 返回单例智能指针
		 */
		static std::shared_ptr<T> GetInstance() {
			static std::shared_ptr<T> v(new T);
			return v;
			//return GetInstancePtr<T, X, N>();
		}
	};
}
#endif // !__SINGLETON_H__
