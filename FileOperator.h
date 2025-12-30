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
    bool static readBookFile(string bookFilename,AVLTree* tree);
    void static writeBookFile(string bookFilename,AVLTree* tree);
    bool static readUserFile(string userFilename,unordered_map<string,User*>& userMap);
    void static writeUserFile(string userFilename,User* user);
};


#endif //AVL_BOOKSYSTEM_FILEOPERATOR_H