//  report-6.c
//  Data_structure
//
//  Created by 20184646-권석환 on 2020/11/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

// 주어진 가중치 그래프에서 한 정점에서 다른 모든 정점까지의 최단 경로를 구하는 Dijkstra 알고리즘에 대해서 답하시오.
// [ ] 한 정점에서 다른 정점까지의 최단 경로의 길이와 그 경로를 출력하도록 수업시간에 다룬 Dijkstra 알고리즘을 수정하라.
// [ ] 다음번째 최단 경로 정점을 선택하기 위해서 최소 히프로 구현되는 우선순위 큐를 이용하라.
// [ ] 위의 수정 버전 알고리즘을 C 코드로 작성하고, 다음 그래프에 대해서 실행을 통해서 테스트하고, 그 결과를 검증하라.



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000     // 무한대 (연결이 없는 경우)
#define MAX_ELEMENT 7
#define MAX_HEAP_SIZE 200

typedef struct GraphType {
    int n;      // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

typedef struct Element {
    int weight; // weight (거리)
    int way[MAX_ELEMENT];
    int found;
} Element;

typedef struct HeapType {
    Element heap[MAX_HEAP_SIZE];
    int heap_size;
} HeapType;

int distance[MAX_VERTICES];     // 시작정점으로부터의 최단경로 거리
int found[MAX_VERTICES];        // 방문한 정점 표시(집합 S 표현)
int checker[MAX_ELEMENT][MAX_ELEMENT];    // 방문한 경로 표시


// ============ 우선순위 큐 최소 힙 관련 =================
HeapType* create()
{
    return (HeapType*)malloc(sizeof(HeapType));
}

void init_heap(HeapType* h)
{
    h->heap_size = 0;
}

void insert_min_heap(HeapType* h, Element item)
{
    int i = ++(h->heap_size);
    
    while((i != 1) && (item.weight < h->heap[i/2].weight))
    {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}

Element delete_min_heap(HeapType* h)
{
    int parent = 1, child = 2;
    Element item, temp;
    
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    
    while(child <= h->heap_size)
    {
        if((child < h->heap_size) && (h->heap[child].weight) > h->heap[child + 1].weight) child++;
        if(temp.weight <= h->heap[child].weight) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    
    return item;
}
// =================================================


// 가지고 있는 경로중 가장 거리가 짧은 것을 선택
int choose(int distance[], int n)
{
    int i, min, minpos;
    min = INT_MAX;  // 최대로 설정
    minpos = -1;    // default로 음수의 index를 설정한다
    for(i = 0; i < n; i++)
        if(distance[i] < min && !found[i])  // 현재 저장된 거리 && 발견된 것이 아닐 때
        {
            min = distance[i];  // 그 값을 최소값으로
            minpos = i;
        }
    return minpos;
}


void print_status(GraphType* g)
{
    static int step = 1;        // 정적변수로 몇번째 step인지 표시해주자
    printf("\n\n[STEP %d] \n", step++);
    printf("   index : ");
    for(int i = 0; i < g->n; i++)
    {
        printf(" %d ", i);
    }
    printf("\ndistance : ");
    for(int i = 0; i < g->n; i++)
    {
        if(distance[i] == INF) // 무한인 경우 '*' 로 표시해준다.
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    
    printf("\n");
    printf("   found : ");
    for(int i = 0; i < g->n; i++)
        printf("%2d ", found[i]);
    printf("\n");
}


// 경로 초기화
void init_checker(int start, GraphType* g, int index[])
{
    // 우선 방문한 정점인덱스를 다 -1로 표시한다.
    for(int i = 0; i < MAX_ELEMENT; i++)
    {
        for(int j = 0; j < MAX_ELEMENT; j++)
        {
                checker[i][j] = -1;
        }
    }
    
    // 시작위치를 각각 경로에 표시해준다.
    for(int i = 0; i < MAX_ELEMENT; i++)
    {
        checker[i][index[i]++] = start;
    }
    
    // 시작정점과 직접 연결된 경로를 표시해준다.
    for(int i = 1; i < MAX_ELEMENT; i++)
    {
        if(g->weight[0][i] != INF)
            checker[i][1] = i;
    }
}


// 경로 출력
void print_checker()
{
    for(int i = 0; i < MAX_ELEMENT; i++)
    {
        printf("v[%d] = ", i);
        for(int j = 0; j < MAX_ELEMENT; j++)
        {
            if(checker[i][j] != -1)  // 경로 인덱스가 확인 된다면 출력
            {
                printf("%2d -> ", checker[i][j]);
            }
        }
        printf("도착!\n");
    }
    printf("\n");
}

void heap_print(HeapType* h[], int cnt[])
{
    Element v;
    
    for(int i = 0; i < MAX_ELEMENT; i++)
    {
        for(int j = 0; j < cnt[i]; j++)
        {
            v = delete_min_heap(h[i]);
            // printf("| %d -> %d | weight : %2d \n", v.start, v.end, v.weight);
            printf("| ");
            for(int k = 0; k < MAX_ELEMENT; k++)
            {
                if(v.way[k] != -1)
                {
                    printf("%d -> ",v.way[k]);
                }
            }
            printf("| weight : %2d \n", v.weight);
        }
    }
}

void heap_shortest_path(GraphType* g, int start)
{
    HeapType* h[MAX_ELEMENT];       // 각 정점에 대한 최소트리 생성
    Element v;                      // 임시사용할 수 있는 정점
    // int cnt[MAX_ELEMENT] = {0};     // 체크용
    // int index[MAX_ELEMENT] = {0};   // 체크용
    int index = 0;
    int cnt = 0;
    int u;
    
    // 트리 초기화
    for(int i = 0; i < MAX_ELEMENT; i++)
    {
        h[i] = create();
        init_heap(h[i]);
        v.way[i] = -1; // 경로 1로 초기화
        distance[i] = g->weight[0][i];
    }
    
    v.found = TRUE;
    v.weight = 0;
    v.way[index++] = 0;
    insert_min_heap(h[0], v);
    
    for(int i = 1; i < MAX_ELEMENT; i++)
    {
        if(g->weight[0][i] != INF && g->weight[0][i] != 0) // 의미있는 값만 추가
        {
            v.weight = g->weight[0][i];
            v.way[index++] = i;  // 앞에서부터 최소경로만 추가 나머지는 -1로 세팅
            v.found = FALSE;
            insert_min_heap(h[0], v);
            cnt++;
        }
    }
    
    printf("distance : 0 ");
    for(int j = 1; j < MAX_ELEMENT; j++)
    {
        if(distance[j] != INF)
            printf(" %2d ", distance[j]);
        else printf("  *  ");
    }
    printf("\n");
    
    printf("현재 경로 : \n");
    for(int i = 0; i < cnt; i++)
    {
        v = delete_min_heap(h[0]);
        v.found = TRUE;
        for(int j = 0; j < MAX_ELEMENT; j++)
        {
            if(v.way[j] != -1)
                printf(" %d ->", v.way[j]);
        }
        printf("도착!\n");
        u = choose(distance, g->n); // v랑 u랑 같은 값이 나온다.
        
        for(int w = 0; w < MAX_ELEMENT; w++)
        {
            if(distance[u] + g->weight[u][w] > distance[w])
            {
                distance[w] = distance[u] + g->weight[u][w];
                index = 1;
                for(int k = 1; k < MAX_ELEMENT; k++)
                {
                    if(v.way[k] != -1)
                    {
                        v.way[index++] = u;
                        
                    }
                }v.way[index++] = w;
            }
        }
        
        
    }
    
    for(int i = 0; i < MAX_ELEMENT; i++)
    {
        free(h[i]);
    }
//    // 그래프에서 힙으로 옮기기
//    for(int i = 0; i < MAX_ELEMENT; i++)
//    {
//        for(int j = 0; j < MAX_ELEMENT; j++)
//        {
//            if(g->weight[i][j] != INF && g->weight[i][j] != 0) // 의미있는 값만 추가
//            {
//                v.weight = g->weight[i][j];
//                v.way[index[i]++] = j;  // 앞에서부터 최소경로만 추가 나머지는 -1로 세팅
//                v.found = FALSE;
//                insert_min_heap(h[i], v);
//                cnt[i]++;
//            }
//        }
//    }
//
//
//    // 경로확인 초기화
//
//    distance[start] = 0;        // 시작정점 -> 시작정점의 거리는 0으로
//
//    for(int i = 0; i < (g->n - 1); i++) // 나머지 정점에 대해서 // 반복 회수만 유의미하다.
//    {
//        print_status(g);    // distance, found 상태 출력
//        v = delete_min_heap(h[start]);
//        v.found = TRUE;
//
//        printf("     경로 : \n");
//        printf("v[%d] : ", i);
//        for(int j = 0; j < MAX_ELEMENT; j++)
//        {
//            printf(" %2d -> ",v.way[j]);
//        }
//        printf("도착! \n");
//
//
//        for(int w = 0; w < g->n; w++)
//        {
//            if(!found[w])
//            {
//                if(v.way[i] + g->weight[v.end][w] < distance[w]) // 이미 저장된 경로보다 더 작은 경로를 찾은경우
//                {
//                    distance[w] = distance[v.end] + g->weight[v.end][w];    // 거리를 갱신해준다.
//                    index[w] = 1;   // 경로를 처음부터 다시 작성하기 위해 인덱스를 조정해준다.
//                    for(int k = 1; k < MAX_ELEMENT; k++)
//                    {
//                        if(checker[v.end][k] != -1) // u까지의 경로를 먼저 넣어준다.
//                            checker[w][index[w]++] = checker[v.end][k];
//                    }
//                    checker[w][index[w]] = w;   // w를 추가해준다.
//                }
//            }
//        }
//
//    }
}




void shortest_path(GraphType* g, int start)
{
    int i, u, w;
    int index[MAX_ELEMENT] = {0};
    
    
    for(i = 0; i < g->n; i++) // distance, found를 초기화
    {
        distance[i] = g->weight[start][i];  // start에서 시작하여 가장 짧은길 찾기
        found[i] = FALSE;   // 아직 찾은 것이 없다.
    }
    
    // 경로확인 초기화
    init_checker(start, g, index);
    
    found[start] = TRUE;        // 출발지는 이미 방문 완료
    distance[start] = 0;        // 시작정점 -> 시작정점의 거리는 0으로
    
    for(i = 0; i < (g->n - 1); i++) // 나머지 정점에 대해서 // 반복 회수만 유의미하다.
    {
        print_status(g);    // distance, found 상태 출력
        u = choose(distance, g->n);  // 방문되지 않은 정점중에서 distance의 최소 값 선택
        
        found[u] = TRUE;    // 최소 경로라고 found로 확인해준다.
        checker[u][index[u]++] = u; // 최소경로라고 확인이 된다면, 경로배열에 추가해주자.
        
        printf("     경로 : \n");
        print_checker();
        
        for(w = 0; w < g->n; w++)
        {
            if(!found[w])
            {
                if(distance[u] + g->weight[u][w] < distance[w]) // 이미 저장된 경로보다 더 작은 경로를 찾은경우
                {
                    distance[w] = distance[u] + g->weight[u][w];    // 거리를 갱신해준다.
                    index[w] = 1;   // 경로를 처음부터 다시 작성하기 위해 인덱스를 조정해준다.
                    for(int k = 1; k < MAX_ELEMENT; k++)
                    {
                        if(checker[u][k] != -1) // u까지의 경로를 먼저 넣어준다.
                            checker[w][index[w]++] = checker[u][k];
                    }
                    checker[w][index[w]] = w;   // w를 추가해준다.
                }
            }
        }
        
    }
}


int main(void)
{
    
    
    // 그래프 초기화된 것을 보면, 대칭행렬인 것을 알 수 있습니다.
    GraphType g = { 7,
        {   //  0    1    2    3    4    5    6
            {   0,   7, INF, INF,   3,  10, INF },  // 0
            {   7,   0,   4,  10,   2,   6, INF },  // 1
            { INF,   4,   0,   2, INF, INF, INF },  // 2
            { INF,  10,   2,   0,  11,   9,   4 },  // 3
            {   3,   2, INF,  11,   0, INF,   5 },  // 4
            {  10,   6, INF,   9, INF,   0, INF },  // 5
            { INF, INF, INF,   4,   5, INF,   0 }   // 6
        }
    };
    
    // shortest_path(&g, 0);
    heap_shortest_path(&g, 0);
    
    return 0;
}

