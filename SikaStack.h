//
// Created by 22355 on 24-6-2.
//

#ifndef SIKASTACK_H
#define SIKASTACK_H
#include <stdexcept>
#ifdef __INCLUDE_LEVEL__
#pragma message("Including SikaStack.h at level " STR(__INCLUDE_LEVEL__))
#elif
#pragma message("Including SikaStack.h at level ")
#endif

namespace Sika {
    /**
     * 线性表节点类型, 具有下一节点的指针和数据域
     * @tparam T 节点数据类型
     */
    template<class T>
    class SikaNode {
    private:
        T data;
        SikaNode *next;
    public:
        SikaNode(): data(T()), next(nullptr) {
        }

        explicit SikaNode(const T &data): data(data), next(nullptr) {
        }

        SikaNode(const T data, SikaNode *next): data(data), next(next) {
        }

        SikaNode *getNextNode() {
            return next;
        }

        void setNextNode(SikaNode *nextNode) {
            next = nextNode;
        }

        T getData() {
            return data;
        }

        void setData(T newData) {
            data = newData;
        }
    };

    /**
     * 动态栈, 使用链表的方式进行实现, 动态存储, 不需要做数组迁移
     * 需要属性: size, top, buttom, HEAD
     *
     * 初始化时给定一个头节点, 无任何数据类型, 压栈时链表头插, 栈顶指针根据新节点移动
     *
     * 析构时, 根据头节点便利整个链表进行内存释放
     *  栈空时, 压栈栈底指针指向当前节点
     *  栈中有内容时, 栈底指针不变
     *
     * pop, peek都根据栈顶指针搜索节点,
     *  pop时更新栈顶指针状态, 如果只有一个栈帧进行pop, 栈顶和栈底指针置为nullptr
     *      如果有多个元素时, 栈顶指针移动到下一节点, 栈底不变
     *      释放相应节点内存
     *  pop, push时更新栈的size
     * @tparam T 栈帧数据类型
     */
    template<class T>
    class SikaDynamicStack final {
        int _size;
        SikaNode<T> *HEAD;
        // 栈顶指针
        SikaNode<T> *top;
        // 栈底指针
        SikaNode<T> *bottom;

        template<class E>
        friend std::ostream& operator<<(std::ostream& print, SikaDynamicStack<E>& stack);

    public:
        SikaDynamicStack(): _size(0), HEAD(new SikaNode<T>()), top(nullptr), bottom(nullptr) {
        }

        // todo 根据列表或者数组转为栈, 根据数据直接构建一个单栈帧的栈

        ~SikaDynamicStack() {
            this->_size = 0;
            // 析构时, 根据头节点遍历整个链表进行内存释放
            while (HEAD->getNextNode() != nullptr) {
                auto needFree = HEAD->getNextNode();
                HEAD->setNextNode(HEAD->getNextNode()->getNextNode());
                delete needFree;
            }
        }

        void push(T data) {
            auto nodeHasData = new SikaNode<T>(data);
            // 压栈时链表头插, 栈顶指针根据新节点移动
            if (_size == 0) {
                top = nodeHasData;
                bottom = nodeHasData;
                _size++;
            }
            else {
                auto oldNext = HEAD->getNextNode();
                auto newNext = new SikaNode<T>(data, oldNext);
                top = newNext;
                _size++;
            }
            HEAD->setNextNode(top);
        }

        T pop() {
            if (_size <= 0) {
                throw std::length_error("当前栈中无内容");
            }
            auto data = top->getData();
            // pop时更新栈顶指针状态, 如果只有一个栈帧进行pop, 栈顶和栈底指针置为nullptr
            if (_size == 1) {
                top = nullptr;
                bottom = nullptr;
            }
            else {
                top = top->getNextNode();
            }
            HEAD->setNextNode(top);
            _size--;
            return data;
        }

        T peek() {
            return top->getData();
        }

        [[nodiscard]] int size() const {
            return _size;
        }

        [[nodiscard]] bool isEmpty() const {
            return _size == 0;
        }

    };

    template<class T>
    std::ostream& operator<<(std::ostream& print, SikaDynamicStack<T>& stack) {
        std::string builder = "[";
        auto node = stack.HEAD->getNextNode();

        while (node != nullptr) {
            builder.append(std::to_string(node->getData()) + ", ");
            node = node->getNextNode();
        }

        const unsigned int lastComma = builder.find_last_of(", ");
        if (lastComma == builder.size() - 1) {
            builder = builder.substr(0, lastComma - 1);
        }

        builder.append("]");

        print << builder;
        return print;
    }

    template<class T>
    class StaticStack {
    private:
        T arr[];
        int _index = 0;
        int _size = 0;
        int _max = 100;
    public:
        StaticStack() { arr = new T[_max]; };
        /**
         * 将数据推入到数组的末尾
         * @param value 数据
         */
        void push(T value) {

        }

        /**
         * 删除数组头部元素内容并返回
         * @return 数据
         */
        T pop() {

        }

        int size() {}

        /**
         * 返回栈顶元素的内容但不删除
         * @return 栈顶元素内容
         */
        T peek() {}

        /**
         * 判断栈是否为空
         * @return 返回true当栈为空时
         */
        bool isEmpty() {}

    };
} // Sika

#endif //SIKASTACK_H
