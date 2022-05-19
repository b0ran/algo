#include <stdio.h>
#include <stdlib.h>

#define N 6
#define INF 9999

void dijkatra(int n, int w[][N], int f[], int source) {
	int i, j;
	int min;	//���� ���� weight ��
	int vnear=0;	//�߰��� ����
	int touch[N];	//�˻��ϱ� ���� ������ ����
	int length[N];	//�Ÿ� ���� �迭

	//�� �����͸� ������ �迭 �ʱ�ȭ
	for (i = 0;i < n;i++) {
		touch[i] = 1;
		length[i] = w[source][i];
		f[i] = -1;
	}
	f[source] = 1;	//source�� �̹� �湮�� ���� �ִٰ� ǥ��

	//�ִ� �Ÿ��� ã�� ���� �ݺ���
	for (i = 0; i < n - 1; i++) {
		min = INF;

		//���� ª�� �Ÿ��� ������ ã�� �ݺ���
		for (j = 0;j < n;j++) {
			if ((length[j] < min)&&f[j]==-1) {
				min = length[j];
				vnear = j;
			}
		}
		f[vnear] = 1;	//�ش� ������ �湮�� ���� �ִٰ� ǥ��

		//�Ÿ��� ������Ʈ �ݺ���
		for (j = 0;j < n;j++) {
			if ((length[vnear] + w[vnear][j] < length[j])) {
				length[j] = length[vnear] + w[vnear][j];
				touch[j] = vnear;
			}
		}
	}

	//�ִ� �Ÿ��� ����ϴ� �ݺ���
	for (i = 0; i < n; i++) {
		printf("%d���� %d������ �ִܰŸ� : %d \n", source, i, length[i]);
	}
}

void main() {
	int graph[N][N];
	int i, j, eNum, v1, v2, s;
	int e = 0;
	int f[N];	//�湮�� ���� �ִ� �������� Ȯ���ϴ� �迭
	
	printf("edge�� ������ �Է��Ͻÿ� : ");
	scanf_s("%d", &eNum);

	//������� ������ �ʱ�ȭ
	for (i = 0;i < N;i++) {
		for (j = 0;j < N;j++) {
			graph[i][j] = INF;
			if (i == j) {
				graph[i][j] = 0;
			}
		}
	}

	//������� ������ �Է�
	for (i = 0; i < eNum;i++) {
		printf("vertex1 vertex2 weight : ");
		scanf_s("%d %d %d", &v1, &v2, &e);

		graph[v1][v2] = e;
		graph[v2][v1] = e;
	}

	printf("\n<�ִ� �Ÿ��� ���� �������>\n");

	//������� ���
	for (i = 0;i < N;i++) {
		for (j = 0;j < N;j++) {
			printf("%-5d", graph[i][j]);
		}
		printf("\n");
	}

	printf("\n�ִ� �Ÿ��� ã�� source �� �Է�(0~5) : ");
	scanf_s("%d", &s);

	dijkatra(N, graph, f, s);
}