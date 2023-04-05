#include <chrono>
#include <random>
#include "sort.h"

/* 1.冒泡排序 */
void sort_bubble(std::vector<int> &arr, statistic& info) {
    int length = arr.size();
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (COMPARISON_INC arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                EXCHANGE_INC
            }
        }
    }
}
void sort_bubble2(std::vector<int> &arr, statistic& info) {
    int length = arr.size();
    int lastExchange = 0;
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        bool exchange = false;
        for (int i = left; i < right; i++) {
            if (COMPARISON_INC arr[i] > arr[i + 1]) {
                int temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                exchange = true;
                lastExchange = i;
                EXCHANGE_INC
            }
        }
        if (exchange == false) {
            return;
        }
        exchange = false;
        right = lastExchange;
        for (int i = right; i > left; i--) {
            if (COMPARISON_INC arr[i] < arr[i - 1]) {
                int temp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp;
                exchange = true;
                lastExchange = i;
                EXCHANGE_INC
            }
        }
        if (exchange == false) {
            return;
        }
        left = lastExchange;
    }
}

/* 2.选择排序 */
void sort_selection(std::vector<int>& arr, statistic& info) {
    int length = arr.size();
    for (int i = 0; i < length - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < length; j++) {
            if (COMPARISON_INC arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            EXCHANGE_INC
        }
    }
}
/* 3.插入排顺 */
void sort_insertion(std::vector<int>& arr, statistic& info) {
    for (int i = 1; i < arr.size(); i++) {
        int preIndex = i - 1;
        int current = arr[i];
        while (preIndex >= 0 && COMPARISON_INC current < arr[preIndex]) {
            arr[preIndex + 1] = arr[preIndex];
            preIndex--;
            EXCHANGE_INC
        }
        arr[preIndex + 1] = current;
    }
}

/* 4.希尔排序 */
void sort_shell(std::vector<int>& arr, statistic& info) {
    int length = arr.size();
    for (int gap = length / 2; gap > 0; gap = gap / 2) {
        for (int i = gap; i < length; i++) {
            int k = i;
            int current = arr[k];
            while (k - gap >= 0 && COMPARISON_INC current < arr[k - gap]) {
                arr[k] = arr[k - gap];
                k = k - gap;
                EXCHANGE_INC
            }
            arr[k] = current;
        }
    }
}

/* 5.归并排序 */
static void Merge(std::vector<int>& arr, int left, int mid, int right, statistic& info) {
    int n = right - left + 1;//临时数组存合并后的有序序列
    int* tmp = new int[n];
    int k = 0;
    int i = left;
    int j = mid + 1;
    while (i <= mid && j <= right) {
        if (COMPARISON_INC arr[i] < arr[j]) {
            tmp[k++] = arr[i++];
        }
        else {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    while (j <= right) {
        tmp[k++] = arr[j++];
    }
    for (int m = 0; m < n; ++m) {
        arr[left + m] = tmp[m];
    }
    delete[] tmp;//删掉堆区的内存
}

static void sortMerge(std::vector<int>& arr, int left, int right, statistic& info) {
    STACK_START
    if (left == right) {
        return;  //递归基是让数组中的每个数单独成为长度为1的区间
    }
    int mid = (left + right) / 2;
    sortMerge(arr, left, mid, info);
    sortMerge(arr, mid + 1, right, info);
    Merge(arr, left, mid, right, info);
    STACK_END
}

/* 5.归并排序 */
void sort_merge(std::vector<int>& arr, statistic& info) {
    sortMerge(arr, 0, arr.size() - 1, info);
}

/* 快速排序 */
static inline int partition(std::vector<int>& arr, int left, int right, statistic& info) {
    int pivot = arr[left]; /* 在最左边挖了一个坑，并临时保存坑中的元素，此时left指向这个坑 */
    while (left < right) {
        while (left < right && COMPARISON_INC arr[right] >= pivot) {
            right--; 
        }
        arr[left] = arr[right]; /* 从右往左，找到第一个小于基准的值，与坑进行互换 */
        while (left < right && COMPARISON_INC arr[left] <= pivot) {
            left++; 
        }
        arr[right] = arr[left]; /* 从左望右，找到第一个大于基数的值，与坑进行互换 */
        EXCHANGE_INC
    }
    arr[left] = pivot; /* 把基准填入最后一个坑 */
    return left;
}
static inline void quickSort(std::vector<int>& arr, int left, int right, statistic& info) {
    STACK_START
    if (left >= right) {
        return;
    }
    int position = partition(arr, left, right, info);
    if (position > left) {
        quickSort(arr, left, position - 1, info);
    }
    if (position < right) {
        quickSort(arr, position + 1, right, info);
    }
    STACK_END
}
//////////////////////
static inline int partition_mid(std::vector<int>& arr, int left, int right, statistic& info) {
    int mid = (right - left) / 2 + left;
    int temp = arr[left];
    arr[left] = arr[mid];
    arr[mid] = temp;

    int pivot = arr[left]; /* 在最左边挖了一个坑，并临时保存坑中的元素，此时left指向这个坑 */
    while (left < right) {
        while (left < right && COMPARISON_INC arr[right] >= pivot) {
            right--;
        }
        arr[left] = arr[right]; /* 从右往左，找到第一个小于基准的值，与坑进行互换 */
        while (left < right && COMPARISON_INC arr[left] <= pivot) {
            left++;
        }
        arr[right] = arr[left]; /* 从左望右，找到第一个大于基数的值，与坑进行互换 */
        EXCHANGE_INC
    }
    arr[left] = pivot; /* 把基准填入最后一个坑 */
    return left;
}
static inline void quickSort_mid(std::vector<int>& arr, int left, int right, statistic& info) {
    STACK_START
    if (left >= right) {
        return;
    }
    int position = partition_mid(arr, left, right, info);
    if (position > left) {
        quickSort_mid(arr, left, position - 1, info);
    }
    if (position < right) {
        quickSort_mid(arr, position + 1, right, info);
    }
    STACK_END
}
void sort_quick_mid(std::vector<int>& arr, statistic& info) {
    quickSort_mid(arr, 0, arr.size() - 1, info);
}

static inline int partition_random(std::vector<int>& arr, int left, int right, statistic& info) {
    std::default_random_engine random(time(NULL));
    std::uniform_int_distribution<int> dis1(left, right);
    int mid = dis1(random);
    int temp = arr[left];
    arr[left] = arr[mid];
    arr[mid] = temp;

    int pivot = arr[left]; /* 在最左边挖了一个坑，并临时保存坑中的元素，此时left指向这个坑 */
    while (left < right) {
        while (left < right && COMPARISON_INC arr[right] >= pivot) {
            right--;
        }
        arr[left] = arr[right]; /* 从右往左，找到第一个小于基准的值，与坑进行互换 */
        while (left < right && COMPARISON_INC arr[left] <= pivot) {
            left++;
        }
        arr[right] = arr[left]; /* 从左望右，找到第一个大于基数的值，与坑进行互换 */
        EXCHANGE_INC
    }
    arr[left] = pivot; /* 把基准填入最后一个坑 */
    return left;
}
static inline void quickSort_random(std::vector<int>& arr, int left, int right, statistic& info) {
    STACK_START
    if (left >= right) {
        return;
    }
    int position = partition_random(arr, left, right, info);
    if (position > left) {
        quickSort_random(arr, left, position - 1, info);
    }
    if (position < right) {
        quickSort_random(arr, position + 1, right, info);
    }
    STACK_END
}
void sort_quick_random(std::vector<int>& arr, statistic& info) {
    quickSort_random(arr, 0, arr.size() - 1, info);
}
/////////////////////////

/* 6.快速排序 */
void sort_quick(std::vector<int>& arr, statistic& info) {
    quickSort(arr, 0, arr.size() - 1, info);
}

void sort_quick2(std::vector<int>& arr, statistic& info) {
    std::stack<int> stack;
    int left = 0, right = arr.size() - 1;
    stack.push(right);
    stack.push(left);
    while (!stack.empty()) {
        left = stack.top(); stack.pop();
        right = stack.top(); stack.pop();
        if (left < right) 
        {
            int position = partition(arr, left, right, info);
            if (position > left) {
                stack.push(position - 1);
                stack.push(left);
            }
            if (position < right) {
                stack.push(right);
                stack.push(position + 1);
            }
        }
    }
}

void sort_quick3(std::vector<int>& arr, statistic& info) {
    //std::stack<int> stack;
    int stack[1024*10];
    int top = 0;
    int left = 0, right = arr.size() - 1;
    stack[top++] = right;
    stack[top++] = left;
    while (top > 0) {
        left = stack[--top];
        right = stack[--top];
        if (left < right)
        {
            int position = partition(arr, left, right, info);
            if (position > left) {
                stack[top++] = position - 1;
                stack[top++] = left;
            }
            if (position < right) {
                stack[top++] = right;
                stack[top++] = position + 1;
            }
        }
    }
}

/* 调整大顶堆 */
static inline void heapify(std::vector<int>& arr, int i, int length, statistic& info) {
    STACK_START
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < length && COMPARISON_INC arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < length && COMPARISON_INC arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        EXCHANGE_INC
        heapify(arr, largest, length, info);
    }
    STACK_END
}

/* 7.堆排序 */
void sort_heap(std::vector<int>& arr, statistic& info) {
    /* 构建大顶堆 */
    for (int i = arr.size() / 2 - 1; i >= 0; i--) {
        heapify(arr, i, arr.size(), info);
    }

    for (int i = arr.size() - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        EXCHANGE_INC
        heapify(arr, 0, i, info);
    }
}


/* 8.计数排序 */
void sort_counting(std::vector<int>& arr, statistic& info) {
    int max = arr[0];
    for (int i = 0; i < arr.size(); i++) {
        if (COMPARISON_INC arr[i] > max) {
            max = arr[i];
        }
    }

    std::vector<int> count(max + 1, 0);
    std::vector<int> tArr(arr);

    for (auto x : arr) {
        count[x]++;
    }
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    for (int i = arr.size() - 1; i >= 0; i--) {
        arr[count[tArr[i]] - 1] = tArr[i];
        count[tArr[i]]--;
    }
}

/* 9.桶排序 */
void sort_bucket(std::vector<int>& arr, statistic& info) {
    int max = arr[0];
    int min = arr[0];
    for (int i = 0; i < arr.size(); i++) {
        if (COMPARISON_INC arr[i] > max) {
            max = arr[i];
        }
        if (COMPARISON_INC arr[i] < min) {
            min = arr[i];
        }
    }

    int bucketCount = 10;
    int bucketSize = arr.size();
    int gap = (max - min) / bucketCount + 1;

    std::vector<std::vector<int>> bucket(bucketCount + 1);

    for (int i = 0; i < arr.size(); i++) {
        int index = (arr[i] / gap);
        bucket[index].push_back(arr[i]);
    }
    int k = 0;
    for (int i = 0; i < bucket.size(); i++) {
        statistic info0{};
        sort_shell(bucket[i], info0);
        info.comparison += info0.comparison;
        info.exchange += info0.exchange;

        for (int j = 0; j < bucket[i].size(); j++) {
            arr[k++] = bucket[i][j];
        }
    }
}

/* 10.基数排序 */
void sort_radix(std::vector<int>& arr, statistic& info) {
    /* 获取位数 */
    int max = arr[0];
    for (int i = 0; i < arr.size(); i++) {
        if (COMPARISON_INC arr[i] > max) {
            max = arr[i];
        }
    }
    int d = 1;
    int p = 10;
    while (max >= p) {
        max /= p;
        d++;
    }

    std::vector<int> temp(arr.size(), 0);
    std::vector<int> count(p);
    for (int radix = 1, i = 0; i <= d; i++, radix *= p) {
        for (int j = 0; j < p; j++) {   /* 清空计数器 */
            count[j] = 0;  
        }
        for (int j = 0; j < arr.size(); j++) {  /* 统计每个桶中的记录 */
            int index = (arr[j] / radix) % p;
            count[index]++;
        }
        for (int j = 1; j < p; j++) {
            count[j] = count[j] + count[j - 1];
        }
        for (int j = arr.size() - 1; j >= 0; j--) {
            int index = (arr[j] / radix) % p;
            temp[count[index] - 1] = arr[j];
            count[index]--;
        }
        for (int j = 0; j < arr.size(); j++) {
            arr[j] = temp[j];
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct {
    void(*pfn_sort)(std::vector<int>&, statistic&);
    const char* name;
}sort_item;

#define TEST_ITEM(x) {x, #x}

static sort_item s_sort_test[] = {
    //TEST_ITEM(sort_bubble),
    //TEST_ITEM(sort_bubble2),
    /*TEST_ITEM(sort_selection),*/
 /*   TEST_ITEM(sort_insertion),*/
    TEST_ITEM(sort_shell),
    TEST_ITEM(sort_merge),
    //TEST_ITEM(sort_quick),
    TEST_ITEM(sort_quick_mid),
    TEST_ITEM(sort_quick_random),
    //TEST_ITEM(sort_quick3),
    TEST_ITEM(sort_heap),
    
    TEST_ITEM(sort_counting),
    TEST_ITEM(sort_bucket),
    TEST_ITEM(sort_radix), 
};

void check(std::vector<int>& result, std::vector<int>& data) {
    if (result.size() != data.size()) {
        printf("check error\r\n");
        return;
    }
    for (int i = 0; i < result.size(); i++) {
        if (data[i] != result[i]) {
            printf("check error, index:%d data[%d]=%d result[%d]=%d\r\n", i, i, data[i], i, result[i]);
            return;
        }
    }
}

void sort(std::vector<int>& data, const char* testName) {
    printf("-------------------------------------------------------------------------------------------------\r\n");
    printf("dataLen:%d %s \r\n", data.size(), testName);
    std::vector<int> result;
    for (auto &it: s_sort_test) {
        std::vector<int> array = data;
        statistic statistic{it.name};
        uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        it.pfn_sort(array, statistic);
        uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        statistic.time = t1 - t0;
        printf("%-20s  time: %6lld, compration: %10lld, exchange: %10lld, CE: %10lld, stack: %8lld\r\n", 
            statistic.name, statistic.time, statistic.comparison, statistic.exchange, statistic.comparison + statistic.exchange, statistic.stackDepth);

        if (result.size() == 0) {
            result = array;
        }
        check(result, array);
    }
}

void sort_test() {
    int dataLengths[] = { 1000, 10000, 100000, 1000000 };
    for (auto dataLength : dataLengths) {
        std::vector<int> data(dataLength);

        for (auto i = 0; i < dataLength; i++) {
            data[i] = i;
        }
        sort(data, "顺序");

        for (auto i = 0; i < dataLength; i++) {
            data[i] = dataLength - i;
        }
        sort(data, "逆序");

        std::default_random_engine random(time(NULL));
        std::uniform_int_distribution<int> dis1(0, dataLength);
        for (auto i = 0; i < dataLength; i++) {
            data[i] = dis1(random);
        }
        sort(data, "random[0-dataLength]");

        std::default_random_engine random1(time(NULL));
        std::uniform_int_distribution<int> dis11(0, dataLength / 10);
        for (auto i = 0; i < dataLength; i++) {
            data[i] = dis11(random1);
        }
        sort(data, "random[0-dataLength/10]");

        std::default_random_engine random2(time(NULL));
        std::uniform_int_distribution<int> dis12(0, dataLength / 100);
        for (auto i = 0; i < dataLength; i++) {
            data[i] = dis12(random2);
        }
        sort(data, "random[0-dataLength/100]");

        for (auto i = 0; i < dataLength; i++) {
            data[i] = 0;
        }
        sort(data, "all 0");

        for (auto i = 0; i < dataLength / 2; i++) {
            data[i] = i;
            data[i + dataLength / 2] = dataLength / 2 - i;
        }
        sort(data, "0->max->1");
        printf("\r\n");
    }
}