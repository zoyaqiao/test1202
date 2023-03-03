#include <iostream>
#include <vector>
using namespace std;

// 将两个有序数组合并成一个有序数组
/**算法思路：
 * 1. 先创建一个可以容纳两个数组元素的大数组
 * 2. 接着依次把较小的数写入到数组中
 * 3. 新数组元素的下标是旧数组元素的下标之和**/
static vector<int> merge(const vector<int>& a1, const vector<int>& a2) {
    // 创建新数组
    int len1 = a1.size();
    int len2 = a2.size();
    vector<int> a1a2(len1 + len2);
    // 创建两个移动指针
    int pa1 = 0, pa2 = 0;
    while (pa1 < len1 && pa2 < len2) {
        if (a1[pa1] <= a2[pa2]) {
            a1a2[pa1 + pa2] = a1[pa1];
            ++pa1;
        } else {
            a1a2[pa1 + pa2] = a2[pa2];
            ++pa2;
        }
    }
    while (pa1 < len1) {
        a1a2[pa2 + pa1] = a1[pa1];
        ++pa1;
    }
    while (pa2 < len2) {
        a1a2[pa2 + pa1] = a2[pa2];
        ++pa2;
    }
    return a1a2;
}

//**                正式开始归并排序                  **//

//1. 将数组拆分成有序数组 , 框架如下
static void mergeSort(vector<int>& arr) {
    if (arr.size() == 0) return;
    vector<int> result = mergeSort(arr, 0, arr.size() - 1);
    // 将结果拷贝到arr数组中
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = result[i];
    }
}

// 2. 对arr的[start, end]区间归并排序
static vector<int> mergeSort(vector<int>& arr, int start , int end) {
    // 只剩下一个数字，停止拆分，返回单个数字
    if (start == end) return {arr[start]};
    // 获取中间元素的位置
    int middle = (start + end) / 2;
    //拆分左边区域
    vector<int> left = mergeSort(arr, start, middle);

    // 拆分右边区域
    vector<int> right = mergeSort(arr, middle + 1, end);

    // 合并左边区域和右边区域
    return merge(left, right);

}

int main() {
    // vector<int> a1 = {1,2,3,4,5};
    // vector<int> a2 = {2, 3, 4, 7, 8};
    // vector<int> a3 = merge(a1, a2);
    vector<int> a1 = {5,4,3,5,4,6,3,7,1,2,4};
    mergeSort(a1);
    for (auto& a : a1) {
        cout << a << " ";
    }
    
    return 0;
}