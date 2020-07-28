//
//  5-3 buffer.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ====== 원형큐 코드 시작 =======
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;


// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}


// 초기화 함수
void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}


// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}


// 원형큐 출력 함수
void queue_print(QueueType *q)
{
    printf("QUEUE(front = %d rear = %d) = ", q->front, q->rear);
    if(!is_empty(q))
    {
        int i = q->front;
        do{
            i = (i + 1) % (MAX_QUEUE_SIZE);     // 원형큐의 특징이다.
            printf("%d | ", q->data[i]);        // 데이터를 출력
            if(i == q->rear)                    // index가 꼬리를 잡으면 종료(break;)
                break;
        }while(i != q->front);                  // index가 front를 따라잡으면 종료
    }
    
    printf("\n");
}


// 삽입 함수
void enqueue(QueueType *q, element item)
{
    if(is_full(q))
        error("큐가 포화상태입니다.");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}


// 삭제 함수
element dequeue(QueueType *q)
{
    if(is_empty(q))
        error("큐가 공백상태입니다.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 피크 함수
element peek(QueueType *q)
{
    if(is_empty(q))
        error("큐가 공백상태입니다.");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ======= 원형큐 코드 끝 =========


int main(void)
{
    QueueType queue;
    int element, data;
    
    init_queue(&queue);
    srand(time(NULL)); // 랜덤함수
    
    for(int i = 0; i < 100; i++)
    {
        if(rand() % 5 == 0)     // 5로 나누어 떨어지면
            enqueue(&queue, rand()%100);
        queue_print(&queue);
        if(rand() % 10 == 0)    // 10로 나누어 떨어지면
            data = dequeue(&queue);
        queue_print(&queue);
    }
    
    return 0;
}
