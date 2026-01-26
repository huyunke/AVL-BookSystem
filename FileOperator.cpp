#include "FileOperator.h"
#include "Book/Book.h"
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
        Book book =Book(id,name,author,borrowerId,bookStatus);
        tree->insert(book);
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

//利用递归遍历AVL树结点，将其写入文件
void FileOperator::writeBookFile(ofstream& file,AVLNode* node) {
    if (node==nullptr) {
        return;
    }
    file<<node->book.getId()<<" "<<node->book.getName()<<" "<<node->book.getAuthor()<<" "<<node->book.getBorrowerId()<<" "<<node->book.getStatus()<<endl;
    writeBookFile(file,node->left);
    writeBookFile(file,node->right);
}

//从文件中读取用户信息
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
        string borrowData;
        while (iss>>borrowData) {
            //解析借阅数据格式：bookId:borrowTime:returnTime
            size_t firstColon = borrowData.find(':');
            //格式：bookId:borrowTime:returnTime
            size_t secondColon = borrowData.find(':', firstColon + 1);
            if (secondColon == string::npos) {
                //格式错误，跳过
                continue;
            }
            string bookId = borrowData.substr(0, firstColon);
            string borrowTimeStr = borrowData.substr(firstColon + 1, secondColon - firstColon - 1);
            string returnTimeStr = borrowData.substr(secondColon + 1);

            time_t borrowTime = stoll(borrowTimeStr);
            time_t returnTime = stoll(returnTimeStr);
            user->addBorrowInfoWithTime(bookId, borrowTime, returnTime);
        }
        userMap.insert({id,user});
    }
    return true;
}

//将当前用户信息重新写入文件
void FileOperator::writeUserFile(string userFilename,User* user) {
    //先读取所有用户信息
    ifstream readUserFile(userFilename);
    if (!readUserFile) {
        cout << "无法打开用户文件进行读取" << endl;
        return;
    }

    vector<string> lines;
    string line;

    while (getline(readUserFile, line)) {
        stringstream ss(line);
        string id;
        ss>>id;
        if (id==user->getId()) {
            //更新当前用户的信息
            string updatedLine = user->getId() + " " + user->getName() + " " +
                                user->getPassword() + " " + user->getType() +
                                user->getBorrowBookDataWithTime();
            lines.push_back(updatedLine);
        } else {
            lines.push_back(line);
        }
    }
    readUserFile.close();

    //写回文件
    ofstream writeUserFile(userFilename);
    if (!writeUserFile) {
        cout << "无法打开用户文件进行写入" << endl;
        return;
    }

    for (int i = 0; i < lines.size(); i++) {
        writeUserFile << lines[i] << endl;
    }
    writeUserFile.close();
}

//将所有用户信息写入文件
void FileOperator::writeAllUsersFile(string userFilename,unordered_map<string,User*>& userMap) {
    ofstream userFile(userFilename);
    if (!userFile) {
        cout << "无法打开用户文件进行写入" << endl;
        return;
    }

    //遍历所有用户并写入文件
    for (auto& pair : userMap) {
        User* user = pair.second;
        userFile << user->getId() << " " << user->getName() << " "
                 << user->getPassword() << " " << user->getType()
                 << user->getBorrowBookDataWithTime() << endl;
    }
    userFile.close();
}