cmake_minimum_required(VERSION 3.14)
project(AVL_BookSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVL_BookSystem main.cpp
        Book/Book.cpp
        Book/Book.h
        User.cpp
        User.h
        database/DatabaseOperator.cpp
        database/DatabaseOperator.h
        database/dao/BookDAO.cpp
        database/dao/BookDAO.h
        database/dao/UserDAO.cpp
        database/dao/UserDAO.h
        Book/BookCopy.cpp
        Book/BookCopy.h
        database/dao/BookCopyDAO.cpp
        database/dao/BookCopyDAO.h
        utils/PasswordUtils.cpp
        utils/PasswordUtils.h
        database/dao/RecordDAO.cpp
        database/dao/RecordDAO.h
        Record.cpp
        Record.h
        utils/TxtToDatabaseWriter.cpp
        utils/TxtToDatabaseWriter.h
        database/DatabaseInitializer.cpp
        database/DatabaseInitializer.h
        service/borrowService.cpp
        service/borrowService.h
        service/InventoryService.cpp
        service/InventoryService.h
        service/UserService.cpp
        service/UserService.h
        service/SearchService.cpp
        service/SearchService.h
)

# 添加测试程序
add_executable(test_database_init
        database/DatabaseOperator.cpp
        database/DatabaseOperator.h
        database/DatabaseInitializer.cpp
        database/DatabaseInitializer.h
        database/dao/UserDAO.cpp
        database/dao/UserDAO.h
        database/dao/BookCopyDAO.cpp
        database/dao/BookCopyDAO.h
        database/dao/RecordDAO.cpp
        database/dao/RecordDAO.h
        Book/Book.cpp
        Book/Book.h
        Book/BookCopy.cpp
        Book/BookCopy.h
        User.cpp
        User.h
        Record.cpp
        Record.h
        utils/PasswordUtils.cpp
        utils/PasswordUtils.h
)

# 链接Crypto++库到主程序
target_link_libraries(AVL_BookSystem PRIVATE cryptopp)

# 链接Crypto++库到测试程序
target_link_libraries(test_database_init PRIVATE cryptopp)

# 添加简单的数据库初始化程序（不依赖DAO）
add_executable(simple_db_init
        database/DatabaseOperator.cpp
        database/DatabaseOperator.h
        database/DatabaseInitializer.cpp
        database/DatabaseInitializer.h
)
