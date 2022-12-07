#include "generateSortTree.h"
#include "sort.h"

#include <iostream>
#include <vector>
using namespace std;
void testTree () {
    sorttree::Solution* ptr = new sorttree::Solution(5);
    sorttree::TreeNode* root = ptr->generateTree();
    // 深度遍历搜索二叉树
    string flag = "中序";
    vector<int> res = ptr -> traversal(root, flag);
    for (auto& r : res) {
        cout << r << " " ;
    }
}

void testSort() {
    stlSort::sort* prt = new stlSort::vectorSort();
    const int num = 10;
    std::vector<int> data;
    srand(unsigned(time(0)));
    for (int i = 0; i < num; ++i) {
        int val = rand() % 100;
        data.emplace_back(val);
    }
    for (auto& r : data) {
        cout << r << " " ;
    } 
    cout << endl; 
    // std::vector<int> data = {5, 4, 2, 1, 3};
    prt->quickSort(data);
    for (auto& r : data) {
        cout << r << " " ;
    }    
}

int main(int argc, const char* argv[]) {
    testSort();
    return 0;
}