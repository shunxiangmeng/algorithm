#include <chrono>
#include "sort.h"

std::vector<int>& sort_bubble(std::vector<int> &arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = {0, 0, 0};
	int length = arr.size();
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			if (++info.comparison && arr[j] > arr[j + 1]) {
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
				info.exchange++;
			}
		}
	}
	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}

std::vector<int>& sort_bubble2(std::vector<int>& arr, sortInfo& info) {
	int length = arr.size();
	for (int i = length - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return arr;
}

std::vector<int>& sort_selection(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };
	int length = arr.size();
	int minIndex;
	for (int i = 0; i < length - 1; i++) {
		minIndex = i;
		for (int j = i + 1; j < length; j++) {
			if (++info.comparison && arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			int temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
			info.exchange++;
		}
	}
	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}

std::vector<int>& sort_insertion(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };
	int length = arr.size();
	int preIndex, current;
	for (int i = 1; i < length; i++) {
		preIndex = i - 1;
		current = arr[i];
		while (preIndex >= 0 && ++info.comparison && current < arr[preIndex]) {
			arr[preIndex + 1] = arr[preIndex];
			preIndex--;
			info.exchange++;
		}
		arr[preIndex + 1] = current;
	}
	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}

std::vector<int>& sort_shell(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };
	int length = arr.size();
	for (int gap = length / 2; gap > 0; gap = gap / 2) {
		for (int i = gap; i < length; i++) {
			int k = i;
			int current = arr[k];
			while (k - gap >= 0 && ++info.comparison && current < arr[k - gap]) {
				arr[k] = arr[k - gap];
				k = k - gap;
				info.exchange++;
			}
			arr[k] = current;
		}
	}
	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}


/* 快速排序 */
static inline int partition(std::vector<int>& arr, int left, int right, sortInfo& info) {
	int pivot = arr[left]; /* 在最左边挖了一个坑，并临时保存坑中的元素，此时left指向这个坑 */
	while (left < right) {
		while (left < right && ++info.comparison && arr[right] >= pivot) {
			right--; 
		}
		arr[left] = arr[right]; /* 从右往左，找到第一个小于基准的值，与坑进行互换 */
		while (left < right && ++info.comparison && arr[left] <= pivot) {
			left++; 
		}
		arr[right] = arr[left]; /* 从左望右，找到第一个大于基数的值，与坑进行互换 */
		info.exchange++;
	}
	arr[left] = pivot; /* 把基准填入最后一个坑 */
	return left;
}
static inline void quickSort(std::vector<int>& arr, int left, int right, sortInfo& info) {
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

std::vector<int>& sort_quick(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };
	quickSort(arr, 0, arr.size() - 1, info);
	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}

std::vector<int>& sort_quick2(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };

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

	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}

std::vector<int>& sort_quick3(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };

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

	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}

/* 调整大顶堆 */
static inline void heapify(std::vector<int>& arr, int i, int length, sortInfo& info) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < length && ++info.comparison && arr[left] > arr[largest]) {
		largest = left;
	}
	if (right < length && ++info.comparison && arr[right] > arr[largest]) {
		largest = right;
	}
	if (largest != i) {
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		info.exchange++;
		heapify(arr, largest, length, info);
	}
}

std::vector<int>& sort_heap(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };

	/* 构建大顶堆 */
	for (int i = arr.size() / 2 - 1; i >= 0; i--) {
		heapify(arr, i, arr.size(), info);
	}

	for (int i = arr.size() - 1; i > 0; i--) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		info.exchange++;
		heapify(arr, 0, i, info);
	}


	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}

static void Merge(std::vector<int>& arr, int l, int q, int r, sortInfo& info) {
	int n = r - l + 1;//临时数组存合并后的有序序列
	int* tmp = new int[n];
	int i = 0;
	int left = l;
	int right = q + 1;
	while (left <= q && right <= r) {
		tmp[i++] = arr[left] <= arr[right] ? arr[left++] : arr[right++];
		info.comparison++;
	}
	while (left <= q)
		tmp[i++] = arr[left++];
	while (right <= r)
		tmp[i++] = arr[right++];
	for (int j = 0; j < n; ++j)
		arr[l + j] = tmp[j];
	delete[] tmp;//删掉堆区的内存
}

static void sortMerge(std::vector<int>& arr, int l, int r, sortInfo& info) {
	if (l == r)
		return;  //递归基是让数组中的每个数单独成为长度为1的区间
	int q = (l + r) / 2;
	sortMerge(arr, l, q, info);
	sortMerge(arr, q + 1, r, info);
	Merge(arr, l, q, r, info);
}

std::vector<int>& sort_merge(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };

	sortMerge(arr, 0, arr.size() - 1, info);

	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}



std::vector<int>& sort_counting(std::vector<int>& arr, sortInfo& info) {
	uint64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info = { 0, 0, 0 };

	int max = arr[0];
	for (int i = 0; i < arr.size(); i++) {
		if (++info.comparison && arr[i] > max) {
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

	uint64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	info.time = t1 - t0;
	return arr;
}