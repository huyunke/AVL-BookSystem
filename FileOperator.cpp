#include "include/FileOperator.h"
#include "include/Book.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

//从文件中读取图书信息
void FileOperator::readBookFile(string bookFilename,AVLTree* tree) {
    ifstream bookFile(bookFilename);
    if (!bookFile) {
        cout << "无法打开图书文件" << endl;
        return;
    }
    string line;
    while (getline(bookFile, line)) {
        istringstream iss(line);
        string id;
        string name;
        string author;
        string borrowerId;
        string status;
        iss>>id>>name>>author>>borrowerId>>status;
        //如果出现空值跳过该行
        if (id.empty()||name.empty()||author.empty()||borrowerId.empty()||status.empty()) {
            continue;
        }
        bool bookStatus;
        //status为0表示未借出，为1表示已借出
        if (status=="0") {
            bookStatus=false;
        } else {
            bookStatus=true;
        }
        Book* book =new Book(id,name,author,borrowerId,bookStatus);
        tree->insert(*book);
    }
}

//将图书信息写入文件
void FileOperator::writeBookFile(string bookFilename,AVLTree* tree) {
    ofstream bookFile(bookFilename);
    if (!bookFile) {
        cout << "无法打开图书文件" << endl;
        return;
    }
    //采用前序遍历AVL树
    AVLNode* node=tree->getRoot();
    if (node==nullptr) {
        return;
    }
    writeBookFile(bookFile,node);
}

void FileOperator::writeBookFile(ofstream& file,AVLNode* node) {
    if (node==nullptr) {
        return;
    }
    file<<node->book.getId()<<" "<<node->book.getName()<<" "<<node->book.getAuthor()<<" "<<node->book.getBorrowerId()<<" "<<node->book.getStatus()<<endl;
    writeBookFile(file,node->left);
    writeBookFile(file,node->right);
}