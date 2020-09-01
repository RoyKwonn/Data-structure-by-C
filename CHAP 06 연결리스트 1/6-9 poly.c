//
//  6-9 poly.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/08/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


typedef struct ListNode {   // 노드 타입
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;

typedef struct ListType {   // 리스트 헤더 타입
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;


// 오류 처리 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}


// 리스트 헤더 생성 함수
ListType* create()
{
    ListType *plist = (ListType *)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}


// plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수
// expon는 지수
void insert_last(ListType* plist, int coef, int expon)
{
    ListNode* temp = (ListNode *)malloc(sizeof(ListNode));
    
    if(temp == NULL) error("메모리 할당 에러");
    
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;
    
    if(plist->tail == NULL)
    {
        plist->head = plist->tail = temp;
    }
    else
    {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->size++;
}


// list3 = list1 + list2
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{
    ListNode* a = plist1->head;
    ListNode* b = plist2->head;
    int sum;
    
    while(a && b)
    {
        if(a->expon == b->expon)
        {
            sum = a->coef + b->coef;
            if(sum != 0) insert_last(plist3, sum, a->expon);
            a = a->link;
            b = b->link;
        }
        else if(a->expon > b->expon)
        {
            insert_last(plist3, a->coef, a->expon);
            a = a->link;
        }
        else
        {
            insert_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }
    
    for(; a != NULL; a = a->link)
        insert_last(plist3, a->coef, a->expon);
    for(; b != NULL; b = b->link)
        insert_last(plist3, b->coef, b->expon);
}


void poly_print(ListType* plist)
{
    ListNode* p = plist->head;
    
    printf("polynomial = ");
    for(; p; p = p->link)
    {
        printf("%d^%d + ", p->coef, p->expon);
    }
    printf("\n");
}


int main(void)
{
    ListType *list1, *list2, *list3;
    
    // 연결 리스트 헤더 생성
    list1 = create();
    list2 = create();
    list3 = create();
    
    // 다항식 1을 생성
    insert_last(list1, 3, 12);
    insert_last(list1, 2, 8);
    insert_last(list1, 1, 0);
    
    // 다항식 2를 생성
    insert_last(list2, 8, 12);
    insert_last(list2, -3, 10);
    insert_last(list2, 10, 6);
    
    poly_print(list1);
    poly_print(list2);
    
    // 다항식 3 = 다항식 1 + 다항식 2
    poly_add(list1, list2, list3);
    poly_print(list3);
    
    free(list1);
    free(list2);
    free(list3);
}
