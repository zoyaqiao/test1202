#include "generateSortTree.h"

int main(int argc, const char* argv[]) {
    sorttree::Solution* ptr = new sorttree::Solution(5);
    sorttree::TreeNode* root = ptr->generateTree();
    // 深度遍历搜索二叉树
    vector<int> res = ptr -> traversal(root);
    for (auto& r : res) {
        cout << r << " " ;
    }
    
}