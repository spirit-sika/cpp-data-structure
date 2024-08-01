//
// Created by 22355 on 24-6-2.
//

#ifndef INTEGERARRAY_H
#define INTEGERARRAY_H
#include <stdexcept>
#include <string>
#include<iostream>

namespace Sika {
    class IntegerArray {
        int *_array;
        int _size;
        // 让类外的函数能够访问私有成员
        friend std::ostream &operator<<(std::ostream &print, const IntegerArray &ia);

    public:
        /*-------------------- 构造 --------------------*/
        IntegerArray() {
            this->_size = 0;
            this->_array = new int[0];
        }

        explicit IntegerArray(const int size) {
            this->_size = size;
            this->_array = new int[this->_size];
            for (int i = 0; i < this->_size; i++) {
                this->_array[i] = 0;
            }
        }

        IntegerArray(const int size, const int defaultValue) {
            this->_size = size;
            this->_array = new int[size];
            for (int i = 0; i < this->_size; i++) {
                this->_array[i] = defaultValue;
            }
        }

        ~IntegerArray() {
            delete[] _array;
        }

        /*------------------- 必须重写拷贝构造函数, 让后置自增的效果正常 -------------------*/
        IntegerArray(const IntegerArray& integer_array) {
            this->_size = integer_array._size;
            this->_array = new int[_size];
            for (int i = 0; i < this->_size; i++) {
                this->_array[i] = integer_array[i];
            }
        }

        /*------------------- 属性方法 -------------------*/
        [[nodiscard]] int size() const {
            return this->_size;
        }

        /*------------------- 运算符重载 -------------------*/
        int operator[](const int index) const {
            if (index < 0) {
                throw std::invalid_argument("索引不能为负数");
            }
            if (index >= this->_size) {
                throw std::out_of_range("index out of range _array");
            }
            return this->_array[index];
        }

        void operator+(const int num) const {
            for (int i = 0; i < _size; ++i) {
                this->_array[i] += num;
            }
        }

        /*------------------- 前置自增运算符重载 -------------------*/
        // 如果不返回引用而是返回值, 多次++操作的不是同一个对象 ++(++ia)操作的是两个对象
        IntegerArray& operator++(){
            for (int i = 0; i < _size; i++) {
                _array[i]++;
            }
            return *this;
        }
        /*------------------- 后置自增运算符重载 使用int参数占位 -------------------*/
        // 后置自增不能返回引用, 在函数结束后对象会被销毁, 如果返回引用后续的操作是对一个被销毁的对象操作导致错误
        IntegerArray operator++(int) const {
            const IntegerArray temp = *this;

            for (int i = 0; i < _size; i++) {
                _array[i]++;
            }

            return temp;
        }

        IntegerArray& operator--() {
            for (int i = 0; i < _size; i++) {
                _array[i]--;
            }
            return *this;
        }

        IntegerArray operator--(int) const {
            const IntegerArray temp = *this;
            for (int i = 0; i < _size; i++) {
                _array[i]--;
            }
            return temp;
        }

    };

    /*------------------- ostream输出对象需要类外实现, 并且不能是成员函数 -------------------*/\
    inline std::ostream &operator<<(std::ostream &print, const IntegerArray &ia) {
        std::string target = "[";

        for (int i = 0; i < ia.size(); ++i) {
            target.append(std::to_string(ia._array[i]) + ", ");
        }

        if (const auto lastComma = target.find_last_of(", "); lastComma == target.size() - 1) {
            // target.pop_back();
            // target.pop_back();
            target = target.substr(0, lastComma-1);
        }

        target.append("]");
        print << target;
        return print;
    }

} // Sika

#endif //INTEGERARRAY_H
