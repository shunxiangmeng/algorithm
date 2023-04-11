#pragma once
#include <vector>
#include <stack>

typedef struct {
	const char* name;
	int64_t comparison;
	int64_t exchange;
	double utime;
	double stime;
	int *stackStart;
	int *stackStop;
}statistic;

#define STATISITIC_ON

#ifdef STATISITIC_ON
#define COMPARISON_INC ++info.comparison&&
#define EXCHANGE_INC ++info.exchange;
#define STACK_COUNT     int p = 0;                                     \
						if (info.stackStart == nullptr) {              \
							info.stackStart = info.stackStop = &p;     \
						}                                              \
						if (&p < info.stackStop) {                     \
							info.stackStop = &p;                       \
						}

#else
#define COMPARISON_INC
#define EXCHANGE_INC
#define STACK_COUNT
#endif

void sort_test();