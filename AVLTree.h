#ifndef AVL_BOOKSYSTEM_AVLTREE_H
#define AVL_BOOKSYSTEM_AVLTREE_H
#include "AVLNode.h"
#include<string>
using namespace std;

class AVLTree {
    AVLNode* root;
    int getBalance(AVLNode* node);//获取平衡因子

    //两种旋转操作
    AVLNode* leftRotate(AVLNode* node);//左旋
    AVLNode* rightRotate(AVLNode* node);//右旋

    void clear(AVLNode *node);//清空树

    bool isBalanced(AVLNode* node);//检查平衡树是否平衡

    AVLNode* insert(AVLNode* node,const Book& book);//插入结点
    AVLNode* remove(AVLNode* node,const string& bookId);//删除节点
    void updateHeight(AVLNode* node);//更新高度
    AVLNode* minValueNode(AVLNode* node);//找到最小值结点
    AVLNode* maxValueNode(AVLNode* node);//找到最大值结点
    void printTree(AVLNode* node);
    void printAllBooks(AVLNode* node, bool isAdmin);//打印所有图书信息
    AVLNode* buildShadowTree(AVLNode* t, int level, int& column);//构建影子树
    void clearShadowTree(AVLNode* shadowRoot);//清空影子树
public:
    AVLTree():root(nullptr){};
    ~AVLTree();
    void insert(const Book& book);//插入结点
    void remove(const string& bookId);//删除结点
    AVLNode* search(const string& bookId) const;//查找结点
    void printTree();//中序遍历打印树，用于测试
    void printAllBooks(bool isAdmin);//打印所有图书信息
    AVLNode* getRoot();//获取根节点
    void printAVLTree();//打印AVL树
};


#endif //AVL_BOOKSYSTEM_AVLTREE_H