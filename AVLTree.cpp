#include "AVLTree.h"
#include "AVLNode.h"
#include<iostream>
using namespace std;

int AVLTree::getBalance(AVLNode *node) {
    if (node==nullptr) {
        return 0;
    }
    int leftHeight = (node->left != nullptr) ? node->left->height : 0;
    int rightHeight = (node->right != nullptr) ? node->right->height : 0;
    return leftHeight - rightHeight;
}

AVLNode* AVLTree::leftRotate(AVLNode *node) {
    AVLNode* right = node->right;
    AVLNode* rightLeft = right->left;
    right->left=node;
    node->right=rightLeft;
    node->updateHeight();
    right->updateHeight();
    return right;
}

AVLNode* AVLTree::rightRotate(AVLNode *node) {
    AVLNode* left = node->left;
    AVLNode* leftRight = left->right;
    left->right=node;
    node->left=leftRight;
    node->updateHeight();
    left->updateHeight();
    return left;
}

AVLNode* AVLTree::LL(AVLNode *node) {
    return rightRotate(node);
}

AVLNode* AVLTree::RR(AVLNode *node) {
    return leftRotate(node);
}

AVLNode* AVLTree::LR(AVLNode *node) {
    node->left=leftRotate(node->left);
    return rightRotate(node);
}

AVLNode* AVLTree::RL(AVLNode *node) {
    node->right=rightRotate(node->right);
    return leftRotate(node);
}

void AVLTree::clear(AVLNode *node) {
    if (node==nullptr) {
        return;
    }
    AVLNode* right = node->right;
    AVLNode* left = node->left;
    delete node;
    clear(right);
    clear(left);
}

AVLNode* AVLTree::findParent(const string &bookId) const {
    AVLNode* node=root;
    AVLNode* parent=nullptr;
    while (node!=nullptr) {
        if (node->book.getId()==bookId) {
            return parent;
        } else if (node->book.getId()<bookId) {
            parent=node;
            node=node->right;
        } else {
            parent=node;
            node=node->left;
        }
    }
    return nullptr; // 节点不存在时返回nullptr
}

bool AVLTree::isBalanced(AVLNode *node) {
    if (node==nullptr) {
        return true;
    }
    int balance = getBalance(node);
    if (balance>1||balance<-1) {
        return false;
    }
    return isBalanced(node->left)&&isBalanced(node->right);
}

AVLNode* AVLTree::insert(AVLNode* node,const Book &book) {
    if (!node)return new AVLNode(book);

    if (node->book>book) {
        node->left=insert(node->left,book);
    } else if (node->book<book) {
        node->right=insert(node->right,book);
    }
    updateHeight(node);

    int balance = getBalance(node);
    if (balance>1&&book<node->left->book) {
        return rightRotate(node);
    }
    if (balance<-1&&book>node->right->book) {
        return leftRotate(node);
    }
    if (balance>1&&book>node->left->book) {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance<-1&&book<node->right->book) {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

AVLNode* AVLTree::remove(AVLNode* node,const string &bookId) {
    if (!node) return nullptr; // 节点不存在，返回nullptr

    if (node->book.getId()>bookId) {
        node->left=remove(node->left,bookId);
    } else if (node->book.getId()<bookId) {
        node->right=remove(node->right,bookId);
    } else {
        // 找到要删除的节点
        if (!node->left||!node->right) {
            AVLNode* temp=node->left?node->left:node->right;
            //没有子节点
            if (!temp) {
                temp=node;
                node=nullptr;
            } else {
                //有一个子节点
                *node=*temp;
            }
            delete temp;
        } else {
            // 有两个子节点
            AVLNode* temp= minValueNode(node->right);
            node->book=temp->book;
            node->right=remove(node->right,temp->book.getId());
        }
    }

    if (!node) {
        return node;
    }

    updateHeight(node);
    int balance = getBalance(node);

    // 左左情况
    if (balance>1&&getBalance(node->left)>=0) {
        return rightRotate(node);
    }
    // 左右情况
    if (balance>1&&getBalance(node->left)<0) {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    // 右右情况
    if (balance<-1&&getBalance(node->right)<=0) {
        return leftRotate(node);
    }
    // 右左情况
    if (balance<-1&&getBalance(node->right)>0) {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVLTree::updateHeight(AVLNode* node) {
    if (!node) {
        return;
    }
    int leftHeight = (node->left != nullptr) ? node->left->height : 0;
    int rightHeight = (node->right != nullptr) ? node->right->height : 0;
    node->height = max(leftHeight, rightHeight) + 1;
}

AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

AVLTree::~AVLTree() {
    clear(root);
}

AVLNode* AVLTree::search(const string &bookId) const {
    AVLNode* node=root;
    while (node!=nullptr) {
        if (node->book.getId()==bookId) {
            return node;
        } else if (node->book.getId()<bookId) {
            node=node->right;
        } else {
            node=node->left;
        }
    }
    return nullptr;
}

void AVLTree::printTree() {

}

void AVLTree::insert(const Book& book) {
    root=insert(root,book);
}

void AVLTree::remove(const string &bookId) {
    root=remove(root,bookId);
    cout << "成功删除图书"<< endl;
}

AVLNode* AVLTree::getRoot() {
    return root;
}