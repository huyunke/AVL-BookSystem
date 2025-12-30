#include "AVLNode.h"
#include <algorithm>
using namespace std;

// AVLNode::~AVLNode() {
//     delete left;
//     delete right;
// }
//
// AVLNode* AVLNode::getLeft() {
//     return left;
// }
//
// AVLNode* AVLNode::getRight() {
//     return right;
// }
//
// int AVLNode::getHeight() {
//     return height;
// }
//
// Book AVLNode::getBook() {
//     return book;
// }
//
// void AVLNode::setLeft(AVLNode* left) {
//     this->left = left;
// }
//
// void AVLNode::setRight(AVLNode* right) {
//     this->right = right;
// }

void AVLNode::updateHeight() {
    int leftHeight = (left != nullptr) ? left->height : 0;
    int rightHeight = (right != nullptr) ? right->height : 0;
    height = max(leftHeight, rightHeight) + 1;
}