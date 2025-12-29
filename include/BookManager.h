#ifndef AVL_BOOKSYSTEM_BOOKMANAGER_H
#define AVL_BOOKSYSTEM_BOOKMANAGER_H
#include "AVLTree.h"
using namespace std;

//图书管理类
class BookManager {
    AVLTree* tree;//存放图书AVL树的根节点
public:
    BookManager();
    ~BookManager();
    void addBook(Book& book);//添加图书
    void removeBook(const string& bookId);//删除书籍
    void searchBook(const string& bookId);//查询书籍
    void borrowBook(const string& bookId, User& user);//借阅书籍
    void returnBook(const string& bookId);//归还书籍
};


#endif //AVL_BOOKSYSTEM_BOOKMANAGER_H