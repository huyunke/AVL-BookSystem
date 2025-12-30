#include "FileOperator.h"
#include "Book.h"
#include "User.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <vector>

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

//需要检查
void FileOperator::writeUserFile(string userFilename,User* user) {
    // 先读取所有用户信息
    ifstream readUserFile(userFilename);
    if (!readUserFile) {
        cout << "无法打开用户文件进行读取" << endl;
        return;
    }

    vector<string> allLines;
    string line;
    bool userFound = false;

    while (getline(readUserFile, line)) {
        istringstream iss(line);
        string id;
        iss>>id;
        if (id==user->getId()) {
            // 更新当前用户的信息
            string updatedLine = user->getId() + " " + user->getName() + " " +
                                user->getPassword() + " " + user->getType() +
                                user->getBorrowBookId();
            allLines.push_back(updatedLine);
            userFound = true;
        } else {
            allLines.push_back(line);
        }
    }
    readUserFile.close();

    // 如果用户不存在，添加新用户
    if (!userFound) {
        string newLine = user->getId() + " " + user->getName() + " " +
                        user->getPassword() + " " + user->getType() +
                        user->getBorrowBookId();
        allLines.push_back(newLine);
    }

    // 写回文件
    ofstream writeUserFile(userFilename);
    if (!writeUserFile) {
        cout << "无法打开用户文件进行写入" << endl;
        return;
    }

    for (const auto& l : allLines) {
        writeUserFile << l << endl;
    }
    writeUserFile.close();
}