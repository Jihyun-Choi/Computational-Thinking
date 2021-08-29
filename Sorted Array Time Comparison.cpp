#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#define MAXN 100000//�迭�� ũ��
using namespace std;

double Com[3][10], cal[3];


void calcul() {
	long double num = 0;

	for (int i = 0; i < 3; i++) {
		for (int r = 0; r < 10; r++) {
			num += Com[i][r];
		}
		cal[i] = num / 10;
		cout << i + 1 << "��° ���� �ð�: " << cal[i] << endl;
		num = 0;
	}
}

void makeArray(int* arr) {//������ ������ �迭 �ʱ�ȭ
	srand(time(NULL));

	for (int i = 0; i < MAXN; i++)
		arr[i] = rand() % MAXN;
}

void copyArray(int* arr, int* ans) {//�迭 ���� �Լ�
	for (int i = 0; i < MAXN; i++)
		ans[i] = arr[i];
}

void checkArr(int* arr, int* ans) {//���� Ȯ�� �Լ�
	for (int i = 0; i < MAXN; i++)
		if (arr[i] != ans[i]) {
			printf("Sort ERROR!\n");
			return;
		}
}

void suffleArray(int* arr) {//�迭�� ���Ҹ� ����
	for (int i = 0; i < 100; i++)
		swap(arr[rand() % MAXN], arr[rand() % MAXN]);
}

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


int Oarr[MAXN], Carr[MAXN], Result[MAXN];

int main() {
	cout << "�迭�� ����: " << MAXN << endl << endl;

	for (int i = 0; i < 10; i++) {

		clock_t start_time, end_time;
		makeArray(Oarr);//���� ������ ���Ҹ� ������ �迭
		sort(Oarr, Oarr + MAXN);//Oarr�迭 ���� 
		copyArray(Oarr, Result);//Oarr�迭�� Result�迭�� ����, Result�� ���ĵ� �迭
		suffleArray(Oarr);//Oarr �迭 ����ȭ, Oarr�� ������ ���� �ȵ� �迭
		copyArray(Oarr, Carr);//Oarr�迭�� Carr�迭�� ���� , Carr�� Oarr�� ������ �迭

		//�⺻ ������
		start_time = clock();//�ð����� ����
		Quicksort(Carr, 0, MAXN - 1);
		end_time = clock();//�ð����� ����
		Com[0][i] = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		checkArr(Carr, Result);//������ �Ǿ��ִ��� Ȯ��

		//�������� ������
		copyArray(Oarr, Carr);//Oarr�迭�� Carr�迭�� ����
		start_time = clock();//�ð����� ����
		randomizedPivotQuicksort(Carr, 0, MAXN - 1);
		end_time = clock();//�ð����� ����
		Com[1][i] = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		checkArr(Carr, Result);//������ �Ǿ��ִ��� Ȯ��

		//�߰��� ������
		copyArray(Oarr, Carr);//Oarr�迭�� Carr�迭�� ����
		start_time = clock();//�ð����� ����
		MediamOfThreePivotQuicksort(Carr, 0, MAXN - 1);
		end_time = clock();//�ð����� ����
		Com[2][i] = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		checkArr(Carr, Result);//������ �Ǿ��ִ��� Ȯ��
	}
	calcul();
}