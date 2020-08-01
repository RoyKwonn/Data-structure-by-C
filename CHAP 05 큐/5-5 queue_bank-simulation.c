//
//  5-5 queue_bank-simulation.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/08/02.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ====== 원형큐 코드 시작 =======
#define MAX_QUEUE_SIZE 5
typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;      // 교체

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
    int minutes = 60;
    int total_wait = 0;
    int total_customers = 0;
    int service_time = 0;
    int service_customer;
    QueueType queue;
    init_queue(&queue);
    
    srand(time(NULL));
    for (int clock = 0; clock < minutes; clock++)
    {
        printf("현재시각 = %d\n", clock);
        if((rand()%10) < 3)
        {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand()% 3+1;
            enqueue(&queue, customer);
            printf("고객 %d이 %d분에 들어옵니다. 업무처리시간 = %d분\n", customer.id, customer.arrival_time, customer.service_time);
        }
        if(service_time > 0)
        {
            printf("고객 %d 업무처리중입니다. \n", service_customer);
            service_time--;
        }
        else
        {
            if(!is_empty(&queue))
            {
                element customer = dequeue(&queue);
                service_customer = customer.id;
                service_time = customer.service_time;
                printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다. \n", customer.id, clock, clock - customer.arrival_time);
                total_wait += clock - customer.arrival_time;
                
            }
        }
    }
    printf("전체 대기 시간 = %d\n", total_wait);
    return 0;
}
