#ifndef AVL_BOOKSYSTEM_BORROWSERVICE_H
#define AVL_BOOKSYSTEM_BORROWSERVICE_H
#include "../database/dao/BookCopyDAO.h"
#include "../database/dao/RecordDAO.h"
#include "../database/dao/UserDAO.h"

class BorrowService {
private:
    BookCopyDAO* bookCopyDAO;
    RecordDAO* recordDAO;
    UserDAO* userDAO;
    static int MAX_BORROW_COUNT;

public:
    explicit BorrowService(BookCopyDAO* bookCopyDAO,
                           RecordDAO* recordDAO,
                           UserDAO* userDAO);
    ~BorrowService();

    // 核心业务
    [[nodiscard]] bool borrowBook(const string& userId, const string& copyId) const;//借阅书本
    [[nodiscard]] bool returnBook(const string& userId, const string& copyId) const;//归还书本

    // 业务校验
    [[nodiscard]] bool canBorrow(const string& userId, const string& copyId) const;//是否可以借阅
    [[nodiscard]] bool canUserBorrowMore(const string& userId) const;//用户是否可以继续借阅
    [[nodiscard]] bool isCopyBorrowed(const string& copyId) const;//书本是否已借出
    [[nodiscard]] bool hasUserBorrowedCopy(const string& userId, const string& copyId) const;//用户是否有借阅该书本
    //[[nodiscard]] bool isUserBlacklisted(const string& userId) const;
    //bool hasOverdueBooks(const string& userId);//是否逾期

    // 查询类
    [[nodiscard]] vector<Record> getUserBorrowingRecords(const string& userId) const;//获取用户当前借阅的记录

    // 扩展
    bool renewBook(const string& userId, const string& copyId);//续借

    static void setMaxBorrowCount(int maxBorrowCount);//设置最大借阅数量
};



#endif //AVL_BOOKSYSTEM_BORROWSERVICE_H