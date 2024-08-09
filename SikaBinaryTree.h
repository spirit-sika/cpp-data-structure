//
// Created by 22355 on 24-8-6.
//

#ifndef SIKABINARYTREE_H
#define SIKABINARYTREE_H
#include <algorithm>
#include <iostream>
#include <queue>
#include <functional>

namespace Sika {
    template<class T>
    class SikaTreeNode {
        T data;
        SikaTreeNode* left;
        SikaTreeNode* right;
    public:
        SikaTreeNode(): data(T()), left(nullptr), right(nullptr) {}
        explicit SikaTreeNode(T value): data(value), left(nullptr), right(nullptr) {}

        T getData() const {
            return data;
        }

        SikaTreeNode* getLeft() const {
            return left;
        }

        SikaTreeNode* getRight() const {
            return right;
        }

        void setData(T data) {
            this->data = data;
        }

        void setLeft(SikaTreeNode* node) {
            this->left = node;
        }

        void setRight(SikaTreeNode* node) {
            this->right = node;
        }

        void setLeft(T data) {
            this->left = new SikaTreeNode(data);
        }

        void setRight(T data) {
            this->right = new SikaTreeNode(data);
        }

        bool isLeaf() {
            return left == nullptr && right == nullptr;
        }
    };
    /**
     * ADT BinaryTree {
     *   数据对象D: D是具有相同特性的数据元素的集合
     *   数据关系R: 1. ROOT唯一
     *             2. 有若干个不相交子集 (子树)
     *             3. 根节点和左右孩子之间的关系说明
     *             3. 左子树和右子树的关系说明
     *
     *
     *   基本操作P:
     *   - createBiTree(&T, definition)
     *     - 初始条件 definition给出二叉树T的定义
     *     - 操作结果 按definition构造二叉树T
     *   - PreOrderTraverse(T)
     *     - 初始条件 二叉树T存在
     *     - 操作结果 先序遍历T, 对每个节点访问一次
     *   - InOrderTraverse(T)
     *   - PostOrderTraverse(T)
     * } ADT BinaryTree
     *
     * 性质一: 在二叉树的第i层上至多有2^(i-1)个节点(i>=1)
     * 性质二: 深度为k的二叉树至多有2^k - 1个节点(k>=1)
     * 性质三: 对任何一颗二叉树T, 如果其叶子数为n0, 度为2(有两个分支)的节点数为n2, 则n0 = n2 + 1
     * 完全二叉树性质:
     * 完全二叉的概念: 深度为k的具有n个节点的二叉树,
     * 当且仅当其每一个节点都与深度为k的满二叉树中编号为1~n的节点一一对应时, 称为完全二叉
     * 可以使用层序遍历的方式为满二叉进行编号, 然后从最后一个节点连续的去掉任意节点, 所有的树都是完全二叉树
     * 1. 完全二叉和满二叉树在顺序存储的情况下可以复原
     * 2. 具有n个节点的完全二叉树的深度为[log2N]+1   [X]称为X的底, 表示不大于X的最大整数 x=3.5,底为3
     * 3. 对于一棵有n个节点的完全二叉树(深度为[log2N]+1)的节点按层序编号, 则对任一节点i(1<=i<=n), 有:
     *   3.1 如果i = 1, 则节点i是二叉树的根, 无双亲, 如果i>1, 则其双亲是节点[i/2]  i/2的底
     *   3.2 如果2i>n, 则节点i为叶子节点, 无左孩子; 否则其左孩子是节点2i
     *   3.3 如果2i+1 > n, 则节点i无右孩子; 否则右孩子是节点2i+1
     *
     *
     *           [i/2]
     *         ↗       ↘
     *       i           i+1
     *     ↗  ↘         ↙    ↘
     *   2i    2i+1   2i+2  2i+3
     *
     *
     *   二叉树的顺序存储:
     *    按满二叉树的节点层次编号, 依次存放二叉树中的数据元素
     *    缺点: 1. 定长   2. 右单支极度浪费存储空间(最坏情况下,
     * 深度为k的且只有k个节点的单支树需要长度为(2^k)-1的一维数组) 适合满二叉和完全二叉树的存储
     *
     *               5
     *            ↙     ↘
     *         3           7
     *       ↙   ↘       ↙   ↘
     *      2     4     6     8
     *
     *      todo: 根据指针删除节点
     */
    template<class T>
    class SikaBinaryTree {
    protected:
        SikaTreeNode<T>* root;
        SikaTreeNode<T>* insert(SikaTreeNode<T>* node, T value) {
            if (node == nullptr) {
                return new SikaTreeNode<T>(value);
            }
            if (value < node->getData()) {
                 node->setLeft(insert(node->getLeft(), value));
            } else {
                node->setRight(insert(node->getRight(), value));
            }
            return node;
        }

        void destoryTree(SikaTreeNode<T>* tree) {
            if (tree != nullptr) {
                destoryTree(tree->getLeft());
                destoryTree(tree->getRight());
                delete tree;
            }
        }

        int getDepth(SikaTreeNode<T>* node) {
            if (node == nullptr) {
                return 0;
            }
            const int left = getDepth(node->getLeft());
            const int right = getDepth(node->getRight());
            return std::max(left, right) + 1;
        }

        void preTraverals(const SikaTreeNode<T>* node, const std::function<void(const SikaTreeNode<T>*)> oper) const {
            if (node != nullptr) {
                oper(node);
                preTraverals(node->getLeft(), oper);
                preTraverals(node->getRight(), oper);
            }
        }
        void inTraverals(SikaTreeNode<T>* node, const std::function<void(const SikaTreeNode<T>*)>& oper) const {
            if (node != nullptr) {
                inTraverals(node->getLeft(), oper);
                oper(node);
                inTraverals(node->getRight(), oper);
            }
        }
        void postTraverals(SikaTreeNode<T>* node, const std::function<void(const SikaTreeNode<T>*)>& oper) const {
            if (node != nullptr) {
                postTraverals(node->getLeft(), oper);
                postTraverals(node->getRight(), oper);
                oper(node);
            }
        }

        void levelTraverals(SikaTreeNode<T>* node, const std::function<void(const SikaTreeNode<T>*)>& oper) const {
            if (node == nullptr) {
                return;
            }
            std::queue<SikaTreeNode<T>*> nodeQueue;
            nodeQueue.push(node);

            while (!nodeQueue.empty()) {
                SikaTreeNode<T>* tempNode = nodeQueue.front();
                nodeQueue.pop();
                oper(tempNode);

                if (tempNode->getLeft() != nullptr) {
                    nodeQueue.push(tempNode->getLeft());
                }
                if (tempNode->getRight() != nullptr) {
                    nodeQueue.push(tempNode->getRight());
                }
            }
        }

    public:
        SikaBinaryTree() : root(nullptr) {}

        explicit SikaBinaryTree(T data) : root(new SikaTreeNode<T>(data)) {}

        /**
         * todo 根据数据列表构造一棵顺序二叉树
         * @param dataList 数据列表
         */
        SikaBinaryTree(T dataList[]) {

        }

        void setRoot(SikaTreeNode<T>* node) {
            destoryTree(root);
            root = node;
        }

        void setRoot(T value) {
            if (root == nullptr) {
                root = new SikaTreeNode<T>(value);
            }
            else {
                root->setData(value);
            }
        }

        // 后序销毁树
        ~SikaBinaryTree() {
            destoryTree(root);
        };

        /**
         * 清空整个树并释放除根节点以外的空间
         * 从根节点出发, 判断是否有孩子节点, 如果有孩子节点则继续深入, 知道节点为叶子节点后执行数据清除释放节点
         *
         */
        void clear() {
            destoryTree(root);
            root = nullptr;
        }

        /**
         * 判断树是否包含数据
         * @return true, 如果树为空(不包含任何数据)
         */
        [[nodiscard]] bool isEmpty() const {
            return root == nullptr;
        }

        /**
         * 获取树的深度
         * @return 返回整个树的深度
         */
        int getDepth() {
            return getDepth(root);
        }

        /**
         * 返回根节点的值
         * @return 根节点的值
         */
        T rootdata() {
            return root->getData();
        }

        /**
         * 先序打印树
         */
        void prePrint() const {
            preTraverals(root,
                std::function<void(const SikaTreeNode<T>*)>([](const SikaTreeNode<T>* node) {
                    std::cout << node->getData() << " ";
                }));
        }

        void preOper(const std::function<void(const SikaTreeNode<T>*)>& oper) const {
            preTraverals(root, oper);
        }

        /**
         * 中序打印树
         */
        void inPrint() const {
            inTraverals(root,
                std::function<void(const SikaTreeNode<T>*)>([](const SikaTreeNode<T>* node) {
                    std::cout << node->getData() << " ";
                }));
        }

        /**
         * 后序打印树
         */
        void postPrint() const {
            postTraverals(root,
                std::function<void(const SikaTreeNode<T>*)>([](const SikaTreeNode<T>* node) {
                    std::cout << node->getData() << " ";
                }));
        }

        /**
         * 层序打印树
         */
        void levelPrint() const {
            levelTraverals(root,
                std::function<void(const SikaTreeNode<T>*)>([](const SikaTreeNode<T>* node) {
                    std::cout << node->getData() << " ";
                }));
        }

        /**
         * 插入新的节点到树中
         * @param data 要插入的节点值
         */
        void assignNode(T data) {
            root = insert(root, data);
        }

        /**
         * 删除子树, 包括左右子树
         */
        void deleteChild() {
            if (root != nullptr && root->getLeft() != nullptr) {
                destoryTree(root->getLeft());
                root->setLeft(nullptr);
            }
            if (root != nullptr && root->getRight() != nullptr) {
                destoryTree(root->getRight());
                root->setRight(nullptr);
            }
        }

        /**
         * 删除左子树
         */
        void deleteLeftChild() {
            if (root != nullptr && root->getLeft() != nullptr) {
                destoryTree(root->getLeft());
                root->setLeft(nullptr);
            }
        }

        /**
         * 删除右子树
         */
        void deleteRightChild() {
            if (root != nullptr && root->getRight() != nullptr) {
                destoryTree(root->getRight());
                root->setRight(nullptr);
            }
        }

        /**
         * 根据给定值在对树中存在的节点进行删除, 此操作会连同节点的子节点一同删除
         * @param value 要删除的值
         */
        void deleteByData(T value) {

        }
    };

    /**
     * 高度平衡树 AVL, 通过插入时的自旋实现树的平衡
     * @tparam T 树节点存储的内容类型
     *
     * 节点的左子树高度-右子树高度为节点的平衡因子, 当平衡因子的绝对值<=1的时候树就是平衡树
     *
     * 插入操作时很容易让树失去平衡, 通过节点的左旋或者右旋就可以让树重新平衡
     *
     * 左旋: 向左旋转, 发生冲突时左孩子变成旋转节点右孩子
     * 右旋: 向右旋转, 发生冲突时右孩子变成旋转节点左孩子
     * LL 型: 导致失衡的节点在根节点的左孩子左子树上  (右旋)
     *                     14
     *                   ↙    ↘
     *                 6        17
     *               ↙   ↘
     *             5       9
     *           ↙
     *         3
     *
     *  RR 型: (左旋)
     *                       5
     *                     ↙   ↘
     *                   3      9
     *                         ↙  ↘
     *                        6    14
     *                               ↘
     *                                 17
     *
     * LR 型: 导致失衡的节点在根节点左孩子的右子树上 (左孩子左旋, 根节点再右旋)
     *                   9
     *                 ↙   ↘
     *               5       14
     *             ↙   ↘
     *           3       8
     *                 ↙
     *               6
     *  左孩子左旋变为:
     *                  9
     *                ↙   ↘
     *              8       14
     *            ↙
     *          5
     *        ↙   ↘
     *      3       6
     * 最后自身右旋变为:
     *                  8
     *                ↙   ↘
     *              5       9
     *            ↙   ↘       ↘
     *          3       6       14
     *
     * RL型: 导致失衡的节点在根节点右孩子的左子树上 (右孩子右旋, 自身左旋)
     *                  5
     *                ↙   ↘
     *              3       9
     *                    ↙   ↘
     *                  6       14
     *                    ↘
     *                      8
     *
     * 右旋右孩子变成:
     *                    5
     *                  ↙   ↘
     *                3       6
     *                          ↘
     *                            9
     *                          ↙   ↘
     *                        8       14
     * 自身左旋变为:
     *                       6
     *                     ↙   ↘
     *                   5       9
     *                 ↙       ↙   ↘
     *               3       8       14
     *
     * 如果根平衡因子 = 2,  树必然是 L?型, 左孩子的平衡因子=1, 为LL型, 左孩子平衡因子=-1, 为LR型
     * 如果根平衡因子 = -2, 树必然是 R?型, 右孩子的平衡因子=1, 为RL型, 右孩子平衡因子=-1, 为RR型
     *
     *                                  平衡因子 = 1, LL型  (右旋)
     *                                ↗
     * 根节点平衡因子 = 2, L?型, 看左孩子
     *                                ↘
     *                                  平衡因子 = -1, LR型  (左孩子左旋, 自身右旋)
     *
     *
     *                                   平衡因子 = 1, RL型  (右孩子右旋, 自身左旋)
     *                                 ↗
     * 根节点平衡因子 = -2, R?型, 看右孩子
     *                                 ↘
     *                                   平衡因子 = -1, RR型  (左旋)
     *
     * 如果在插入时已经存在多个双亲节点失衡的情况, 只需要处理离失衡节点最近的节点即可, 只在插入时有效
     *                   3
     *                 ↙   ↘
     *               1       6
     *                         ↘
     *                           7
     *                             ↘
     *                               9
     * 根节点3的平衡因子是-2, 6节点的平衡因子也是-2, 存在多个失衡节点, 处理失衡节点最近的节点, 也就是针对6节点进行操作即可
     * RR型失衡树, 左旋, 因为处理离9最近的节点就是6左旋
     *                     3
     *                   ↙   ↘
     *                 1       7
     *                       ↙   ↘
     *                     6       9
     *
     * [14, 9, 5, 17, 11, 12, 7, 19, 16, 27]
     */
    // template<class T>
    // class SikaAVLTree :public SikaBinaryTree<T> {
    // private:
    //     /**
    //      * AVL树节点
    //      *
    //      * 为节点增加 height 属性, 通过 height 可以轻松计算节点之间的高度差
    //      * 在树的插入和删除时计算高度差查看是否发生失衡, 并进行相应的旋转操作
    //      */
    //     struct AVLTreeNode {
    //         T data;
    //         AVLTreeNode* left;
    //         AVLTreeNode* right;
    //         int height;
    //     };
    //     AVLTreeNode<T>* root = nullptr;
    //     SikaTreeNode<T>* insert(SikaTreeNode<T>* node, T value) {}
    //
    //     /**
    //      * 插入新的节点到树中
    //      * @param data 要插入的节点值
    //      */
    //     void assignNode(T data) {
    //         root = insert(root, data);
    //     }
    //
    //
    // };

    /**
     * 红黑树, 子平衡二叉树的一种
     * Red-Black Tree
     * - 红黑树的前提必须是一棵二叉搜索树, 并且在红黑树中使用 NULL 充当叶子节点,
     * - 红黑树的根节点和叶子节点始终为黑色, 并且红节点的孩子节点必须是黑色 (红黑树不存在两个连续的红色节点)
     * - 任一节点到叶子节点(NULL)所有路径黑节点数量相同
     * 左根右, 根叶黑, 不红红, 黑相同
     *
     * 红黑树的左右子树高度相差不会超过两倍, AVL是左右子树高度差不能超过1, AVL对于平衡的要求会更高
     * @tparam T 树节点存储的内容类型
     */
    template<class T>
    class SikaRBTree :public SikaBinaryTree<T> {

    };
} // Sika

#endif //SIKABINARYTREE_H
