#include <iostream>
#include <vector>
using namespace std;

class  quicksort {
public:
    static void quickSort(vector<int>& arr) {
        if (arr.size() <= 1) return;
        quickSort(arr, 0, arr.size() - 1);
    }
    static void swap(int& a, int& b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    static void quickSort(vector<int>& arr, int start, int end) {
        // 如果区域内的数字少于1个，则退出递归
        if (start >= end) { 
            return;
        }
        // 将数组分区，并获得中间值的下标
        for (auto& a : arr) {
            cout << a << " ";
        }
        cout << endl;
        // cout << "check1" << endl;
        int middle = partition(arr, start, end);
        // cout << "check2" << endl;
        if (middle == -1) {
            cout << "fenqu wei kong";
            return;
        }
        //对左边区域进行快排
        quickSort(arr, start, middle - 1); 
        //对右边区域进行快排
        quickSort(arr, middle + 1, end); 
    }
    static int partition(vector<int>& arr, int start, int end) {
        if (start > end ) return -1; 
        int privotIndex = start;
        start = privotIndex + 1;
        // 若end <= start 跳过下面的循环
        // end移动到小于轴的位置
        while (end > start) {
            while (end > start && arr[end] >= arr[privotIndex]) {
                --end;
            }
            // start移动到大于轴的位置
            while (end > start && arr[start] < arr[privotIndex]) {
                ++start;
            }
            if (start < end) {
                swap(arr[start], arr[end]);
                ++start;
                --end;
            } else if (start == end){
/**
 * 这里有一个很容易犯错的点：
 * 1. 首先我们是把一个一个的区间逐步逐步地内缩，就像是从大圆环中一次往内缩，确保圆环左边位置的数值都小于基准值，右边位置的数值都大于基准值
 * 2. 所以左右指针相遇的情况有三种，在左右边界相遇，在中间的位置相遇
 *      1）. 如果是在中间位置相遇，那么该位置的值必然小于基准值，因为右指针是一直向左移动直至遇到小于基准值的数
 *      2) . 如果是在最左边和最右边的位置的，那么可能大于或等于基准值，如果大于或等于基准值，那么就说明此时的区间可以与圆环右边的区间进行合并，
 *           然后就要去找上一个区间，也就是左指针要向左移动一步，若左指针与基准位置没有重合，则可以进行交换
 *    . . .
 *   . .  . .
 *  . .    . .
 *   . .  . .
 *     . . .
 */
                if (arr[start] < arr[privotIndex]) {
                    swap(arr[start], arr[privotIndex]);
                    privotIndex = start;
                    break;
                } else {
                    --start;
                    // --end;
                    if (start > privotIndex)  {
                        swap(arr[start], arr[privotIndex]);
                        privotIndex = start;
                    } else {
                        // 此时这种情况就是左指针和基准值重合，
                        /**
                         * 本来左右指针本来是相遇的，但是由于上面把start--了，这是end > start的
                         * 所以这里要手动break退出循环，或者上面--start的时候把end也减了
                         * 
                         */
                        privotIndex = start;
                    }
                    break;
                }
            }

        }
        return privotIndex;
    }
    static int partition2(vector<int>& arr, int start, int end) {
        // 取第一个数为基数
        int privot = arr[start];
        // 从第2个数开始分区
        int left = start + 1;
        // 右边界
        int right = end;
        // left, right相遇时退出循环
        while (left < right) {
            // 找到第一个大于基数的位置
            while (left < right && arr[left] <= privot) left++;
            // 找到第一个小于基数的位置
            while(left < right && arr[right] >= privot) right--;
            if (left < right) {
                swap(arr[left], arr[right]);
                left++;
                right--;
            }
        }
        // 如果left和right相等，单独比较arr[right]和privot
    }
};

int main() {
    quicksort obj;
    vector<int> arr = {10,9,8,5, 7,6,5,5,4,3,2,1};
    obj.quickSort(arr);
    for (auto& a : arr) {
        cout << a << " " ;
    }
    return 0;
}