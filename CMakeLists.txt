cmake_minimum_required(VERSION 3.14)
project(AVL_BookSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVL_BookSystem main.cpp
        Book/Book.cpp
        Book/Book.h
        User.cpp
        User.h
        AVLNode.cpp
        AVLNode.h
        AVLTree.cpp
        AVLTree.h
        Print.cpp
        Print.h
        FileOperator.cpp
        FileOperator.h
        BookBorrowInfo.cpp
        BookBorrowInfo.h
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
)

# 链接Crypto++库到主程序
target_link_libraries(AVL_BookSystem PRIVATE cryptopp)
