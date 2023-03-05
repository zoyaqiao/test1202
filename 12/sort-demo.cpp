#include <iostream>
#include <vector>
using namespace std;

void swap(int& a, int& b);

class baseSort {
public:
    virtual void sort(vector<int>& data) = 0;
    virtual ~baseSort(){};
};

class bubbleSort : public baseSort {
public:
    void sort(vector<int>& data);
};

class bubbleSort2 : public baseSort {
public:
    void sort(vector<int>& data);
};

class selectSort : public baseSort {
public:
    void sort(vector<int>& data);
};

class quickSort : public baseSort {
public:
    void sort(vector<int>& data);
    void sort(vector<int>& data, int begin, int end);
};

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void bubbleSort2::sort(vector<int>& data) {
    if (data.size() < 2) return;
    for (int i = 0; i < data.size() - 1; ++i) {
        bool swap_flag = false;
        int EndIndexOfUnswapedElem = data.size() -1;
        int swapIndex = -1;
        for (int j = 0; j < EndIndexOfUnswapedElem; ++j) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                swap_flag = true;
                swapIndex = j;
            }
        }
        if (!swap_flag) break;
        EndIndexOfUnswapedElem = swapIndex;
    }
}

void bubbleSort::sort(vector<int>& data) {
    bool flag = false;
    for (int i = 0; i < data.size() - 1; ++i) {
        for (int j = 0; j < data.size() - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                int tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
}

void selectSort::sort(vector<int>& data) {
    for (int i = 0; i < data.size() - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < data.size(); ++j) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        if (i != minIndex) {
            int tmp = data[i];
            data[i] = data[minIndex];
            data[minIndex] = tmp;
        }
    }
}

void quickSort::sort(vector<int>& data) {
    if (data.size() <= 1) {
        return;
    }
    sort(data, 0, data.size() - 1);
}
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void quickSort::sort(vector<int>& data, int begin, int end) {
    if (begin >= end) {
        return;
    }
    int baseVal = data[begin];
    int baseIndex = begin;
    int baseEnd = end;
    while (begin < end) {
        while (begin < end && data[end] >= baseVal) {
            --end;
        }
        while (begin < end && data[begin] <= baseVal) {
            ++begin;
        }
        if (begin < end) {
            swap(data[begin], data[end]);
        }
        if (begin == end) {
            int coinIndex = begin;
            if (data[coinIndex] < baseVal) {
                swap(data[coinIndex], data[baseIndex]);
            }
            sort(data, baseIndex, coinIndex - 1);
            sort(data, coinIndex + 1, baseEnd);
        }
    }
}

class factory {
public:
    virtual baseSort* createSort() = 0;
};

class bubbleFac : public factory {
public:
    baseSort* createSort() { return new bubbleSort(); }
};

class bubbleFac2 : public factory {
public:
    baseSort* createSort() { return new bubbleSort2(); }
};

class selectFac : public factory {
public:
    baseSort* createSort() { return new selectSort(); }
};

class quickFac : public factory {
public:
    baseSort* createSort() { return new quickSort(); }
};

int main() {
    vector<int> data = {42, 20, 17, 13, 28, 14, 23, 15};
    vector<int> data2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> data3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    // bubbleSort(data);
    // 选择排序
    // factory* fac = new selectFac();
    // baseSort* ptr = fac->createSort();
    // ptr->sort(data);
    // for (auto&d : data) {
    //     cout << d << " ";
    // }
    // 快速排序
    // factory* fac_quick = new quickFac();
    // baseSort* ptr_sort = fac_quick->createSort();
    // ptr_sort->sort(data3);
    // for (auto& d : data3) {
    //     cout << d << " ";
    // }
    factory* fac_bubble2 = new bubbleFac2();
    baseSort* ptr_sort = fac_bubble2->createSort();
    ptr_sort->sort(data3);
    for (auto& d : data3) {
        cout << d << " ";
    }
};