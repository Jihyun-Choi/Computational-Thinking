void Quicksort(int* arr, int start, int end) {//퀵소트 구현  
	if (start >= end) {//원소가 1개인 경우
		return;
	}
	int pivot = start, left = start + 1, right = end;

	while (left <= right) {
		while (left <= end && arr[left] <= arr[pivot]) {
			left++;
		}while (right > start && arr[right] >= arr[pivot]) {
			right--;
		}

		if (left > right) {
			swap(arr[right], arr[pivot]);
		}
		else {
			swap(arr[left], arr[right]);
		}
	}

	Quicksort(arr, start, right - 1);
	Quicksort(arr, right + 1, end);
}