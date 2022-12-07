#include "sort.h"
#include <iostream>
namespace stlSort {
    void swap(int& a, int& b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    void vectorSort::quickSort(
            std::vector<int>& arr, 
            int begin, int end) {
        if (begin >= end) {
            return;
        }
        int baseIndex = begin;
        int baseVal = arr[begin];
        int baseEnd = end;
        while (begin < end) {
            while (begin < end && arr[end] >= baseVal) {
                --end;
            }
            while (begin < end && arr[begin] <= baseVal) {
                ++begin;
            }
            if (begin < end) {
                swap(arr[begin], arr[end]);
            }
            if (begin == end) {
                int coinIndex = begin;
                if (arr[coinIndex] < arr[baseIndex]) {
                    swap(arr[coinIndex], arr[baseIndex]);
                }
                quickSort(arr, baseIndex, coinIndex -1);
                quickSort(arr, coinIndex + 1, baseEnd);
            }
        }
    }
    void vectorSort::quickSort(std::vector<int>& arr) {
        int begin = 0;
        int end = arr.size() - 1;
        if (end <= 0) {
            return;
        }
        quickSort(arr, begin, end);
    }
}
