//
// Created by 22355 on 24-5-31.
//

#ifndef SIKASINGLYLINKEDLIST_H
#define SIKASINGLYLINKEDLIST_H

#include <ostream>
#include <string>
#include<stdexcept>

#include "SikaLinkedList.h"

namespace Sika {

    template<class T>
    class SikaSinglyLinkedNode {
        T data;
        SikaSinglyLinkedNode *next;

        template<class U>
        friend class SikaSinglyLinkedList;

    public:
        SikaSinglyLinkedNode(): data(T()), next(nullptr) {
        }

        // explicit 确保只能显示调用创建
        explicit SikaSinglyLinkedNode(const T &data): data(data), next(nullptr) {
        }

        SikaSinglyLinkedNode(const T &data, SikaSinglyLinkedNode *nextNode): data(data), next(nextNode) {
        }

        SikaSinglyLinkedNode *getNextNode() const {
            return this->next;
        }

        void setNextNode(SikaSinglyLinkedNode *nextNode) {
            this->next = nextNode;
        }

        T getData() const {
            return this->data;
        }

        void setData(const T &data) {
            this->data = data;
        }
    };

    template<class T>
    class SikaSinglyLinkedList
            : public SikaLinkedList<T> {
    private:
        SikaSinglyLinkedNode<T> *HEAD;
    public:
        /*
        创建一个带有头节点的空单链表
        */
        SikaSinglyLinkedList(): HEAD(new SikaSinglyLinkedNode<T>()) {}

        SikaSinglyLinkedList(SikaSinglyLinkedList& list) {
            this->HEAD = new SikaSinglyLinkedNode<T>;
            auto sourceNode = list.HEAD;
            while (sourceNode->getNextNode() != nullptr) {
                this->HEAD->setNextNode(sourceNode->getNextNode());
                sourceNode = sourceNode->getNextNode();
            }
        }

        ~SikaSinglyLinkedList() override{
            SikaSinglyLinkedNode<T> *currentNode = HEAD;
            while (currentNode != nullptr) {
                SikaSinglyLinkedNode<T> *nextNode = currentNode->getNextNode();
                delete currentNode;
                currentNode = nextNode;
            }
        }

        /**
         * 将数据插入到链表头部, 函数内部会将数据转为链表节点
         * @param data 要插入的数据
         */
        void head_insert(const T &data) override {
            /*
        auto* newNode = new SikaSinglyLinkedNode<T>(data, HEAD->getNextNode());
        HEAD->setNextNode(newNode);
         */
            // 未发现头节点
            if (this->HEAD == nullptr) {
                return;
            }
            // 空链表直接插入
            if (this->HEAD->getNextNode() == nullptr) {
                auto *node = new SikaSinglyLinkedNode<T>(data);
                this->HEAD->setNextNode(node);
            }
            // 非空链表使用临时节点存储头节点的下一个接点后插入
            else {
                auto *temp = this->HEAD->getNextNode();
                auto *newNode = new SikaSinglyLinkedNode<T>(data);
                newNode->setNextNode(temp);
                this->HEAD->setNextNode(newNode);
            }
        }

        /**
         * 将数据插入到链表尾部, 函数内部会将数据转为链表节点
         * @param data 要插入的数据
         */
        void tail_insert(const T &data) override {
            /*
            auto* currentNode = HEAD;
            while (currentNode->getNextNode() != nullptr) {
                currentNode = currentNode->getNextNode();
            }
            auto* newNode = new SikaSinglyLinkedNode<T>(data);
            currentNode->setNextNode(newNode);
            */

            // 未发现头节点
            if (this->HEAD == nullptr) {
                return;
            }
            // 指针移动到最末尾后直接插入
            auto *currentNode = this->HEAD;
            while (currentNode->getNextNode() != nullptr) {
                currentNode = currentNode->getNextNode();
            }
            auto *newNode = new SikaSinglyLinkedNode<T>(data);
            currentNode->setNextNode(newNode);
        }

        /**
         * 通过索引对应位置的节点
         * @param index 要删除的元素索引, 从1开始
         * @return 返回删除的元素的值,
         * 如果索引错误会直接触发异常,
         * 如果正常返回则一定是有效值
         * @throw std::invalid_argument 当索引为0或者负数
         * @throw std::out_of_range 索引超出当前链表长度
         */
        T delete_by_index(int index) override {
            if (index <= 0) {
                throw std::invalid_argument("Position cannot be negative or zero");
            }
            if (index >= this->size()) {
                throw std::out_of_range("Position out of range");
            }
            // 移动到目标位置的前一个位置
            auto *currentNode = this->HEAD;
            for (int i = 0; i < index - 1; i++) {
                currentNode = currentNode->getNextNode();
            }
            // 保存要删除的目标节点的下一个节点, 可能为nullptr
            auto *target = currentNode->getNextNode();
            auto *newNextNode = target->getNextNode();
            auto deleteResult = target->getData();
            target->setData(0);
            target->setNextNode(nullptr);
            delete target;
            currentNode->setNextNode(newNextNode);
            return deleteResult;
        }

        /**
         * 根据内容进行删除, 只会删除第一个找到的元素
         * @param data 要删除的元素
         * @return 返回删除的元素位置
         */
        int delete_by_data(const T &data) override {
            const int index = search_data(data);
            delete_by_index(index);
            return index;
        }

        /**
         * 根据数据查找节点在链表上的位置, 如果没找到返回-1
         * @param data 要查找的元素
         * @return 查找到的元素的位置
         */
        int search_data(const T &data) const override {
            auto *currentNode = this->HEAD->getNextNode();
            int target = 0;
            while (currentNode != nullptr) {
                if (data != currentNode->getData()) {
                    target++;
                    currentNode = currentNode->getNextNode();
                } else {
                    return target;
                }
            }
            return -1;
        }

        /**
         * 根据位置获取链表节点的内容
         * @param index 要获取数据的节点位置
         * @return 目标节点的数据
         * @throw std::invalid_argument 位置为负数时
         * @throw std::out_of_range 位置超出链表长度时
         */
        T get_data(int index) const override {
            if (index < 0) {
                throw std::invalid_argument("Position cannot be negative");
            }
            if (index >= this->size()) {
                throw std::out_of_range("Position out of range");
            }

            auto currnetNode = this->HEAD->getNextNode();
            for(int i = 0; i < index; i++) {
                currnetNode = currnetNode->getNextNode();
            }
            return currnetNode->getData();
        }

        /**
         *
         * @return 返回链表的长度
         */
        [[nodiscard]] int size() const override {
            int length = 0;
            auto *tempNode = this->HEAD;
            while (tempNode->getNextNode() != nullptr) {
                tempNode = tempNode->getNextNode();
                length++;
            }
            return length;
        }

        /**
         *
         * @return 返回链表的长度
         */
        [[nodiscard]] int length() const override {
            return this->size();
        };

        /**
         * 根据给定的规则对链表进行排序
         * @param rule 要排序的规则
         */
        void sort(std::function<bool(const T &, const T &)> rule) override {
            if (HEAD == nullptr || HEAD->getNextNode() == nullptr) {
                return;
            }
            bool swapped;
            do {
                swapped = false;
                SikaSinglyLinkedNode<T> *prev = HEAD;
                SikaSinglyLinkedNode<T> *curr = HEAD->getNextNode();
                SikaSinglyLinkedNode<T> *next = curr->getNextNode();
                while (next != nullptr) {
                    if (!rule(curr->getData(), next->getData())) {
                        std::swap(curr->data, next->data);
                        swapped = true;
                    }
                    prev = curr;
                    curr = next;
                    next = next->getNextNode();
                }
            } while (swapped);
        }

        [[deprecated]] T inverted_search(int index) const override {
            return 0;
        }

        /**
         * 打印整个链表
         * @param cout 输出流
         */
        void print_list(std::ostream &cout) {
            auto *node = this->HEAD->getNextNode();
            cout << "[";
            for (int i = 0; i < this->size(); i++) {
                cout << node->getData() << ", ";
                node= node->getNextNode();
            }
            cout << "]\n";
        }
    };

    template<class T>
    std::ostream& operator<<(std::ostream& print, SikaSinglyLinkedList<T>& list) {
        std::string stringBuilder = "[";
        for (int i = 0; i < list.size(); i++) {
            stringBuilder.append(std::to_string(list.get_data(i)) + ", ");
        }
        if (
            const auto lastComma = stringBuilder.find_last_of(", ");
            lastComma == stringBuilder.size() - 1
            ) {
            stringBuilder = stringBuilder.substr(0, lastComma-1);
        }
        stringBuilder.append("]");
        print << stringBuilder;
        return print;
    }
} // Sika

#endif //SIKASINGLYLINKEDLIST_H
