#include "AVLTree.h"
#include "AVLNode.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//获取平衡因子
int AVLTree::getBalance(AVLNode *node) {
    if (node==nullptr) {
        return 0;
    }
    int leftHeight = (node->left != nullptr) ? node->left->height : 0;
    int rightHeight = (node->right != nullptr) ? node->right->height : 0;
    return leftHeight - rightHeight;
}

//左旋
AVLNode* AVLTree::leftRotate(AVLNode *node) {
    AVLNode* right = node->right;
    AVLNode* rightLeft = right->left;
    right->left=node;
    node->right=rightLeft;
    node->updateHeight();
    right->updateHeight();
    return right;
}

//右旋
AVLNode* AVLTree::rightRotate(AVLNode *node) {
    AVLNode* left = node->left;
    AVLNode* leftRight = left->right;
    left->right=node;
    node->left=leftRight;
    node->updateHeight();
    left->updateHeight();
    return left;
}

//清空树
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

//检查平衡树是否平衡
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

//插入结点
AVLNode* AVLTree::insert(AVLNode* node,const Book &book) {
    if (!node)return new AVLNode(book);

    if (node->book>book) {
        node->left=insert(node->left,book);
    } else if (node->book<book) {
        node->right=insert(node->right,book);
    }
    updateHeight(node);

    int balance = getBalance(node);
    //左左情况
    if (balance>1&&book<node->left->book) {
        return rightRotate(node);
    }
    //右右情况
    if (balance<-1&&book>node->right->book) {
        return leftRotate(node);
    }
    //左右情况
    if (balance>1&&book>node->left->book) {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    //右左情况
    if (balance<-1&&book<node->right->book) {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

//删除结点
AVLNode* AVLTree::remove(AVLNode* node,const string &bookId) {
    if (!node) return nullptr; //节点不存在，返回nullptr
    if (node->book.getId()>bookId) {
        node->left=remove(node->left,bookId);
    } else if (node->book.getId()<bookId) {
        node->right=remove(node->right,bookId);
    } else {
        //找到要删除的节点
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
            //有两个子节点
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

    //左左情况
    if (balance>1&&getBalance(node->left)>=0) {
        return rightRotate(node);
    }
    //左右情况
    if (balance>1&&getBalance(node->left)<0) {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    //右右情况
    if (balance<-1&&getBalance(node->right)<=0) {
        return leftRotate(node);
    }
    //右左情况
    if (balance<-1&&getBalance(node->right)>0) {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

//更新高度
void AVLTree::updateHeight(AVLNode* node) {
    if (!node) {
        return;
    }
    int leftHeight = (node->left != nullptr) ? node->left->height : 0;
    int rightHeight = (node->right != nullptr) ? node->right->height : 0;
    node->height = max(leftHeight, rightHeight) + 1;
}

//找到最小值结点
AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

//析构函数
AVLTree::~AVLTree() {
    clear(root);
}

//插入结点
void AVLTree::insert(const Book& book) {
    root=insert(root,book);
}

//删除结点
void AVLTree::remove(const string &bookId) {
    root=remove(root,bookId);
}

//查找结点
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

//中序遍历打印树，用于测试
void AVLTree::printTree() {
    cout<<"中序遍历打印树"<<endl;
    printTree(root);
}

//中序遍历打印树，用于测试
void AVLTree::printTree(AVLNode* node) {
    if (node==nullptr) {
        return;
    }
    printTree(node->left);
    cout<<node->book.getId()<<endl;
    printTree(node->right);
}

//获取根节点
AVLNode* AVLTree::getRoot() {
    return root;
}

//构建影子树，用于打印树形结构
AVLNode* AVLTree::buildShadowTree(AVLNode* t, int level, int& column) {
    AVLNode* newNode = nullptr;
    if (t != nullptr) {
        newNode = new AVLNode(t->book);
        AVLNode* newleft = buildShadowTree(t->left, level + 1, column);
        newNode->left = newleft;
        newNode->level = level;
        newNode->column = column;
        column++;
        AVLNode* newright = buildShadowTree(t->right, level + 1, column);
        newNode->right = newright;
        newNode->height = t->height;
    }
    return newNode;
}

//清空影子树
void AVLTree::clearShadowTree(AVLNode* shadowRoot) {
    if (shadowRoot == nullptr) {
        return;
    }
    clearShadowTree(shadowRoot->left);
    clearShadowTree(shadowRoot->right);
    delete shadowRoot;
}

//打印AVL树型结构
void AVLTree::printAVLTree() {
    cout<<"=================================="<<endl;
    cout<<"AVL树形结构："<<endl;
    cout<<"=================================="<<endl;
    if (root == nullptr) {
        cout<<"树为空"<<endl;
        cout<<"=================================="<<endl;
        return;
    }
    //构建影子树
    int column = 0;
    AVLNode* shadowRoot = buildShadowTree(root, 0, column);
    //找出最大的列号，用于确定输出宽度
    int maxColumn = column;
    //找出最大的层级
    int maxLevel = root->height - 1;
    //创建二维数组存储每个位置的节点id
    vector<vector<string>> grid(maxLevel + 1, vector<string>(maxColumn, "    "));
    //填充数组（用队列进行层次遍历）
    queue<AVLNode*> q;
    q.push(shadowRoot);
    while (!q.empty()) {
        AVLNode* node = q.front();
        q.pop();
        if (node != nullptr) {
            //将节点id放入对应的位置
            grid[node->level][node->column] = node->book.getId();
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }
    //打印数组
    for (int i = 0; i <= maxLevel; i++) {
        cout<<"第"<<(i+1)<<"层: ";
        for (int j = 0; j < maxColumn; j++) {
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    //清空影子树
    clearShadowTree(shadowRoot);
    cout<<"=================================="<<endl;
}