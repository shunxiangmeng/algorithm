// algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <random>
#include "sort.h"

#define CHECK 1

void printArray(const char* name, std::vector<int>& arr, sortInfo& info) {
    printf("%16s, time: %4lldms, compration: %8d, exchange: %8d, CE: %d\r\n", name, info.time, info.comparison, info.exchange, info.comparison+info.exchange);
#if 0
    int len = arr.size() < 50 ? arr.size() : 50;
    for (auto i = 0; i < len; i++) {
        printf(" %02d", arr[i]);
    }
    printf("\r\n\r\n");
#endif
}

void check(std::vector<int>& result, std::vector<int>& data) {
#if CHECK
    if (result.size() != data.size()) {
        printf("check error\r\n");
        return;
    }
    for (int i = 0; i < result.size(); i++) {
        if (data[i] != result[i]) {
            printf("check error, index:%d\r\n", i);
            return;
        }
    }
#endif
}

int main()
{
    sortInfo info{};
    int arrayLength = 10000;
    std::vector<int> arr(arrayLength);
    for (auto i = 0; i < arrayLength; i++) {
        arr[i] = arrayLength - i;
    }
    std::cout << "input data length: " << arrayLength << "\r\n\r\n";
    printArray("input data", arr, info);

    std::vector<int> input = arr;
    std::vector<int> &output = input;
    std::vector<int> result;
     
    input = arr;
    output = sort_bubble(input, info);
    printArray("bubble sort", output, info);
    result = output;

    input = arr;
    output = sort_selection(input, info);
    printArray("selection sort", output, info);
    check(result, output);

    input = arr;
    output = sort_insertion(input, info);
    printArray("insertion sort", output, info);
    check(result, output);

    input = arr;
    output = sort_shell(input, info);
    printArray("shell sort", output, info);
    result = output;
    check(result, output);

    input = arr;
    output = sort_quick(input, info);
    printArray("quick sort", output, info);
    check(result, output);

    input = arr;
    output = sort_quick2(input, info);
    printArray("quick2 sort", output, info);
    check(result, output);

    input = arr;
    output = sort_quick3(input, info);
    printArray("quick3 sort", output, info);
    check(result, output);

    input = arr;
    output = sort_heap(input, info);
    printArray("heap sort", output, info);
    check(result, output);

    input = arr;
    output = sort_merge(input, info);
    printArray("merge sort", output, info);
    check(result, output);

    input = arr;
    output = sort_counting(input, info);
    printArray("counting sort", output, info);
    check(result, output);

    for (int i = 0; i < 2; i++) {
        std::default_random_engine random(time(NULL));
        std::uniform_int_distribution<int> dis1(0, arrayLength);
        for (auto i = 0; i < arrayLength; i++) {
            arr[i] = dis1(random);
        }
        //printArray("input data", arr, info);
        printf("---------------------------------------------------------------------------------------\r\n");
        input = arr;
        output = sort_bubble(input, info);
        printArray("bubble sort", output, info);
        result = output;

        input = arr;
        output = sort_selection(input, info);
        printArray("selection sort", output, info);
        check(result, output);

        input = arr;
        output = sort_insertion(input, info);
        printArray("insertion sort", output, info);
        check(result, output);

        input = arr;
        output = sort_shell(input, info);
        printArray("shell sort", output, info);
        result = output;
        check(result, output);

        input = arr;
        output = sort_quick(input, info);
        printArray("quick sort", output, info);
        check(result, output);

        input = arr;
        output = sort_quick2(input, info);
        printArray("quick2 sort", output, info);
        check(result, output);

        input = arr;
        output = sort_quick3(input, info);
        printArray("quick3 sort", output, info);
        check(result, output);

        input = arr;
        output = sort_heap(input, info);
        printArray("heap sort", output, info);
        check(result, output);

        input = arr;
        output = sort_merge(input, info);
        printArray("merge sort", output, info);
        check(result, output);

        input = arr;
        output = sort_counting(input, info);
        printArray("counting sort", output, info);
        check(result, output);
    }
} 
