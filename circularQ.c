#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 // 큐의 최대 크기 = 4

typedef char element; // (typedef를 사용하여) char 형 element 생성
typedef struct { // (typedef를 사용하여) QueueType 구조체 생성
	element queue[MAX_QUEUE_SIZE]; // (element) 큐의 최대 크기 = 4
	int front, rear;
}QueueType;

QueueType *createQueue(); // 원형 큐 초기화
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ); // 큐의 공백상태
int isFull(QueueType *cQ); // 큐의 포화상태
void enQueue(QueueType *cQ, element item); // 큐의 rear에 원소 삽입
void deQueue(QueueType *cQ, element* item); // 큐의 front에 원소 제거/반환
void printQ(QueueType *cQ); // 큐의 현재 상태 출력
void debugQ(QueueType *cQ); // 큐 안의 값 출력
element getElement();


int main(void)
{
    printf("[----- [Kim Yun Seo]  [2020021016] -----]\n");

	QueueType *cQ = createQueue(); // 큐 생성
	element data;

	char command; // 변수 command

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 값 받기

		switch(command) {  
		case 'i': case 'I': // command 값이 i 또는 I 일 경우
			data = getElement();
			enQueue(cQ, data); // enQueue() 함수 호출
			break;
		case 'd': case 'D': // command 값이 d 또는 D 일 경우
			deQueue(cQ,&data); // deQueue() 함수 호출
			break;
		case 'p': case 'P': // command 값이 p 또는 P 일 경우
			printQ(cQ); // printQ() 함수 호출
			break;
		case 'b': case 'B': // command 값이 b 또는 B 일 경우
			debugQ(cQ); // debugQ() 함수 호출
			break;
		case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
			break;

		default: // 기본값
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행
	return 1;
}

QueueType *createQueue() // 원형 큐 초기화 (처음 생성하는 함수)
{
	QueueType *cQ; // QueueType의 포인터 = cQ
	cQ = (QueueType *)malloc(sizeof(QueueType));  // cQ 에 QueueType으로 주소 받기 (동적메모리 할당)
	cQ->front = 0; //front 의 초기값 설정
	cQ->rear = 0; // rear의 초기값 설정 (front == rear)
	return cQ; // cQ 값 반환
}

element getElement()
{
	element item; // element 로 변수 item 선언
	printf("Input element = ");
	scanf(" %c", &item); // item 값 받기
	return item;
}

int isEmpty(QueueType *cQ) // 큐가 공백상태인가?
{
	if (cQ->front == cQ->rear){ // (front 값 = rear 값)
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ) // 큐가 포화상태인가?
{
    // rear의 값을 1만큼씩 증가 -> (rear = front)가 되면 포화상태라고 안내 
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item) // 큐의 rear에 원소 삽입
{
	if(isFull(cQ)) return; // 포화된 큐 -> 중단
	else {
        // 원형 순환을 위해 '나머지 연산자'를 이용해 rear 변수 이동
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear = rear + 1
		cQ->queue[cQ->rear] = item; // cQ[rear] 에 item 삽입
	}
}

void deQueue(QueueType *cQ, element *item) // 큐의 front에 원소 제거, 반환
{
	if(isEmpty(cQ)) exit(1); // 공백의 큐
	else {
        // 원형 순환을 위해 '나머지 연산자'를 이용해 front 변수 이동
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // front = front + 1
		cQ->queue[cQ->front];
		return;
	}
}

void printQ(QueueType *cQ) // 현재 큐 상태 출력
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; // 첫번째 큐 (front + 1)
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; // 마지막 큐 (rear + 1)

	printf("Circular Queue : [");

	i = first;
	while(i != last){ // i 값이 last 가 아닐 경우동안 진행
		printf("%3c", cQ->queue[i]);
		i = (i+1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ) // 큐 안의 값 출력
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // i가 0부터 MAX_QUEUE_SIZE 전까지 진행
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
