#ifndef GENERATE_SORT_TREE_H
#define GENERATE_SORT_TREE_H
#include <iostream>
namespace sorttree {
    using namespace std;

    /**
     * 根据指定的序列生成一棵二叉搜索树
     * 指定的序列为[1,5]
     * 
     */
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;

        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    };

    class Solution {
    public:
        Solution(int data)
            :val(data){}
        // 生成二叉搜索树
        TreeNode* generateTree();
        TreeNode* generateTree(int start, int end);
    private:
        int val;
    };

}
#endif