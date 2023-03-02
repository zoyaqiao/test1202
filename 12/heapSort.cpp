
static void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

static void buildMaxHeap(vector<int>& arr, int len) {
    if (len <= 1) return;
    int size = len - 1;
    int endOfRootIndex = (size - 1) / 2;
    int leftChildIndex = 2 * endOfRootIndex + 1;
    if (leftChildIndex < size && leftChildIndex > endOfRootIndex)
        swap(arr[leftChildIndex], arr[endOfRootIndex]);

    int rightChildIndex = 2 * endOfRootIndex + 2;

    if (rightChildIndex < size && rightChildIndex > endOfRootIndex) 
        swap(arr[rightChildIndex], arr[endOfRootIndex]);
    buildMaxHeap(arr, len - 1);
}
void maxfyHeap(vector<int>& arr, int startIndex, int len) {
    if (startIndex >= len) return;
    int root = arr[startIndex];
    int leftChildIndex = 2 * root + 1;
    if (leftChildIndex >= len) return;
    int rightChildIndex = 2 * root + 2;
    if (rightChildIndex >= len) return;
    int maxChildIndex;
    if (arr[leftChildIndex] > arr[rightChildIndex]) {
        maxChildIndex = leftChildIndex;
    } else {
        maxChildIndex = rightChildIndex;
    }
    if (arr[maxChildIndex] > arr[root]) {
        swap(arr[maxChildIndex], arr[root]);
        maxfyHeap(arr, maxChildIndex, len);
    }
    
}

static void heapSort(vector<int>& arr) {
    int len = arr.size();
    if (len <= 1) {
        return;
    }
    // 初始化大顶堆
    buildMaxHeap(arr, len);
    // 取出堆顶的元素并进行调整
    for (int i = len - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        maxfyHeap(arr, 0, i);
    }
}