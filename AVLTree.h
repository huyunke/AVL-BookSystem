#ifndef AVL_BOOKSYSTEM_AVLTREE_H
#define AVL_BOOKSYSTEM_AVLTREE_H
#include "AVLNode.h"
using namespace std;

class AVLTree {
    AVLNode* root;
    int getBalance(AVLNode* node);//获取平衡因子

    //两种旋转操作
    AVLNode* leftRotate(AVLNode* node);//左旋
    AVLNode* rightRotate(AVLNode* node);//右旋

    //四种调整方式
    AVLNode* LL(AVLNode* node);
    AVLNode* RR(AVLNode* node);
    AVLNode* LR(AVLNode* node);
    AVLNode* RL(AVLNode* node);

    void clear(AVLNode *node);//清空树

    bool isBalanced(AVLNode* node);//检查平衡树是否平衡

    AVLNode* insert(AVLNode* node,const Book& book);//插入结点
    AVLNode* remove(AVLNode* node,const string& bookId);//删除节点
    void updateHeight(AVLNode* node);//更新高度
    AVLNode* minValueNode(AVLNode* node);//找到最小值结点
    void printTree(AVLNode* node);
public:
    AVLTree():root(nullptr){};
    ~AVLTree();
    void insert(const Book& book);//插入结点
    void remove(const string& bookId);//删除结点
    AVLNode* search(const string& bookId) const;//查找结点
    void printTree();//中序遍历打印树，用于测试
    AVLNode* getRoot();//获取根节点
};


#endif //AVL_BOOKSYSTEM_AVLTREE_H