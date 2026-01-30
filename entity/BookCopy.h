#ifndef AVL_BOOKSYSTEM_BOOKCOPY_H
#define AVL_BOOKSYSTEM_BOOKCOPY_H
#include<string>
using namespace std;

class BookCopy {
    string bookId;
    string copyId;
    string status;
public:
    BookCopy(string bookId, string copyId, string status="available");
    BookCopy();
    ~BookCopy();
    string getBookId()const;
    string getCopyId()const;
    string getStatus()const;
    void setBookId(string bookId);
    void setCopyId(string copyId);
    void setStatus(string status);
};


#endif //AVL_BOOKSYSTEM_BOOKCOPY_H