#include "generateSortTree.h"
namespace sorttree {

    TreeNode* Solution::generateTree() {
        int n = val;
        if (n < 1) {
            return nullptr;
        } 
        return generateTree(1, n);
    }
    TreeNode* Solution::generateTree(int start, int end) {
        if (start < end) {
            return nullptr;
        }
        int rootVal = (start + end) / 2;
        TreeNode* pLeft = generateTree(start, rootVal - 1);
        TreeNode* pRight = generateTree(rootVal + 1, end);

        TreeNode* curRoot = new TreeNode(rootVal);
        curRoot -> left = pLeft;
        curRoot -> right = pRight;

        return curRoot;
    }
}