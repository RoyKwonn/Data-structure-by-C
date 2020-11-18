//
//  9-4 heap-sort.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/09/15.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 200

typedef struct {
    int key;        // 우선순위 값?
} element;

typedef struct {
    //element heap[MAX_ELEMENT + 1];
    element* heap;
    int heap_size;
} HeapType;

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


// 정렬 함수
void heap_sort(element a[], int n)
{
    int i;
    HeapType* h;
    h = (HeapType*)malloc(sizeof(HeapType));
    h->heap = (element *)malloc(sizeof(element) * n);
    init(h);
    
    
    for(i = 0; i < n; i++)
    {
        insert_max_heap(h, a[i]);
    }
    
    for(i = (n - 1); i >= 0; i--)
    {
        a[i] = delete_max_heap(h);
    }
    
    free(h);
}

// #define SIZE 8


void make_change(element a[], int i, element key)
{
    int n = 8, j;
    HeapType* h;
    h = (HeapType*)malloc(sizeof(HeapType));
    h->heap = (element *)malloc(sizeof(element) * n);
    init(h);
    
    /*
    temp1 = a[i];
    a[i] = key;
    for(int j = i; j < n + 1; j += 2)
    {
        temp2 = a[j+1];
        a[j+1] = temp1;
        temp1 = a[j+2];
        a[j+2] = temp2;
    }*/
    
    
    for(j = 0; j < n; j++)
    {
        insert_max_heap(h, a[j]);
    }
    
    j = h->heap_size;
    while ((j != 1) && (key.key > h->heap[j / 2].key))
    {
        h->heap[j] = h->heap[j / 2];
        j /= 2;
    }
    h->heap[i] = key; // 새로운 노드를 삽입
    
    
    for(i = (n - 1); i >= 0; i--)
    {
        a[i] = delete_max_heap(h);
    }
    
    free(h);
}


int main(void)
{
    element list[] = { 23, 56, 11, 9, 56, 99, 27, 34 };
    element key;
    
    
    int n = MAX_ELEMENT;
    n = sizeof(list)/sizeof(element);
    
    key.key = 3;
    /*
    element* list;
    list = (element *)malloc(sizeof(element) * MAX_ELEMENT);
    */
    
    /*
    for(int i = 0; i < n; i++)
    {
        list[i].key = (rand() % 1000) + 1;
    }
    */
    
    make_change(list, 3, key);
    
    // heap_sort(list, n+1);
    
    //heap_sort(list, MAX_ELEMENT);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", list[i].key);
    }
    printf("\n");
    
    return 0;
}
