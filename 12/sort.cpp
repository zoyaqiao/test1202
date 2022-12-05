#incldue "sort.h"
namespace stlSort {
    void vectorSort::quickSort(
            vector<int>& arr, 
            int& begin, int& end) {
        if (begin == end) {
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
                swap (arr[begin], arr[end]);;
            } else if (begin == end) {
                int coinIndex = begin;
                if (coinIndex == baseIndex) {
                    quickSort(arr, coninIndex + 1, baseEnd);
                } else {
                    quickSort(arr, baseIndex, coinIndex -1);
                    quickSort(arr, coinIndex + 1, baseEnd);
                }
            }
        }
    }

}
