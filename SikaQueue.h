//
// Created by 22355 on 24-6-5.
//
#ifndef SIKAQUEUE_H
#define SIKAQUEUE_H
#include "SikaStack.h"

#pragma message("Including SikaQueue.h")
namespace Sika {
    /**
     * 动态队列, 需要属性 _head, _size, _front, _back
     * 首次插入使用头插,HEAD->next=newNode, _front=newData, _back=newData 头尾指向新节点
     * 非首次插入使用头插, 新元素的下一节点为原本的back, HEAD->next=newNode, _front不变, back指向新元素, _back->next=newData
     */
    template<class T>
    class SikaQueue {
        SikaNode<T>* _head;
        int _size;
        SikaNode<T>* _front;
        SikaNode<T>* _back;

        template<class Y>
        friend std::ostream& operator<<(std::ostream& print, SikaQueue<Y>& queue);
    public:
        SikaQueue():_head(new SikaNode<T>()), _size(0), _front(nullptr), _back(nullptr){}
        ~SikaQueue() {
            _size = 0;
            auto needFree = _head->getNextNode();
            while (needFree != nullptr) {
                auto nextNode = needFree->getNextNode();
                delete needFree;
                needFree = nextNode;
            }
        }

        void push(T data) {
            auto newNode = new SikaNode<T>(data);
            // 空队列插入
            if (_size == 0) {
                _head->setNextNode(newNode);
                _front = newNode;
                _back = newNode;
            }
            else {
                newNode->setNextNode(_back);
                _head->setNextNode(newNode);
                _back = newNode;
            }
            _size++;
        }

        T peek() {
            if (_size <= 0) {
                throw std::length_error("队列为空");
            }
            return _front->getData();
        }

        T pull() {
            if (_size <= 0) {
                throw std::length_error("队列为空");
            }
            // 获取队列前端数据
            auto data = _front->getData();
            // front 指针移动到上一个节点
            auto next_node = _head->getNextNode();
            while (next_node != nullptr && next_node->getNextNode() != _front) {
                next_node = next_node->getNextNode();
            }
            delete _front;
            next_node->setNextNode(nullptr);
            _front = next_node;
            _size--;
            return data;
        }

        [[nodiscard]] int size() const {
            return _size;
        }

        [[nodiscard]] bool isEmpty() const {
            return _size == 0;
        }
    };

    template<class T>
    std::ostream& operator<<(std::ostream& print, SikaQueue<T>& queue) {
        if (queue.size() <= 0) {
            print << "[]";
            return print;
        }

        std::string builder = "[";
        auto dataNode = queue._head->getNextNode();
        while (dataNode != nullptr) {
            builder.append(std::to_string(dataNode->getData()) + ", ");
            dataNode = dataNode->getNextNode();
        }

        const unsigned int lastComma = builder.find_last_of(", ");
        if (lastComma == builder.size() - 1) {
            builder = builder.substr(0, lastComma - 1);
        }

        builder.append("]");
        print << builder;

        return print;
    }
} // Sika

#endif //SIKAQUEUE_H
