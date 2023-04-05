#pragma once
#include <vector>
#include <stack>

typedef struct {
	const char* name;
	int64_t comparison;
	int64_t exchange;
	int64_t stackDepth;
	int64_t count;
	uint64_t time;
}statistic;

#define STATISITIC_ON

#ifdef STATISITIC_ON
#define COMPARISON_INC ++info.comparison&&
#define EXCHANGE_INC ++info.exchange;
#define STACK_START {++info.count; if (info.count > info.stackDepth) {info.stackDepth = info.count;}}
#define STACK_END --info.count;
#else
#define COMPARISON_INC
#define EXCHANGE_INC
#define STACK_START
#define STACK_END
#endif

void sort_test();