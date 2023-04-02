#pragma once
#include <vector>
#include <stack>

typedef struct sortInfo_tag {
	int comparison;
	int exchange;
	uint64_t time;
	int other;
}sortInfo;

/* 1.ð������ */
std::vector<int>& sort_bubble(std::vector<int>& arr, sortInfo& info);
/* 2.ѡ������ */
std::vector<int>& sort_selection(std::vector<int>& arr, sortInfo& info);
/* 3.������˳ */
std::vector<int>& sort_insertion(std::vector<int>& arr, sortInfo& info);
/* 4.ϣ������ */
std::vector<int>& sort_shell(std::vector<int>& arr, sortInfo& info);
/* 5.�������� */
std::vector<int>& sort_quick(std::vector<int>& arr, sortInfo& info);
std::vector<int>& sort_quick2(std::vector<int>& arr, sortInfo& info);
std::vector<int>& sort_quick3(std::vector<int>& arr, sortInfo& info);
/* 6.������ */
std::vector<int>& sort_heap(std::vector<int>& arr, sortInfo& info);
/* 7.�鲢���� */
std::vector<int>& sort_merge(std::vector<int>& arr, sortInfo& info);
/* �������� */
std::vector<int>& sort_counting(std::vector<int>& arr, sortInfo& info);