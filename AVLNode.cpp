#include "AVLNode.h"
#include <algorithm>
using namespace std;

//更新节点高度
void AVLNode::updateHeight() {
    int leftHeight = (left != nullptr) ? left->height : 0;
    int rightHeight = (right != nullptr) ? right->height : 0;
    height = max(leftHeight, rightHeight) + 1;
}