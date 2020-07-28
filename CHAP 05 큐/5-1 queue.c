//
//  5-1 queue.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//


// 선형큐 프로그램
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;    // 데이터 타입

typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;            // 큐 타입


// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기화
void init_queue(QueueType *q)
{
    q->rear = -1;
    q->front = -1;
}


// 큐 출력
void queue_print(QueueType *q)
{
    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        if(i <= q->front || i > q->rear) // 선형큐에서 데이터가 저장되어 있지 않는 구간
            printf("   | ");
        else                             // 선형큐에서 데이터가 저장되어 있는 구간
            printf("%d | ", q->data[i]);
    }
    printf("\n");
}


// 포화 검사
int is_full(QueueType *q)
{
    if(q->rear == MAX_QUEUE_SIZE - 1)
        return 1;
    else
        return 0;
}


// 공백검사
int is_empty(QueueType *q)
{
    if (q->front == q->rear)  // 이게 큐에 핵심이다.
        return 1;
    else
        return 0;
}

void enqueue(QueueType *q, int item)
{
    if(is_full(q))
    {
        error("큐가 포화상태입니다.");
        return;
    }
    q->data[++(q->rear)] = item; // ++(index)에 주목
}

int dequeue(QueueType *q)
{
    if(is_empty(q))
    {
        error("큐가 공백상태입니다.");
        return -1;
    }
    return q->data[++(q->front)];
    
}

int main(void)
{
    int item = 0;
    QueueType q;
    
    init_queue(&q);
    
    enqueue(&q, 10); queue_print(&q);
    enqueue(&q, 20); queue_print(&q);
    enqueue(&q, 30); queue_print(&q);
    
    item = dequeue(&q); queue_print(&q);
    item = dequeue(&q); queue_print(&q);
    item = dequeue(&q); queue_print(&q);
    return 0;
}
