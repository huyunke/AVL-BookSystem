#include "include/FileOperator.h"
#include "include/Book.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

using namespace std;

//从文件中读取图书信息
bool FileOperator::readBookFile(string bookFilename,AVLTree* tree) {
    ifstream bookFile(bookFilename);
    if (!bookFile) {
        cout << "无法打开图书文件" << endl;
        return false;
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
        //status为0表示借出，为1表示未借出
        if (status=="0") {
            bookStatus=false;
        } else {
            bookStatus=true;
        }
        Book* book =new Book(id,name,author,borrowerId,bookStatus);
        tree->insert(*book);
    }
    return true;
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

bool FileOperator::readUserFile(string userFilename,unordered_map<string,User*>& userMap) {
    ifstream userFile(userFilename);
    if (!userFile) {
        cout << "无法打开用户文件" << endl;
        return false;
    }
    string line;
    while (getline(userFile, line)) {
        istringstream iss(line);
        string id;
        string name;
        string password;
        string type;
        iss>>id>>name>>password>>type;
        //如果出现空值跳过该行
        if (id.empty()||name.empty()||password.empty()||type.empty()) {
            continue;
        }
        User* user =new User(id,name,password,type);
        string bookId;
        while (iss>>bookId) {
            user->addBorrowInfo(bookId);
        }
        userMap.insert({id,user});
    }
    return true;
}

void FileOperator::writeUserFile(string userFilename,User* user) {
    ofstream writeUserFile(userFilename);
    ifstream readUserFile(userFilename);
    if (!writeUserFile||!readUserFile) {
        cout << "无法打开用户文件" << endl;
        return;
    }
    //遍历用户信息，查找到当前用户信息所在位置
    string line;
    while (getline(readUserFile, line)) {
        istringstream iss(line);
        string id;
        iss>>id;
        if (id==user->getId()) {
            writeUserFile<<user->getId()<<" "<<user->getName()<<" "<<user->getPassword()<<" "<<user->getType();
            string borrowBookIds=user->getBorrowBookId();
            writeUserFile<<borrowBookIds;
            writeUserFile<<endl;
        } else {
            writeUserFile<<line<<endl;
        }
    }
}