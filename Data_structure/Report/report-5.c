//  Created by Seokhwan Kwon on 2020/11/24.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//  20184646 컴퓨터공학과 권석환

/*
 [v] 그래프를 인접 행렬로 표현하되, 선언하면서 초기화하라.
 [ ] 위의 그래프에 대해서 Prim 알고리즘을 적용하되, 정점을 신장트리에 포함시키는데 최소 소요 비용을 표현하는 distance 배열을 최소 힙 구조, min-heap으로 표현하라. (정점이 선택되면서, 선택되지 않은 정점의 비용이 변경될 수 있다는 점을 유의하라)
 [ ] 알고리즘 수행 결과로 선택된 간선을 포함하는 배열 tree를 반환하라.
 [ ] 배열 tree를 이용하여 프로그램 수행 결과로 선택된 간선을 출력하고, 그 결과가 주어진 그래프에 대해서 최소 비용 신장트리임을 검증하라.
 */


#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000


typedef struct GraphType {
    int n;      // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;


// ========= heap ============
typedef int element;

typedef struct {                // # HeapType의 정의
    element heap[MAX_VERTICES];  // 자료들을 배열로 저장한다 (위에서 지정한 힙의 최대크기 기준으로 넉넉하게 배열을 선언한다.)
    int heap_size;              // Heap의 최대 사이즈를 정의한다
} HeapType;



HeapType* create()              // # 생성함수
{                               // 동적으로 Heap 구조를 생성한다.
    return (HeapType*)malloc(sizeof(HeapType));
}


void init(HeapType* h)          // # 초기화 함수 (heap을 가리키는 포인터로 정보를 가져와 수정이 가능하다.)
{
    h->heap_size = 0;           // # heap_size를 0로 설정하는 이유는 아직 저장한 정보가 하나도 없기 때문
}



void insert_min_heap(HeapType* h, element item)             // # 삽입 함수
{                                                           // 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
    int i = ++(h->heap_size);                               // heap_size를 1 증가시킨다.
    
    
    while ((i != 1) && (item > h->heap[i / 2]))     // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    {
        h->heap[i] = h->heap[i / 2];                        // 몫에 대한 연산이기에 가능하다.
        i /= 2;
    }
    h->heap[i] = item; // 새로운 노드를 삽입
}


element delete_min_heap(HeapType* h)                        // # 삭제 함수
{
    int parent = 1, child = 2;                              // 루트에서부터 차근 차근 검사하기 위하여 위와 같이 설정한다.
    element item, temp;
    
    item = h->heap[1];                                      // 루트 노드의 값을 반환하기 item에 저장시킨다.
    temp = h->heap[(h->heap_size)--];                       // 맨 끝에 있는 노드를 불러오고 힙 사이즈를 감소시킨다.
    
    while(child <= h->heap_size)
    {
        if((child < h->heap_size) && (h->heap[child]) > h->heap[child + 1]) child++;     // 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
        if(temp >= h->heap[child]) break;           // 루트노드부터 오름차순으로 정렬되어있기 때문에 값이 더 작은것이 루트쪽으로 옮겨지면 안된다.
        
        h->heap[parent] = h->heap[child];                   // 한 단계 아래로 이동
        parent = child;                                     // - 부모의 인덱스도 이동
        child *= 2;                                         // - 자녀의 인덱스도 이동
    }
    
    h->heap[parent] = temp;                                 // 이 문장 때문에 위의 구조가 바뀌었다.
 
    return item;
}

// ===========================

element selected[MAX_VERTICES];
element distance[MAX_VERTICES];



// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n, HeapType* tree)
{
    int v = -1, i;       // v : 정점의 정보를 저장
                         //(default : -1로 표현하며 오류를 나타냄)

    for(i = 0; i < n; i++) {  // 첫번째 선택되지 않은 정점 찾기
        if(!selected[i]) {
            v = i;
            insert_min_heap(tree, v);
            break;
        }
    }

//    // 위에서 찾은 정점을 가지고 비교하면서, 최소거리를 지니고 있는 정점을 찾는다.
//    for(i = 0; i < n; i++)
//        if(!selected[i] && (distance[i] < distance[v]))
//        {
//            v = i;
//            insert_min_heap(tree, v);
//        }
    v = delete_min_heap(tree);

    return (v); // 최소 거리를 가지고 있는 정점 반환
}


// void prim(int s, int n) s는 시작 n은 크기
void prim(GraphType* g, int s, HeapType* tree)
{
    int i, u, v;

    for(u = 0; u < MAX_VERTICES; u++) { // 우선 distance와 seleted를 초기화
        distance[u] = INF;
        selected[u] = FALSE;
    }
    
    distance[s] = 0; // 시작정점과 시작정점 사이의 거리는 0
    
    for(i = 0; i < g->n; i++) {
        u = get_min_vertex(g->n, tree);
        selected[u] = TRUE;
        
        
        if(distance[u] == INF) return;  // 직접 연결되지 않은 경우인지 확인
        
        printf("\"weight = %2d\" 노선 추가\n", distance[u]); // 방문한 노선 확인
        
        // INF보다 작은 값을 가지고 있다면, 그 값과 저장된 값을 비교 제일 작은 값을 추출한다.
        // 즉, 최소거리에 있는 정점에서 다시 최소거리 정점을 조사하는 것이다.
        for(v = 0; v < g->n; v++){
            if(g->weight[u][v] != INF) {
                if(!selected[v] && g->weight[u][v] < distance[v]){
                    distance[v] = g->weight[u][v];
                }
            }
        }
    }
}

int main(void)
{
    int s = 0; // 시작 정점
    HeapType* tree;
    
    // ---------- 그래프를 인접 행렬로 표현하되, 선언하면서 초기화하라. ------------
    GraphType g1 = { 7,
        {
            {0, 29, INF, INF, INF, 10, INF},
            {29, 0, 16, INF, INF, INF, 15},
            {INF, 16, 0, 12, INF, INF, INF},
            {INF, INF, 12, 0, 22, INF, 18},
            {INF, INF, INF, 22, 0, 27, 25},
            {10, INF, INF, INF, 27, 0, INF},
            {INF, 15, INF, 18, 25, INF, 0}
        }
    };
    
    GraphType g2 = {8,
        {
            {    0,   10,  INF,    6,  INF,  INF,  INF,    1},
            {   10,    0,    4,  INF,  INF,    2,  INF,  INF},
            {  INF,    4,    0,   11,  INF,    7,  INF,  INF},
            {    6,  INF,   11,    0,  INF,  INF,  INF,    3},
            {  INF,  INF,  INF,  INF,    0,    5,  INF,    8},
            {  INF,    2,    7,  INF,    5,    0,    9,  INF},
            {  INF,  INF,  INF,  INF,  INF,    9,    0,   12},
            {    1,  INF,  INF,    3,    8,  INF,   12,    0}
        }
    };
    
    tree = create();
    init(tree);
    
    prim(&g1, s, tree);      // MST에 포함된 간선들을 포함한 배열 반환
//    print(tree);        // 최소비용 신장트리 출력

    printf("\n=====================\n");
    
    prim(&g2, s, tree);      // MST에 포함된 간선들을 포함한 배열 반환
    free(tree);
    return 0;
}

