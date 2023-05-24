#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__
/**
* @file noncopyable.hpp
* @brief ���ɸ��ƶ����װ
*/
class Noncopyable {
	/**
	* @brief Ĭ�Ϲ��캯��
	*/
	Noncopyable() = default; //c++11 �Զ�����Ĭ�϶���

    /**
     * @brief Ĭ����������
     */
    ~Noncopyable() = default;

    /**
     * @brief �������캯��(����)
     */
    Noncopyable(const Noncopyable&) = delete; // c++11 ��ֹ�����Դ��Ŀ�������

    /**
     * @brief ��ֵ����(����)
     */
    Noncopyable& operator=(const Noncopyable&) = delete; //��ֹ���Դ��ĸ�ֵ

};
#endif // !__NONCOPYABLE_H__
