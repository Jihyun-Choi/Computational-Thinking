void Quicksort(int* arr, int start, int end) {//����Ʈ ����  
	if (start >= end) {//���Ұ� 1���� ���
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