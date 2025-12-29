#include <iostream>
#include "include/Print.h"
#include "include/AVLTree.h"
#include "include/Book.h"
#include "include/BookManager.h"
#include "include/User.h"
#include "include/FileOperator.h"
using namespace std;

int main() {
    AVLTree* tree=new AVLTree();
    FileOperator::readBookFile("book.txt",tree);

    //用户：
    //登录成功后，如果该用户有书本逾期，提醒用户书本逾期（不知道加不加）

    //归还图书：如果id正确将书本信息从用户的借阅信息中删除
    //根据id查找到书本，并更改图书的状态
    //如果id不正确输出提示信息

    //借阅图书：如果id正确将书本信息添加到用户的借阅信息中
    //根据id查找到书本，并更改图书的状态
    //如果id不正确输出提示信息

    //查询图书：根据id查找到书本，并输出书本信息（包括是否被借阅）
    //如果id不正确输出提示信息

    //查询借阅信息：输出用户的借阅信息

    //修改密码：修改用户的密码
    //退出：退出系统
}