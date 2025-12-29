#ifndef AVL_BOOKSYSTEM_AVLTREE_H
#define AVL_BOOKSYSTEM_AVLTREE_H
#include"AVLNode.h"
using namespace std;
//修改图书信息操作是否添加暂定

class AVLTree {
    AVLNode* root;
    //1。获取平衡因子
    int getBalance(AVLNode* node);
    //2.两种旋转操作
    AVLNode* leftRotate(AVLNode* node);//左旋
    AVLNode* rightRotate(AVLNode* node);//右旋
    //3.四种调整方式
    AVLNode* LL(AVLNode* node);
    AVLNode* RR(AVLNode* node);
    AVLNode* LR(AVLNode* node);
    AVLNode* RL(AVLNode* node);
    //4.删除
    void clear(AVLNode *node);
    //5.返回查找结点的前一个结点
    AVLNode* findParent(const string& bookId) const;
    //6.检查平衡树是否平衡
    bool isBalanced(AVLNode* node);
    //7.调整函数，封装四种调整方法
    AVLNode* insert(AVLNode* node,const Book& book);
    AVLNode* remove(AVLNode* node,const string& bookId);
    void updateHeight(AVLNode* node);
    AVLNode* minValueNode(AVLNode* node);
public:
    AVLTree():root(nullptr){};
    ~AVLTree();
    void insert(const Book& book);
    void remove(const string& bookId);
    AVLNode* search(const string& bookId) const;
    void printTree();
    AVLNode* getRoot();
};


#endif //AVL_BOOKSYSTEM_AVLTREE_H