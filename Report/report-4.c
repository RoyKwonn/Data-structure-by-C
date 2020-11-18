//  Created by Seokhwan Kwon on 2020/11/15.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//
//  Kruskal 알고리즘
//  Kruskal 알고리즘은 대부분 간선들을 정렬하는 시간에 좌우됨
//  시간 복잡도 : O(e*log e)


/*
 [ ] 1. 사용자로부터 정점과 간선을 입력받아서 그래프를 구성하라. (insert_vertex(), insert_edge()함수를 이용하라.)
 [ ] 2. 위에서 구성된 그래프에 대해서 Kruskal 알고리즘을 적용하되, 간선들을 정렬하는 대신에 간선들을 최소 힙 구조, min-heap에 저장하고, 새로운 간선을 고려할 때마다 min-heap으로부터 삭제하여 가져와라.
 [ ] 3. Kruskal()은 매개변수로 그래프 g를 전달받고, g로부터 최소비용 신장트리를 구성하는 간선들의 집합 T를 구하여 반환한다.
 [ ] 4. main() 함수는 다음과 같이 구성된다.
 */

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];       // 부모 노드
int num[MAX_VERTICES];          // 각 집합의 크기

// 힙에서는 Element
typedef struct Edge {   // 간선을 나타내는 구조체
    int start, end, weight;
}Edge;

// 힙에서는 HeapType
typedef struct GraphType {
    int n;      // 간선의 개수
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;


// curr이 속하는 집합을 반환한다.
int set_find(int curr)
{
    int p, s, i = -1;

    for(i = curr; (p=parent[i]) >= 0; i = p);    // 루트 노드까지 반복

    s = i;  // 집합의 대표 원소

    for(i = curr; (p = parent[i]) >= 0; i=p)
        parent[i] = s; // 집합의 모든 원소들의 부모를 s로 설정

    return s;
}


// 두개의 원소가 속한 집합을 합친다.
// (정점의 개수가 적은 트리의 루트가 큰 트리의 루트를 가리킨다.)

void set_union(int a, int b)
{
    int root1 = set_find(a);        // 노드 a의 루트를 찾는다.
    int root2 = set_find(b);        // 노드 b의 루트를 찾는다.
    if(num[root1] < num[root2])
    {
        parent[root1] = root2;
        num[root2] += num[root1];
    }
    else
    {
        parent[root2] = root1;
        num[root1] += num[root2];
    }
}

void print(GraphType T)
{
    int i, level = 1;
    printf("\n=====================");
    for(i=1; i <= T.n; i++)
    {
        if(i == level)
        {
            printf("\n");
            level *= 2;
        }
        printf("\t%d", T.edges[i].weight);
    }
    printf("\n======================");
}



// 최소 힙 구조
void insert_min_heap(GraphType* g, Edge item)
{
    int i;
    i = ++(g->n);

    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while((i != 1) && (item.weight < g->edges[i/2].weight))
    {
        g->edges[i] = g->edges[i/2];
        i /= 2;
    }
    g->edges[i] = item;     // 새로운 노드를 삽입
}


// 삭제 함수
Edge delete_min_heap(GraphType* g)
{
    int parent, child;
    Edge item, temp;
    item = g->edges[1];
    temp = g->edges[(g->n)--];
    parent = 1;
    child = 2;

    while(child <= g->n)
    {
        // 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
        if((child < g->n) && (g->edges[child].weight > g->edges[child + 1].weight))
            child++;
        if(temp.weight <= g->edges[child].weight) break;

        // 한 단계 아래로 이동
        g->edges[parent] = g->edges[child];
        parent = child;
    }
    g->edges[parent] = temp;
    return item;
}


/*Kruskal()은 매개변수로 그래프 g를 전달받고, g로부터 최소비용 신장트리를 구성하는 간선들의 집합 T를 구하여 반환한다. */
// kruskal의 최소 비용 신장 트리 프로그램
GraphType* kruskal(GraphType* g)
{
    int edge_accepted = 0;      // 현재까지 선택된 간선의 수
    int uset, vset;             // 정점 u와 정점 v의 집합 번호
    struct Edge e;
    

    /* 위에서 구성된 그래프에 대해서 Kruskal 알고리즘을 적용하되, 간선들을 정렬하는 대신에 간선들을 최소 힙 구조, min-heap에 저장하고, 새로운 간선을 고려할 때마다 min-heap으로부터 삭제하여 가져와라.*/


    printf("크루스칼 최소 신장 트리 알고리즘 \n");
    while(edge_accepted < (g->n))       // n-1개의 간선을 찾을 때까지
    {
        
        e = delete_min_heap(g);
        // 선택된 간선의 두 정점의 각 집합을 찾는다.
        uset = set_find(e.start);       // 정점 u의 집합 번호
        vset = set_find(e.end);         // 정점 v의 집합 번호
        if(uset != vset)        // 서로 속한 집합이 다르면
        {
            printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);      // 두개의 집합을 합친다.
        }
    }
    return g;
}



// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
    Edge temp;
    temp.start = start;
    temp.end = end;
    temp.weight = w;
    insert_min_heap(g, temp);
    g->n++;
}


// 초기화
void set_init(int n)
{
    for(int i = 0; i < n; i++)
    {
        parent[i] = -1;
        num[i] = 0;
    }
}

int insert_vertex()
{
    int i;
    printf("정점의 개수를 입력하시오 : ");
    scanf("%d", &i);
    
    for(int j = 0; j < i; j++)
    {
        parent[j] = 1;
        num[j] = 1;
    }
    
    return i;
}

// 그래프 초기화
void graph_init(GraphType* g)
{
    g->n = 0;
    for(int i = 0; i < 2 * MAX_VERTICES; i++)
    {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}



// 그래프 생성
void gen_graph(GraphType* g)
{
    char c = 'y';
    int n = 0;
    int start, end, w;
    g = (GraphType *)malloc(sizeof(GraphType));
    // 초기화
    graph_init(g);
    
    /*
     [ ] 1. 사용자로부터 정점과 간선을 입력받아서 그래프를 구성하라. (insert_vertex(), insert_edge()함수를 이용하라.)
     */
    n = insert_vertex();
    
    while(1)
    {
        printf("다음 순서대로 입력하시오 (ex. <간선의 시작> <간선의 끝> <간선의 가중치> : ");
        scanf("%d %d %d", &start, &end, &w);
        insert_edge(g, start, end, w);
        fflush(stdin);
        printf("간선을 계속 입력하시겠습니까?(y or n) : ");
        scanf("%c", &c);
        fflush(stdin);
        if(c == 'n') break;
    }
}




int main()
{
    GraphType* g = NULL;
    GraphType* T;
    // [1], [2] 조건이 아래 함수에 들어가야 한다.
    gen_graph(g);       // 그래프 생성
    
    /*
     [ ] 2. 위에서 구성된 그래프에 대해서 Kruskal 알고리즘을 적용하되, 간선들을 정렬하는 대신에 간선들을 최소 힙 구조, min-heap에 저장하고, 새로운 간선을 고려할 때마다 min-heap으로부터 삭제하여 가져와라.
     */
    T = kruskal(g);     // 최소비용 신장트리 간선 집합을 구하여 반환
//    print(T);           // 최소비용신장트리 출력
    
    return 0;
}
