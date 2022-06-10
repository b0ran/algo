#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define t 5	//7, 9

typedef struct bTreeNode {
	int key_num;	//키의 개수
	int keys[2 * t - 1];	//최대로 가질 수 있는 키의 개수를 반영한 배열
	struct bTreeNode** child_pointer;	//자식 노드를 가리키는 포인터
	bool leafNode;	//리프노드인지 확인
}bn;

typedef struct bTree {
	int node_num;	//노드의 개수
	bn* root;	//루트 노드
}bt;

bn* node;
bt* tree;

//노드 생성 함수
void newNode() {
	node = (struct bTreeNode*)malloc(sizeof(struct bTreeNode));
	node->child_pointer = (struct bTreeNode**)malloc((2*t) * sizeof(struct bTreeNode*));
	node->key_num = 0;	//초기 노드가 가지는 키의 개수는 0개
}

//빈 트리 생성 함수
void emptyTree() {
	tree = (struct bTree*)malloc(sizeof(struct bTree));
	tree->root = newNode();
	tree->node_num = 1;		//루트만 생성되었을 때 전체 트리의 노드의 개수는 1개
}

//노드가 가득 찬 상황에서 이루어지는 분할 함수
void split(bn* x) {
	int i;
	bn* y;	//위로 올라가는 중간 키 값
	bn* z;	//분할한 뒤 오른쪽에 위치한 키 값들
	y = newNode();
	y = (x->key_num) / 2;	//x의 middle key에 해당하는 인덱스
	z = newNode();
	z->key_num = t - 1;		//새로 생긴 노드 z의 키의 개수

	//x가 가지고 있던 키 중 middle key 다음 인덱스부터 z로 옮김
	for (i = 0; i < t - 1; i++) {
		z->keys[i] = x->keys[((x->key_num)/2)+1+i];
	}

	//x가 가리키던 포인터를 z로 옮김
	for (i = 0; i < t - 1; i++) {
		z->child_pointer[i] = x->child_pointer[((x->key_num)/2)+1+i];
	}
}

//btree에 data를 삽입하는 함수
void insert(int data) {
	bn* root = tree->root;

	//root가 full 상태일 때 분할 함수 호출
	if (root->key_num == 2*t - 1) {
		bn* s;
		s = newNode();
		s = tree->root;	//s에 root 값을 옮김
		split(s);	//s에 대하여 분할 함수 호출
		//insertdata();
	}
	else {
		//insertdata();
	}
}

void main() {
	tree = emptyTree();		//트리 생성

	int i, random;
	int data_insert = 1000;
	int data_del = 500;
	double result = 0;
	time_t start, end;

	srand(time(NULL));

	start = clock();
	for (i=0; i < data_insert; i++) {
		random = rand() % 10000;
		insert(random);		//삽입함수 호출
	}
	end = clock();

	result = (double)(end - start);
	printf("t = %d일 때 insert 실행시간 : %fms\n", t, result);

	//delete(data_del);
}
