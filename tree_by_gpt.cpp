//
// Created by 22355 on 24-8-7.
//

#include <queue>
#include <algorithm> // 为了使用std::max
#include <iostream>

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinaryTree {
private:
    TreeNode<T>* root;

    TreeNode<T>* insert(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return new TreeNode<T>(value);
        } else if (value < node->data) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    void inOrderTraversal(TreeNode<T>* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            std::cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    void preOrderTraversal(TreeNode<T>* node) const {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void postOrderTraversal(TreeNode<T>* node) const {
        if (node != nullptr) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            std::cout << node->data << " ";
        }
    }

    void levelOrderTraversal(TreeNode<T>* node) const {
        if (node == nullptr) {
            return;
        }

        std::queue<TreeNode<T>*> q;
        q.push(node);

        while (!q.empty()) {
            TreeNode<T>* current = q.front();
            q.pop();
            std::cout << current->data << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    void destroyTree(TreeNode<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    int getDepth(TreeNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        } else {
            int leftDepth = getDepth(node->left);
            int rightDepth = getDepth(node->right);
            return std::max(leftDepth, rightDepth) + 1;
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroyTree(root);
    }

    void insert(T value) {
        root = insert(root, value);
    }

    void inOrderTraversal() const {
        inOrderTraversal(root);
        std::cout << std::endl;
    }

    void preOrderTraversal() const {
        preOrderTraversal(root);
        std::cout << std::endl;
    }

    void postOrderTraversal() const {
        postOrderTraversal(root);
        std::cout << std::endl;
    }

    void levelOrderTraversal() const {
        levelOrderTraversal(root);
        std::cout << std::endl;
    }

    [[nodiscard]] int getDepth() const {
        return getDepth(root);
    }

    void clean() {
        destroyTree(root);
        root = nullptr; // 将根节点设置为nullptr，表示树为空
    }
};
