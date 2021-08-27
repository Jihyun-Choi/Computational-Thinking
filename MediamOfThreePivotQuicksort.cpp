#include <iostream> 
#include <algorithm>

void medianOfThree(int* arr, int left, int right) {
	int mid = (left + right) / 2;
	if (arr[mid] < arr[left])
		swap(arr[mid], arr[left]);
	if (arr[right] < arr[left])
		swap(arr[right], arr[left]);
	if (arr[mid] < arr[right])
		swap(arr[mid], arr[right]);
}

int partition(int* arr, int start, int end) {
	int left = start;
	int right = end - 1;
	medianOfThree(arr, start, end);
	int pivot = end;

	while (left <= right) {
		while (left <= right && arr[left] <= arr[pivot])
			left++;
		while (left <= right && arr[pivot] < arr[right])
			right--;
		if (left > right)
			break;

		swap(arr[left], arr[right]);

		left++;
		right--;
	}
	swap(arr[left], arr[pivot]);
	return left;
}

void MediamOfThreePivotQuicksort(int* arr, int start, int end) {

	if (start < end) {
		int pivot = partition(arr, start, end); // partition
		MediamOfThreePivotQuicksort(arr, start, pivot - 1);
		MediamOfThreePivotQuicksort(arr, pivot + 1, end);
	}
}