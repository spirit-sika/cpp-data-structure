//
// Created by 22355 on 24-5-31.
//

#ifndef SIKALINKEDLIST_H
#define SIKALINKEDLIST_H

#include<functional>
namespace Sika {
    template<class T>
    class SikaLinkedList
    {
    public:
        virtual ~SikaLinkedList() = default;

        /*遍历*/

        /*
        插入节点, 将数据插入到链表头部
        调用者负责将数据传入，数据封装成节点需要由方法实现负责
        */
        virtual void head_insert(const T& data) = 0;
        /*
        插入节点, 将数据插入到链表末尾
        调用者负责将数据传入，数据封装成节点需要由方法实现负责
        */
        virtual void tail_insert(const T& data) = 0;
        /*
        删除节点，将指定位置上的元素删除
        超出链表长度时不执行
        删除后返回被删除的节点内容
        */
        virtual T delete_by_index(int index) = 0;
        /*
        删除节点，在链表中查找需要删除的元素，
        只删除第一个，成功找到则删除并返回删除的元素位置
        如果未找到则返回-1
        */
        virtual int delete_by_data(const T& data) = 0;
        /*
        查找节点，在链表中根据内容找到对应的位置
        未找到返回-1
        */
        virtual int search_data(const T& data) const = 0;
        /*
        获取目标位置节点的内容
        throw std::out_of_range("Position cannot be negative");
        throw std::out_of_range("Position out of range");
        */
        virtual T get_data(int index) const = 0;
        /*
        获取链表长度
        */
        [[nodiscard]] virtual int size() const = 0;
        /*
        获取链表长度
        */
        [[nodiscard]] virtual int length() const = 0;
        /*
        排序，按照指定的方式进行排序
        */
        virtual void sort(std::function<bool(const T&, const T&)> rule) = 0;
        /*
        倒排查找
        */
        virtual T inverted_search(int index) const = 0;
    };
}


#endif //SIKALINKEDLIST_H
