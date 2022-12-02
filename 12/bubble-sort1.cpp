#include <iostream>
#include <vector>
using namespace std;

class baseSort {
public:
    virtual void sort(vector<int>& data) = 0;
    virtual ~baseSort(){};
};

class bubbleSort : public baseSort {
public:
    void sort(vector<int>& data);
};

class selectSort : public baseSort {
public:
    void sort(vector<int>& data);
};

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

class factory {
public:
    virtual baseSort* createSort() = 0;
};

class bubbleFac : public factory {
public:
    baseSort* createSort() {
        return new bubbleSort();
    }
};

class selectFac : public factory {
public:
    baseSort* createSort() {
        return new selectSort();
    }
};

int main() {
    vector<int> data = {42, 20, 17, 13, 28, 14, 23, 15};
    // bubbleSort(data);
    factory* fac = new selectFac();
    baseSort* ptr = fac->createSort();
    ptr->sort(data);
    for (auto&d : data) {
        cout << d << " ";
    }
};