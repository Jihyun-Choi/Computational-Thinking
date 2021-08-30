void randomizedPivotQuicksort(int* arr, int start, int end) {//�����ϰ� �Ǻ��� �̴� ����Ʈ ����
	if (start >= end) {//���Ұ� 1���� ���
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