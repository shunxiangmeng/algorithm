#include <chrono>
#include <random>
#include "sort.h"
#ifndef _WIN32
#include <sys/times.h>
#include <unistd.h>
#endif
#include <map>
#include <unordered_map>
#include <string>

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
void sort_selection2(std::vector<int>& arr, statistic& info) {
    for (int left = 0, right = arr.size() - 1; left < right; left++, right--) {
        int minIndex = left;
        int maxIndex = right;
        for (int i = left; i <= right; i++) {
            if (COMPARISON_INC arr[i] < arr[minIndex]) {
                minIndex = i;
            }
            if (COMPARISON_INC arr[i] > arr[maxIndex]) {
                maxIndex = i;
            }
        }
        if (minIndex != left) {
            int temp = arr[left];
            arr[left] = arr[minIndex];
            arr[minIndex] = temp;
            EXCHANGE_INC
        }
        if (maxIndex == left) {  //先交换left，需要考虑最大值就在left的情况
            maxIndex = minIndex;
        }
        if (maxIndex != right) {
            int temp = arr[right];
            arr[right] = arr[maxIndex];
            arr[maxIndex] = temp;
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
            preIndex = preIndex - 1;
            EXCHANGE_INC
        }
        arr[preIndex + 1] = current;
    }
}

/* 4.希尔排序 */
void sort_shell(std::vector<int>& arr, statistic& info) {
    for (int gap = arr.size() / 2; gap > 0; gap = gap / 2) {
        for (int i = gap; i < arr.size(); i++) {
            int preIndex = i - gap;
            int current = arr[i];
            while (preIndex >= 0 && COMPARISON_INC current < arr[preIndex]) {
                arr[preIndex + gap] = arr[preIndex];
                preIndex = preIndex - gap;
                EXCHANGE_INC
            }
            arr[preIndex + gap] = current;
        }
    }
}

static inline void sort_insertion_gap(std::vector<int>& arr, int gap, statistic& info) {
    for (int i = gap; i < arr.size(); i++) {
        int preIndex = i - gap;
        int current = arr[i];
        while (preIndex >= 0 && COMPARISON_INC current < arr[preIndex]) {
            arr[preIndex + gap] = arr[preIndex];
            preIndex = preIndex - gap;
            EXCHANGE_INC
        }
        arr[preIndex + gap] = current;
    }
}
void sort_shell22(std::vector<int>& arr, statistic& info) {
    int gap = 0;
    for (gap = arr.size() / 2; gap > 0; gap = int(gap*1.0 / 2.2)) {
        sort_insertion_gap(arr, gap, info);
    }
    if (gap != 1) {
        sort_insertion_gap(arr, 1, info);
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
    STACK_COUNT
    if (left == right) {
        return;  //递归基是让数组中的每个数单独成为长度为1的区间
    }
    int mid = (left + right) / 2;
    sortMerge(arr, left, mid, info);
    sortMerge(arr, mid + 1, right, info);
    Merge(arr, left, mid, right, info);
}

/* 5.归并排序 */
void sort_merge(std::vector<int>& arr, statistic& info) {
    sortMerge(arr, 0, arr.size() - 1, info);
}

static inline int partition(std::vector<int>& arr, int left, int right, statistic& info) {
    uint64_t t = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int mid = t % (right - left) + left;
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
static inline void quickSort(std::vector<int>& arr, int left, int right, statistic& info) {
    STACK_COUNT
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
}

/* 6.快速排序 */
void sort_quick(std::vector<int>& arr, statistic& info) {
    quickSort(arr, 0, arr.size() - 1, info);
}
/*使用迭代替换递归方式的快速排序, 问题是stack数组开多大呢*/
void sort_quick_stack(std::vector<int>& arr, statistic& info) {
    //std::stack<int> stack;
    int stack[1024 * 10] = { 0 };
    int top = 0;
    int left = 0, right = arr.size() - 1;
    stack[top++] = right;
    stack[top++] = left;
    while (top > 0) {
        left = stack[--top];
        right = stack[--top];
        if (left < right) {
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
    STACK_COUNT
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

    int needMemory = count.capacity() * sizeof(int);
    needMemory += (tArr.capacity() * sizeof(int));
    info.stackStart = (int*)(needMemory);

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
    TEST_ITEM(sort_bubble2),
    TEST_ITEM(sort_selection),
    TEST_ITEM(sort_insertion),
    //TEST_ITEM(sort_shell),
    TEST_ITEM(sort_shell22),
    TEST_ITEM(sort_merge),
    TEST_ITEM(sort_quick),
    TEST_ITEM(sort_heap),
    
    TEST_ITEM(sort_counting),
    TEST_ITEM(sort_bucket),
    TEST_ITEM(sort_radix), 
};

void check(std::vector<int>& data) {
    for (int i = 1; i < data.size(); i++) {
        if (data[i] < data[i - 1]) {
            printf("check error, data[%d]=%d < data[%d]=%d\r\n", i, data[i], i - 1, data[i - 1]);
            return;
        }
    }
}

std::map<std::string, std::vector<statistic>> g_statistics;
void sort(std::vector<int>& data, const std::string testName) {
    printf("-----------------------------------------------------------------------------------------------------------\r\n");
    printf("dataLen:%llu %s \r\n", data.size(), testName.c_str());

    for (auto &it: s_sort_test) {
        std::vector<int> array = data;
        statistic statistic{it.name};
        statistic.utime = -1;

        std::string tName(std::to_string(data.size()));
        tName = tName + " " + std::string(it.name);

        if (data.size() >= 1000000) {
            std::string name(it.name);
            if (name == "sort_bubble" || name == "sort_bubble2" || name == "sort_selection" || name == "sort_insertion") {
                g_statistics[tName].push_back(statistic);
                continue;
            }
        }

        if (data.size() >= 1000000) {
            std::string name(it.name);
            if (name == "sort_quick" && testName == "all 0") {
                g_statistics[tName].push_back(statistic);
                continue;
            }
        }

        #ifdef _WIN32
        uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        #else
        static long clocktick = sysconf(_SC_CLK_TCK);
        struct tms t0{};
        times(&t0);
        #endif

        it.pfn_sort(array, statistic);

        #ifdef _WIN32
        uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        statistic.utime = (t1 - t0) * 1.0 / 1000;
        printf("%-20s  time: %6.3f,  compration: %10lld, exchange: %10lld, stack: %8lld\r\n",
            statistic.name, statistic.utime, statistic.comparison, statistic.exchange, int64_t(statistic.stackStart - statistic.stackStop));
        #else
        struct tms t1{};
        times(&t1);
        statistic.utime = (t1.tms_utime - t0.tms_utime) * 1.0 / clocktick;
        statistic.stime = (t1.tms_stime - t0.tms_stime) * 1.0 / clocktick;
        printf("%-20s  utime: %6.3f, stime: %3.3f, compration: %10lld, exchange: %10lld, stack: %8lld\r\n",
            statistic.name, statistic.utime, statistic.stime, statistic.comparison, statistic.exchange, statistic.stackDepth);
        #endif
        
        check(array);

        g_statistics[tName].push_back(statistic);
    }
}

void sort_test() {
    int dataLengths[] = { 10000, 100000, 1000000, 10000000, 100000000 };
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

        for (auto i = 0; i < dataLength; i++) {
            data[i] = 0;
        }
        sort(data, "all 0");

        for (auto i = 0; i < dataLength / 2; i++) {
            data[i] = i;
            data[i + dataLength / 2] = dataLength / 2 - i;
        }
        sort(data, "0->max->1");

        std::default_random_engine random(time(NULL));
        std::uniform_int_distribution<int> dis1(0, dataLength);
        for (auto i = 0; i < dataLength; i++) {
            data[i] = dis1(random);
        }
        sort(data, "random[0-dataLen]");

        if (dataLength > 10) {
            std::default_random_engine random(time(NULL));
            std::uniform_int_distribution<int> dis1(0, dataLength / 10);
            for (auto i = 0; i < dataLength; i++) {
                data[i] = dis1(random);
            }
            sort(data, "random[0-dataLen/10]");
        }

        if (dataLength > 100) {
            std::default_random_engine random(time(NULL));
            std::uniform_int_distribution<int> dis1(0, dataLength / 100);
            for (auto i = 0; i < dataLength; i++) {
                data[i] = dis1(random);
            }
            sort(data, "random[0-dataLen/100]");
        }

        if (dataLength > 1000) {
            std::default_random_engine random(time(NULL));
            std::uniform_int_distribution<int> dis1(0, dataLength / 1000);
            for (auto i = 0; i < dataLength; i++) {
                data[i] = dis1(random);
            }
            sort(data, "random[0-dataLen/1000]");
        }

        printf("\r\n");
    }

    printf(".......................\r\n");


    for (auto& it : g_statistics) {
        printf("%s\r\n", it.first.c_str());  //数据类型
        printf("  |");
        for (int i = 0; i < it.second.size(); i++) {
            if (i == it.second.size() - 1) {
                printf("%0.3f", it.second[i].utime);
            } else {
                printf("%0.3f<br>", it.second[i].utime);
            }
        }

        /*printf("|");
        for (int i = 0; i < it.second.size(); i++) {
            if (i == it.second.size() - 1) {
                printf("%lld", it.second[i].comparison);
            }
            else {
                printf("%lld<br>", it.second[i].comparison);
            }
        }

        printf("|");
        for (int i = 0; i < it.second.size(); i++) {
            if (i == it.second.size() - 1) {
                printf("%lld", it.second[i].exchange);
            }
            else {
                printf("%lld<br>", it.second[i].exchange);
            }
        }

        printf("|");
        for (int i = 0; i < it.second.size(); i++) {
            if (i == it.second.size() - 1) {
                printf("%lld", it.second[i].stackStart - it.second[i].stackStop);
            }
            else {
                printf("%lld<br>", it.second[i].stackStart - it.second[i].stackStop);
            }
        }
        */
        printf("| \r\n\r\n");
    }
    printf(".......................\r\n");
}