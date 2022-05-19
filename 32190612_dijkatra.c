#include <stdio.h>
#include <stdlib.h>

#define N 6
#define INF 9999

void dijkatra(int n, int w[][N], int f[], int source) {
	int i, j;
	int min;	//가장 작은 weight 값
	int vnear=0;	//추가될 정점
	int touch[N];	//검사하기 위해 선택한 정점
	int length[N];	//거리 저장 배열

	//각 데이터를 저장할 배열 초기화
	for (i = 0;i < n;i++) {
		touch[i] = 1;
		length[i] = w[source][i];
		f[i] = -1;
	}
	f[source] = 1;	//source는 이미 방문한 적이 있다고 표시

	//최단 거리를 찾기 위한 반복문
	for (i = 0; i < n - 1; i++) {
		min = INF;

		//가장 짧은 거리의 정점을 찾는 반복문
		for (j = 0;j < n;j++) {
			if ((length[j] < min)&&f[j]==-1) {
				min = length[j];
				vnear = j;
			}
		}
		f[vnear] = 1;	//해당 정점은 방문한 적이 있다고 표시

		//거리값 업데이트 반복문
		for (j = 0;j < n;j++) {
			if ((length[vnear] + w[vnear][j] < length[j])) {
				length[j] = length[vnear] + w[vnear][j];
				touch[j] = vnear;
			}
		}
	}

	//최단 거리를 출력하는 반복문
	for (i = 0; i < n; i++) {
		printf("%d에서 %d까지의 최단거리 : %d \n", source, i, length[i]);
	}
}

void main() {
	int graph[N][N];
	int i, j, eNum, v1, v2, s;
	int e = 0;
	int f[N];	//방문한 적이 있는 정점인지 확인하는 배열
	
	printf("edge의 개수를 입력하시오 : ");
	scanf_s("%d", &eNum);

	//인접행렬 데이터 초기화
	for (i = 0;i < N;i++) {
		for (j = 0;j < N;j++) {
			graph[i][j] = INF;
			if (i == j) {
				graph[i][j] = 0;
			}
		}
	}

	//인접행렬 데이터 입력
	for (i = 0; i < eNum;i++) {
		printf("vertex1 vertex2 weight : ");
		scanf_s("%d %d %d", &v1, &v2, &e);

		graph[v1][v2] = e;
		graph[v2][v1] = e;
	}

	printf("\n<최단 거리를 구할 인접행렬>\n");

	//인접행렬 출력
	for (i = 0;i < N;i++) {
		for (j = 0;j < N;j++) {
			printf("%-5d", graph[i][j]);
		}
		printf("\n");
	}

	printf("\n최단 거리를 찾을 source 값 입력(0~5) : ");
	scanf_s("%d", &s);

	dijkatra(N, graph, f, s);
}