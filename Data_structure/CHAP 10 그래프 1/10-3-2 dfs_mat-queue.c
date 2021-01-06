//
//  10-3-2 dfs_mat-queue.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/12/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 100

typedef struct GraphType {
    int n;      // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

// ====== 원형큐 코드 시작 =======

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

// 그래프 초기화
void init(GraphType* g)
{
    int r, c;
    g->n = 0;
    for(r = 0; r < MAX_VERTICES; r++)
        for(c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}


// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
    if(((g->n) + 1) > MAX_VERTICES)
    {
        fprintf(stderr, "그래프 : 정점의 개수 초과");
        return;
    }
    g->n++;
}


// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
    if(start >= g->n || end >= g->n) // 이거 조건식이 이상한듯
    {
        fprintf(stderr, "그래프 : 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}


// 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType* g, int v)
{
    int w;
    QueueType q; init_queue(&q);
    visited[v] = TRUE;               // 정점 v의 방문 표시
    printf("정점 %d -> ", v);       // 방문한 정점 출력
    enqueue(&q, v);
    while(!is_empty(&q))
    {
        v = dequeue(&q);
        for(w = 0; w < g->n; w++)
        {
            if(g->adj_mat[v][w] == 1 && visited[w] != TRUE)
            {
                visited[w] = TRUE;
                printf("정점 %d -> ", w);       // 방문한 정점 출력
                enqueue(&q, w);
            }
        }
    }
}

int main(void)
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    
    for(int i = 0; i < 4; i++)
        insert_vertex(g, i);
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);
    
    printf("깊이 우선 탐색\n");
    dfs_mat(g, 0);
    printf("\n");
    free(g);
    return 0;
}

