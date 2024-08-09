#include <iostream>
#include <vector>
#include "PointerAndReference.hpp"
#include "SikaQueue.h"
#include "SikaSinglyLinkedList.h"
#include "SikaStack.h"

#include "SikaBinaryTree.h"
#include "SikaQueue.h"
#include "SikaBinaryTree.h"
#include "tree_by_gpt.cpp"

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

    std::cout << "queue = " << queue << std::endl;

    std::cout << "queue.peek() is " << queue.peek() << std::endl;
    std::cout << "queue.pull() is " << queue.pull() << std::endl;
    std::cout << "queue.size() is " << queue.size() << std::endl;

    std::cout << "queue = " << queue << std::endl;
}

template<typename T>
void traveralsTree(Sika::SikaBinaryTree<T>* tree) {
    std::cout << "please check the order of pre-order traversal: " << std::endl;
    tree->prePrint();
    std::cout << std::endl;
    std::cout << "please check the order of mid-order traversal: " << std::endl;
    tree->inPrint();
    std::cout << std::endl;
    std::cout << "please check the order of post-order traversal: " << std::endl;
    tree->postPrint();
    std::cout << std::endl;
    std::cout << "please check the order of level-order traversal: " << std::endl;
    tree->levelPrint();
    std::cout << std::endl;
}

void fillTree(Sika::SikaBinaryTree<int>* integerTree) {
    integerTree->assignNode(2);
    integerTree->assignNode(3);
    integerTree->assignNode(4);
    integerTree->assignNode(5);
    integerTree->assignNode(6);
    integerTree->assignNode(7);
    integerTree->assignNode(8);
}
void testSikaTree() {
    Sika::SikaBinaryTree<int> tree;
    tree.setRoot(5);
    tree.assignNode(3);
    tree.assignNode(7);
    tree.assignNode(2);
    tree.assignNode(4);
    tree.assignNode(6);
    tree.assignNode(8);

    std::cout << "tree depth is: " << tree.getDepth() << std::endl;
    std::cout << "tree is empty: " << ((tree.isEmpty() == true) ? "true" : "false") << std::endl;
    std::cout << "root value is: " << tree.rootdata() << std::endl;
    traveralsTree(&tree);

    std::cout << "deleted left child! " << std::endl;
    tree.deleteLeftChild();
    std::cout << "tree depth is: " << tree.getDepth() << std::endl;
    std::cout << "tree is empty: " << ((tree.isEmpty() == true) ? "true" : "false") << std::endl;
    traveralsTree(&tree);

    std::cout << "deleted right child! " << std::endl;
    tree.deleteRightChild();
    std::cout << "tree depth is: " << tree.getDepth() << std::endl;
    std::cout << "tree is empty: " << ((tree.isEmpty() == true) ? "true" : "false") << std::endl;
    traveralsTree(&tree);

    std::cout << "clear tree! " << std::endl;
    tree.clear();
    std::cout << "tree depth is: " << tree.getDepth() << std::endl;
    std::cout << "tree is empty: " << ((tree.isEmpty() == true) ? "true" : "false") << std::endl;
    traveralsTree(&tree);

    // todo 未处理树自旋, 导致单支树
    fillTree(&tree);
    std::cout << "fill tree! " << std::endl;
    std::cout << "tree depth is: " << tree.getDepth() << std::endl;
    std::cout << "tree is empty: " << ((tree.isEmpty() == true) ? "true" : "false") << std::endl;
    traveralsTree(&tree);
    tree.deleteChild();
    std::cout << "delete child of tree! " << std::endl;
    std::cout << "tree depth is: " << tree.getDepth() << std::endl;
    std::cout << "tree is empty: " << ((tree.isEmpty() == true) ? "true" : "false") << std::endl;
    traveralsTree(&tree);
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

int main() {
    testSikaStack();
    // todoTestSikaQueue();
    return 0;
}