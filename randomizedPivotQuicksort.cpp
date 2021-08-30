void randomizedPivotQuicksort(int* arr, int start, int end) {//랜덤하게 피봇을 뽑는 퀵소트 구현
	if (start >= end) {//원소가 1개인 경우
		return;
	}

	int pivot = (rand() * rand() % (end - start + 1)) + start, left = start + 1, right = end;
	swap(arr[start], arr[pivot]);
	pivot = start;
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
	randomizedPivotQuicksort(arr, start, right - 1);
	randomizedPivotQuicksort(arr, right + 1, end);
}