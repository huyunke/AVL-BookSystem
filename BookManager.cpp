#include "include/BookManager.h"
#include<iostream>
using namespace std;

BookManager::BookManager() {
    tree=new AVLTree();
}

BookManager::~BookManager() {
    if (tree==nullptr) return;
    tree->~AVLTree();
}

void BookManager::addBook(Book &book) {
    AVLNode* targetBook=tree->search(book.get_id());
    if (targetBook!=nullptr) {
        cout<<"图书已存在"<<endl;
        cout<<"请检查书本id是否正确"<<endl;
        return;
    }
    tree->insert(book);
}

void BookManager::removeBook(const string &bookId) {
    if (!tree->search(bookId)) {
        cout<<"图书不存在"<<endl;
        cout<<"请检查书本id是否正确"<<endl;
        return;
    }
    tree->remove(bookId);
}

void BookManager::searchBook(const string &bookId) {
    AVLNode* targetBook=tree->search(bookId);
    //图书不存在
    if (targetBook==nullptr) {
        return;
    }
    //图书存在输出信息
    targetBook->book.printBookInfo();
}

void BookManager::borrowBook(const string &bookId, User &user) {
    AVLNode* targetBook=tree->search(bookId);
    if (targetBook==nullptr) {
        cout<<"图书不存在"<<endl;
        cout<<"请检查书本id是否正确"<<endl;
        return;
    }
    if (targetBook->book.get_status()) {
        cout<<"图书已借出"<<endl;
        return;
    }
    targetBook->book.setBookStatus(true);
    targetBook->book.setBorrower(user);
    cout<<"借阅成功"<<endl;
}

void BookManager::returnBook(const string &bookId) {
    AVLNode* targetBook=tree->search(bookId);
    if (targetBook==nullptr) {
        cout<<"图书不存在"<<endl;
        cout<<"请检查书本id是否正确"<<endl;
        return;
    }
    if (!targetBook->book.get_status()) {
        cout<<"图书未借出"<<endl;
        return;
    }
    targetBook->book.setBookStatus(false);
    cout<<"归还成功"<<endl;
}