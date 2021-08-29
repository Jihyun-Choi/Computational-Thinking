#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#define MAXN 100000//배열의 크기
using namespace std;

double Com[3][10], cal[3];


void calcul() {
	long double num = 0;

	for (int i = 0; i < 3; i++) {
		for (int r = 0; r < 10; r++) {
			num += Com[i][r];
		}
		cal[i] = num / 10;
		cout << i + 1 << "번째 정렬 시간: " << cal[i] << endl;
		num = 0;
	}
}

void makeArray(int* arr) {//랜덤한 정수로 배열 초기화
	srand(time(NULL));

	for (int i = 0; i < MAXN; i++)
		arr[i] = rand() % MAXN;
}

void copyArray(int* arr, int* ans) {//배열 복사 함수
	for (int i = 0; i < MAXN; i++)
		ans[i] = arr[i];
}

void checkArr(int* arr, int* ans) {//정렬 확인 함수
	for (int i = 0; i < MAXN; i++)
		if (arr[i] != ans[i]) {
			printf("Sort ERROR!\n");
			return;
		}
}

void suffleArray(int* arr) {//배열의 원소를 섞기
	for (int i = 0; i < 100; i++)
		swap(arr[rand() % MAXN], arr[rand() % MAXN]);
}

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
	cout << "배열의 개수: " << MAXN << endl << endl;

	for (int i = 0; i < 10; i++) {

		clock_t start_time, end_time;
		makeArray(Oarr);//랜덤 생성한 원소를 저장한 배열
		sort(Oarr, Oarr + MAXN);//Oarr배열 정렬 
		copyArray(Oarr, Result);//Oarr배열을 Result배열로 복사, Result는 정렬된 배열
		suffleArray(Oarr);//Oarr 배열 랜덤화, Oarr은 정렬이 조금 안된 배열
		copyArray(Oarr, Carr);//Oarr배열을 Carr배열로 복사 , Carr은 Oarr와 동일한 배열

		//기본 퀵정렬
		start_time = clock();//시간측정 시작
		Quicksort(Carr, 0, MAXN - 1);
		end_time = clock();//시간측정 종료
		Com[0][i] = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		checkArr(Carr, Result);//정렬이 되어있는지 확인

		//랜더미즈 퀵정렬
		copyArray(Oarr, Carr);//Oarr배열을 Carr배열로 복사
		start_time = clock();//시간측정 시작
		randomizedPivotQuicksort(Carr, 0, MAXN - 1);
		end_time = clock();//시간측정 종료
		Com[1][i] = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		checkArr(Carr, Result);//정렬이 되어있는지 확인

		//중간값 퀵정렬
		copyArray(Oarr, Carr);//Oarr배열을 Carr배열로 복사
		start_time = clock();//시간측정 시작
		MediamOfThreePivotQuicksort(Carr, 0, MAXN - 1);
		end_time = clock();//시간측정 종료
		Com[2][i] = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		checkArr(Carr, Result);//정렬이 되어있는지 확인
	}
	calcul();
}