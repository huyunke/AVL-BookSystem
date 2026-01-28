#ifndef AVL_BOOKSYSTEM_RECORD_H
#define AVL_BOOKSYSTEM_RECORD_H
#include <string>
#include <chrono>
using namespace std;

class Record {
    string userId;
    string copyId;
    time_t borrowTime;
    time_t returnTime;
public:
    Record(string userId, string copyId, time_t borrowTime, time_t returnTime);
    Record();
    ~Record();
    string getUserId()const;
    string getCopyId()const;
    time_t getBorrowTime()const;
    time_t getReturnTime()const;
    void setUserId(string userId);
    void setCopyId(string copyId);
    void setBorrowTime(time_t borrowTime);
    void setReturnTime(time_t returnTime);
};


#endif //AVL_BOOKSYSTEM_RECORD_H