//
// Created by 22355 on 24-7-11.
//
#pragma once
#include <functional>
inline void swapP(int* value1, int* value2) {
    const int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

inline void swapR(int& value1, int& value2) noexcept {
    const int temp = value1;
    value1 = value2;
    value2 = temp;
}

template<typename T>
void swap(T& t1, T& t2) noexcept {
    T temp = t1;
    t1 = t2;
    t2 = temp;
}

template<typename T>
void func() {
    std::cout << "模板函数内部" << std::endl;
}


class Person {
public:
    std::string name;
    int age;
    void setName(std::string name) {
        this->name = name;
    }
    std::string getName() {
        return this->name;
    }
    void setAge(int age) {
        this->age = age;
    }
    int getAge() {
        return this->age;
    }
};

template<class T>
bool compare(T& t1, T& t2) {
    return t1 == t2;
}

template<> bool compare(Person& t1, Person& t2) {
    return t1.getName() == t2.getName() && t1.getAge() == t2.getAge();
}


template<class T, class E, class Y>
class People {
public:
    T name;
    E age;
    Y ano;

    People(T name, E age):name(name), age(age), ano(Y()) {}
};





