cmake_minimum_required(VERSION 4.1)
project(AVL_BookSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVL_BookSystem main.cpp
        Book.cpp
        Book.h
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
)
