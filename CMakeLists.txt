cmake_minimum_required(VERSION 4.1)
project(AVL_BookSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVL_BookSystem main.cpp
        Book.cpp
        include/Book.h
        User.cpp
        include/User.h
        AVLNode.cpp
        include/AVLNode.h
        AVLTree.cpp
        include/AVLTree.h
        Print.cpp
        include/Print.h
        FileOperator.cpp
        include/FileOperator.h
        BookBorrowInfo.cpp
        include/BookBorrowInfo.h
)
