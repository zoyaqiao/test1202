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
    
    vector<int> Solution::traversal(TreeNode* root, std::string& flag) {
        vector<int> res;
        if (nullptr == root) {
            return res;
        }
        switch (flag) {
            case "前序" :
                preTraversal(root, res);
                break
            case "中序":
                inorderTraversal(root, res);
                break;
            case "后序"
                backTraversal(root, res);
                break;
        }
        return res;
    }
        // 前序遍历二叉搜索树
    void Solution::preTraversal(TreeNode* root, vector<int>& val) {
        if (root) {
            val.emplace_back(root -> val);
            preTraversal(root -> left, val);
            preTraversal(root -> right, val);
        }
    }
    // 中序遍历二叉搜索树
    void Solution::inorderTraversal(TreeNode* root, vector<int>& val) {
        if (root) {
            inorderTraversal(root -> left, val);
            val.emplace_back(root -> val);
            inorderTraversal(root -> right, val);
        }
    }
    // 后序遍历二叉搜索树
    void Solution::backTraversal(TreeNode* root, vector<int>& val) {
        if (root) {
            backTraversal(root -> left, val);
            backTraversal(root -> right, val);
            val.emplace_back(root -> val);
        }
    }










}