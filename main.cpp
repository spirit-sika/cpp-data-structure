#include "SikaSinglyLinkedList.h"
#include "SikaStack.h"
#include "SikaQueue.h"
#include <iostream>
#include "PointerAndReference.hpp"
#include <vector>

#include "SikaQueue.h"

void testSikaSinglyLinkedList() {
    Sika::SikaSinglyLinkedList<int> intList;

    intList.tail_insert(10);
    intList.tail_insert(20);
    intList.tail_insert(30);
    intList.tail_insert(40);
    intList.tail_insert(50);

    const int data = intList.get_data(3);
    std::cout << data << std::endl;

    std::cout << intList << std::endl;
}

void testSikaStack() {
    Sika::SikaDynamicStack<int> stack;
    stack.push(3);
    stack.push(2);
    stack.push(1);

    std::cout << "stack = " << stack << std::endl;

    const int peek = stack.peek();
    std::cout << "peek result is: " << peek << std::endl;

    const int pop_result = stack.pop();
    std::cout << "pop_result is: " << pop_result << std::endl;

    stack.push(4);
    std::cout << "stack = " << stack << std::endl;

    if (stack.isEmpty()) {
        std::cout << "stack is empty!" << std::endl;
    }
    else {
        std::cout << "stack is not empty!" << std::endl;
    }

    stack.pop();
    stack.pop();
    stack.pop();

    if (stack.isEmpty()) {
        std::cout << "stack is empty!" << std::endl;
    }
    else {
        std::cout << "stack is not empty!" << std::endl;
    }
}

void todoTestSikaQueue() {
    Sika::SikaQueue<int> queue;

    queue.push(1);
    queue.push(2);
    queue.push(3);

    // todo 死循环
    std::cout << "queue = " << queue << std::endl;

    std::cout << "queue.peek() is " << queue.peek() << std::endl;
    std::cout << "queue.pull() is " << queue.pull() << std::endl;
    std::cout << "queue.size() is " << queue.size() << std::endl;

    std::cout << "queue = " << queue << std::endl;
}

//template<typename T>
template<class T>
class LinkedNode {
    T data;
    LinkedNode* next;
public:
    LinkedNode():data(T()), next(nullptr) {}
    // 初始化列表, data
    explicit LinkedNode(const T data):data(data), next(nullptr) {}

    LinkedNode(const T data,const  LinkedNode* next):data(data), next(next) {}

    [[nodiscard]] T get_data() const {
        return data;
    }

    void set_data(const T &data) {
        this->data = data;
    }

    [[nodiscard]] LinkedNode * get_next() const {
        return next;
    }

    void set_next(LinkedNode * const next) {
        this->next = next;
    }
};

/*/**
 * 链表节点
 #1#
namespace Sika {
    /*
     * 节点类型
     #1#
    class LinkedNode {
    // 对象所属的属性私有化, 再提供setter/getter
    private:
        int data;
        LinkedNode* next;
    public:
        // get: 拿到
        int getData(){
            return this->data;
        }
        LinkedNode* getNext() {
            return this->next;
        }
        // set: 设置
        void setData(int data) {
            this->data = data;
        }
        void setNext(LinkedNode* node) {
            this->next = node;
        }

        /* 构造函数 #1#
        // 空参构造
        LinkedNode():data(0), next(nullptr) {}
        // 全参构造
        LinkedNode(int data, LinkedNode* next):data(data), next(next) {}
        // 创建一个带数据, 没有下一个节点的节点
        explicit LinkedNode(const int data):data(data), next(nullptr) {}
        // 创建一个无数据, 但是有下一个节点的节点
        explicit LinkedNode(LinkedNode* next):data(0), next(next){}

        /* 析构函数 #1#
        ~LinkedNode() = default;
    };

    class LinkedList {
    private:
        // 头节点
        LinkedNode* HEAD;

        /**
         * 构造函数的目的就是初始话对象中的属性
         #1#
    public:
        LinkedList():HEAD(new LinkedNode()) {}

        explicit LinkedList(LinkedNode* next) {
            HEAD = new LinkedNode();
            HEAD->setNext(next);
        }

        ~LinkedList() {
            /* 先备份节点,再切换下一个节点到下下个节点 #1#
            LinkedNode* temp = HEAD;
            while (temp->getNext() != nullptr) {
                /*
                 * 先保存一份下一个节点的备份,
                 * 当前节点等于下一个节点的下一个节点,
                 * 释放下一个节点的内存
                 #1#
                auto nextNode = temp->getNext();
                temp->setNext(temp->getNext()->getNext());
                delete nextNode;
            }
        }

        void head_insert(const int data) const {
            const auto node = new LinkedNode(data);
            node->setNext(HEAD->getNext());
            HEAD->setNext(node);
        }

        void tail_insert(const int data) const {
            /* 创建一个头节点的备份, 将该备份遍历到最后一个节点(下一个节点为空则到链表末尾) #1#
            auto node = HEAD;
            while (node->getNext()!=nullptr) {
                node = node->getNext();
            }
            node->setNext(new LinkedNode(data));
        }

        int delete_by_index(const int index) {}

        int delete_by_data(const int data) {}

        bool update_by_index(int index, int newData) {}

        /**
         * 根据数据修改, 只修改第一个符合条件的节点,
         * 不保证整个中符合的节点都被修改
         * @param data
         * @param newData
         * @return
         #1#
        bool update_by_data(int data, int newData) {}

        /**
         *
         * @param data 数据内容
         * @return 返回查找到的第一个节点的索引
         #1#
        int search_by_data(int data) {}

        /**
         * 根据索引位置进行查找, 索引不符合链表抛出异常
         * @param index 节点索引
         * @return 返回查找到的元素内容
         * @throw 输入的索引为负数, 超过链表长度
         #1#
        int search_by_index(int index) {}

        int size() {}
        int length() {}


    };
    std::ostream& operator<<(std::ostream& out, LinkedList& list) {

    }
}*/



int main() {

    int a = 10, b = 20;
    int& ref1 = a;
    int& ref2 = b;

    int& rref1 = ref1;
    int& rref2 = ref2;

    swap(rref1, rref2);
    std::cout << "a = " << a << ", b = " << b << std::endl;

    func<int>();

    std::vector<int> v;

    return 0;
}

// list (head=[0, e],e=[5,d], d=[4, a], a=[1, b], b=[2, c], c=[3, nullptr])

/*
 * 插入
 * 删除
 * 修改
 * 查看
 *
 * 插入: 头插   尾插  中间插入
 * 删除: 根据位置删除(返回值), 根据值删除(返回索引)
 * 修改: 根据位置将节点的data修改
 * 查看: 根据位置查找节点(给出的是节点的值T)    打印整个链表
 * 获取链表大小: size()    length()
 */
