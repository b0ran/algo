#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void merge(int h, int m, int u[], int v[], int S[]);
void mergesort(int n, int s[]);
void quicksort(int low, int n, int s[]);
void partition(int l, int h, int pivot, int S[]);
void removekeys(int n, int s[]);
int root(int s[], int n);
void siftdown(int s[], int i, int n);
void makeheap(int n, int s[]);
void heapsort(int n, int s[]);

//exchangesort함수 
void exchangesort(int n, int *s) {
	int i, j;
	int a = 0;

	for (i = 0;i < n - 1;i++) {
		for (j = i + 1;j <= n;j++) {
			if (&s[i] > &s[j]) {
				a = &s[i];
				s[i] = &s[j];
				s[j] = a;
			}
		}
	}
}

//mergesort함수
void mergesort(int n, int s[]) {
	int a[5001], b[5001];
	int i=0, k=0, j=0;

	int high = n/2;
	int mid = n-high;

	for (i = 1;i <= high;i++) {
			a[i] = s[i];
		}
		for (j = 1;j <= mid;j++) {
			k = j + high + 1;  //s의 인덱스
			b[j] = s[k];
		}

	if (n > 1) {
		mergesort(high, a);
		mergesort(mid, b);
		merge(high, mid, a, b, s);
	}
	
}

void merge(int h, int m, int u[], int v[], int S[]) {
	int i = 0;
	int j = 0;
	int k = 0;

	while (i <= h && j <= m) {
		if (u[i] < v[j]) {
			S[k] = u[i];
			i++;
		}
		else {
			S[k] = v[j];
			j++;
		}
		k++;
	}
	if (i > h) {
		for (j = j;j < m;j++) {
			S[k] = v[j];
			k++;
		}
	}
	else {
		for (i = i;i < h;i++) {
			S[k] = u[i];
			k++;
		}
	}
}


//quicksort함수 
void quicksort(int low, int n, int s[]) {
	int pivot=low;
	int h = n;

	if (h > low) {
		partition(low, h, pivot, s);
		quicksort(low, pivot - 1, s);
		quicksort(pivot + 1, h, s);
	}
}

void partition(int l, int h, int pivot, int S[]) {
	int i, j, pivotitem;
	int a = 0;
	int b = 0;

	pivotitem = S[l];
	j = l;
	for (i = l + 1;i < h;i++) {
		if (S[i] < pivotitem) {
			j++;
			a = S[i];
			S[i] = S[j];
			S[j] = a;
		}
	}
	pivot = j;
	b = S[l];
	S[l] = S[pivot];
	S[pivot] = b;
}


//heapsort함수
void removekeys(int n, int s[]) {
	int i;
	for (i = n;i >= 1;i--) {
		s[i] = root(s,n);
	}
}

int root(int s[], int n) {
	int keyout;

	keyout = s[1];
	s[1] = s[n];
	n = n - 1;
	siftdown(s, 1,n);
	return keyout;
}

void siftdown(int s[], int i, int n) {
	int parent, largerchild;
	int siftkey;
	bool spotfound;

	siftkey = s[i];
	parent = i;
	spotfound = false;
	while (2 * parent <= n && !spotfound) {
		if (2 * parent < n && s[2 * parent] < s[2 * parent + 1]) {
			largerchild = 2 * parent + 1;
		}
		else {
			largerchild = 2 * parent;
		}
		if (siftkey < s[largerchild]) {
			s[parent] = s[largerchild];
			parent = largerchild;
		}
		else {
			spotfound = true;
		}
	}
	s[parent] = siftkey;
}

void makeheap(int n, int s[]) {
	int i;
	for (i = (n / 2);i >= 1;i--) {
		siftdown(s, i, n);
	}
}

void heapsort(int n, int s[]) {
	makeheap(n, s);
	removekeys(n, s);
}



int main(void) {
	int n, i, num;
	double result = 0;
	double sum = 0;
	time_t start, end;

	printf("생성할 난수 크기 : ");
	scanf_s("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * (n+1));
	
	
	//랜덤숫자배열 만들기 
	for (i = 0;i < n;i++) {
		//srand((unsigned int)time(NULL));
		num = rand() % 10001;
		arr[i] = num;

	}
	printf("\n");


	//exchangesort실행시간 구하기
	for (i = 0;i < 5;i++) {
		start = clock();
		exchangesort(n, *arr);
		end = clock();
		result = (double)(end - start);
		printf("exchangesort 실행시간 : %fms\n", result);

		sum += result;
	}
	printf("exchangesort 평균 실행 시간 : %fms\n\n", sum/5);

	sum = 0;
	result = 0;

	//mergesort실행시간 구하기
	for (i = 0;i < 5;i++) {
		start = clock();
		mergesort(n, arr);
		end = clock();
		result = (double)(end - start);
		printf("mergesort 실행시간 : %fms\n", result);

		sum += result;
	}
	printf("mergesort 평균 실행 시간 : %fms\n\n", sum / 5);
	
	
	sum = 0;
	result = 0;
	
	//quicksort실행시간 구하기 
	for (i = 0;i < 5;i++) {
		start = clock();
		quicksort(0,n,arr);
		end = clock();
		result = (double)(end - start);
		printf("quicksort 실행시간 : %fms\n", result);

		sum += result;
	}
	printf("quicksort 평균 실행 시간 : %fms\n\n", sum / 5);

	sum = 0;
	result = 0;
	
	//heapsort실행시간 구하기
	for (i = 0;i < 5;i++) {
		start = clock();
		heapsort(n, arr);
		end = clock();
		result = (double)(end - start);
		printf("heapsort 실행시간 : %fms\n", result);

		sum += result;
	}
	printf("heapsort 평균 실행 시간 : %fms\n", sum / 5);

	free(arr);

	return 0;
}
