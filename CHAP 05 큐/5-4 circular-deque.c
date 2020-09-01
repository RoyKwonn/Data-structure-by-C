//
//  5-4 circular-deque.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} DequeType;

// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}


void init_deque(DequeType *q)
{
    q->rear = q->front = 0;
}


// 공백 상태 검출 함수
int is_empty(DequeType *q)
{
    return (q->front == q->rear);
}


// 포화 상태 검출 함수
int is_full(DequeType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}


// 원형큐 출력 함수
void deque_print(DequeType *q)
{
    printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
    if(!is_empty(q)) {
        int i =  q->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;   // front 한칸 뒤부터 시작임
            printf("%d | ", q->data[i]);
            if(i == q->rear)
                break;
        }while(i != q->front);
    }
    printf("\n");
}



// 삽입 함수
void add_rear(DequeType *q, element item)
{
    if(is_full(q))
    {
        error("큐가 포화상태입니다.");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

void add_front(DequeType *q, element item)
{
    if(is_full(q))
    {
        error("큐가 포화상태입니다.");
    }
    q->data[q->front] = item;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE ) % MAX_QUEUE_SIZE;  // 나누기 오류가 날까봐 + MAX를 해주는것임.
}

// 삭제 함수
int delete_front(DequeType *q)
{
    if(is_empty(q))
    {
        error("큐가 공백상태입니다.");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int delete_rear(DequeType *q)
{
    int prev = q->rear;
    if(is_empty(q))
    {
        error("큐가 공백상태입니다.");
    }
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}

element get_front(DequeType *q)
{
    if(is_empty(q))
        error("큐가 공백상태입니다.");
    
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
 
element get_rear(DequeType *q)
{
    if(is_empty(q))
        error("큐가 공백상태입니다");
    return q->data[q->rear];
}

int main(int argc, const char * argv[])
{
    DequeType queue;
    
    init_deque(&queue);
    for(int i = 0; i<3; i++)
    {
        add_front(&queue, i);
        deque_print(&queue);
    }
    
    for(int i = 0; i<3; i++)
    {
        delete_rear(&queue);
        deque_print(&queue);
    }
    
    return 0;
}

