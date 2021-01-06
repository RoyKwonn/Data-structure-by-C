//
//  9-3 heaptree_test_program.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/09/15.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;


// 히프트리의 구성
HeapType* create();                                 // 생성 함수
void init(HeapType* h);                             // 초기화 함수
void insert_max_heap(HeapType* h, element item);    // 삽입 함수
element delete_max_heap(HeapType* h);               // 삭제 함수

// 생성함수
HeapType* create()
{
    return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h)
{
    h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item)
{
    int i;
    i = ++(h->heap_size);
    
    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while ((i != 1) && (item.key > h->heap[i / 2].key))
    {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; // 새로운 노드를 삽입
}

// 삭제 함수
element delete_max_heap(HeapType* h)
{
    int parent, child;
    element item, temp;
    
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    
    while(child <= h->heap_size)
    {
        // 현재 노드의 자식노드 중 더 큰 자식노드를 찾는다.
        if((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
            child++;
        if(temp.key >= h->heap[child].key) break;
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}


void heap_sort(element a[], int n)
{
    int i;
    HeapType* h;
    
    h = create();
    init(h);
    
    for(i = (n - 1); i >= 0; i--)
    {
        insert_max_heap(h, a[i]);
    }
    
    for(i = 0; i < n; i++)
    {
        a[i] = delete_max_heap(h);
    }
    free(h);
}


int main(void)
{
    element e[] = { 10, 40, 30, 5, 12, 6, 15, 9, 60 };    // 문제에서 제시된 데이터
    int size = sizeof(e)/sizeof(element);
    heap_sort(e, size);
    for(int i = 0; i < size; i++)
    {
        printf("%d ", e[i].key);
    }
    printf("\n");
    
    return 0;
}

