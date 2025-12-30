#ifndef AVL_BOOKSYSTEM_AVLNODE_H
#define AVL_BOOKSYSTEM_AVLNODE_H
#include "Book.h"
using namespace std;

struct AVLNode {
    Book book;
    AVLNode* left;
    AVLNode* right;
    int height;
public:
    AVLNode(Book book):book(book),left(nullptr),right(nullptr),height(1){};
    // ~AVLNode();
    // AVLNode* getLeft();
    // AVLNode* getRight();
    // int getHeight();
    // Book getBook();
    // void setLeft(AVLNode* left);
    // void setRight(AVLNode* right);
    void updateHeight();
};


#endif //AVL_BOOKSYSTEM_AVLNODE_H