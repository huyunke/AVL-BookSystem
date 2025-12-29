#ifndef AVL_BOOKSYSTEM_FILEOPERATOR_H
#define AVL_BOOKSYSTEM_FILEOPERATOR_H
#include <string>
#include "AVLTree.h"
using namespace std;

class FileOperator {
    void static writeBookFile(ofstream& file,AVLNode* node);
public:
    void static readBookFile(string bookFilename,AVLTree* tree);
    void static writeBookFile(string bookFilename,AVLTree* tree);
    void static readUserFile(string userFilename);
    void static writeUserFile(string userFilename);
};


#endif //AVL_BOOKSYSTEM_FILEOPERATOR_H