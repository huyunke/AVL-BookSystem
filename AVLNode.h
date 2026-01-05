#ifndef AVL_BOOKSYSTEM_AVLNODE_H
#define AVL_BOOKSYSTEM_AVLNODE_H
#include "Book.h"
using namespace std;

struct AVLNode {
    Book book;
    AVLNode* left;
    AVLNode* right;
    int level;
    int column;
    int height;
    AVLNode(Book book):book(book),left(nullptr),right(nullptr),level(0),column(0),height(1){};
    void updateHeight();//更新高度
};


#endif //AVL_BOOKSYSTEM_AVLNODE_H