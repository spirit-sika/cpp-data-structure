//
// Created by 22355 on 24-6-2.
//

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <stdexcept>
namespace GuoWenxuan {
    class Person {
        int age;
        double height;

    public:
        Person() {
        }

        explicit Person(int age, double height): age(age), height(height) {
        }

        int getAge() {
            return age;
        }

        [[nodiscard]] int get_age() const {
            return age;
        }

        void set_age(const int age) {
            this->age = age;
        }

        [[nodiscard]] double getHeight() const {
            return height;
        }

        void set_height(const double height) {
            this->height = height;
        }

        Person operator+(const Person &person) const {
            Person temp;
            temp.age = this->age + person.age;
            return temp;
        }

        Person operator+(const int some) const {
            Person temp;
            temp.age = this->age + some;
            return temp;
        }
    };

    class Student {
        std::string name;
        int age;
    public:
        Student(std::string name, int age):name(name),age(age) {}
        // 根据n的值拿到名字字符串中的第n个字符， 从0开始
        char operator[](int pos) {
            if (pos < 0) {
                throw std::out_of_range("pos can not be negative");
            }
            if (pos >= this->name.size()) {
                throw std::invalid_argument("invalid_argument");
            }
            return this->name.at(pos);
        }
    };
};

std::ostream &operator<<(std::ostream &cout, GuoWenxuan::Person &person) {
    cout << "age is: " << person.getAge() << std::endl;
    cout << "height is: " << person.getHeight() << std::endl;
    return cout;
}

#endif //PERSON_H
