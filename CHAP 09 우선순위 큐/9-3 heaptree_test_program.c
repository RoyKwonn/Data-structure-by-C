//
//  9-3 heaptree_test_program.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/09/15.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200 // 최대 크기

typedef struct {    // # element 유형 정의
    int key;
} element;

typedef struct {                // # HeapType의 정의
    element heap[MAX_ELEMENT];  // 자료들을 배열로 저장한다 (위에서 지정한 힙의 최대크기 기준으로 넉넉하게 배열을 선언한다.)
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



void insert_max_heap(HeapType* h, element item)             // # 삽입 함수
{                                                           // 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
    int i = ++(h->heap_size);                               // heap_size를 1 증가시킨다.
    
    
    while ((i != 1) && (item.key > h->heap[i / 2].key))     // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    {
        h->heap[i] = h->heap[i / 2];                        // 몫에 대한 연산이기에 가능하다.
        i /= 2;
    }
    h->heap[i] = item; // 새로운 노드를 삽입
}


element delete_max_heap(HeapType* h)                        // # 삭제 함수
{
    int parent = 1, child = 2;                              // 루트에서부터 차근 차근 검사하기 위하여 위와 같이 설정한다.
    element item, temp;
    
    item = h->heap[1];                                      // 루트 노드의 값을 반환하기 item에 저장시킨다.
    temp = h->heap[(h->heap_size)--];                       // 맨 끝에 있는 노드를 불러오고 힙 사이즈를 감소시킨다.
    
    while(child <= h->heap_size)
    {
        if((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key) child++;     // 현재 노드의 자식노드 중 더 큰 자식노드를 찾는다.
        if(temp.key >= h->heap[child].key) break;           // 루트노드부터 오름차순으로 정렬되어있기 때문에 값이 더 큰게 루트쪽으로 옮겨지면 안된다.
        
        h->heap[parent] = h->heap[child];                   // 한 단계 아래로 이동
        parent = child;                                     // - 부모의 인덱스도 이동
        child *= 2;                                         // - 자녀의 인덱스도 이동
    }
    
    h->heap[parent] = temp;                                 // 이 문장 때문에 위의 구조가 바뀌었다.
 
    return item;
}

int main(void)
{
    element e1 = {10}, e2 = {5}, e3 = {30};
    element e4, e5, e6;
    HeapType* heap;
    
    heap = create();    // 히프 생성
    init(heap);         // 초기화
    
    // 삽입
    insert_max_heap(heap, e1);
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);
    
    // 삭제
    e4 = delete_max_heap(heap);
    printf("< %d > ", e4.key);
    e5 = delete_max_heap(heap);
    printf("< %d > ", e5.key);
    e6 = delete_max_heap(heap);
    printf("< %d > \n", e6.key);
    
    free(heap);
    return 0;
}
