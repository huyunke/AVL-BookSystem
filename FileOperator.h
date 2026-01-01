#ifndef AVL_BOOKSYSTEM_FILEOPERATOR_H
#define AVL_BOOKSYSTEM_FILEOPERATOR_H
#include <string>
#include "AVLTree.h"
#include "User.h"
#include <unordered_map>
using namespace std;

class FileOperator {
    void static writeBookFile(ofstream& file,AVLNode* node);
public:
    bool static readBookFile(string bookFilename,AVLTree* tree);//从文件中读取图书信息
    void static writeBookFile(string bookFilename,AVLTree* tree);//将图书信息写入文件
    bool static readUserFile(string userFilename,unordered_map<string,User*>& userMap);//从文件中读取用户信息
    void static writeUserFile(string userFilename,User* user);//将当前用户信息重新写入文件
    void static writeAllUsersFile(string userFilename,unordered_map<string,User*>& userMap);//将所有用户信息写入文件
};


#endif //AVL_BOOKSYSTEM_FILEOPERATOR_H