#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__
/**
* @file noncopyable.hpp
* @brief 不可复制对象封装
*/
class Noncopyable {
	/**
	* @brief 默认构造函数
	*/
	Noncopyable() = default; //c++11 自动生成默认定义

    /**
     * @brief 默认析构函数
     */
    ~Noncopyable() = default;

    /**
     * @brief 拷贝构造函数(禁用)
     */
    Noncopyable(const Noncopyable&) = delete; // c++11 禁止掉类自带的拷贝构造

    /**
     * @brief 赋值函数(禁用)
     */
    Noncopyable& operator=(const Noncopyable&) = delete; //禁止掉自带的赋值

};
#endif // !__NONCOPYABLE_H__
