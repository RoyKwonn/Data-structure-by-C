//
//  6-7 linked-list.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/08/02.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;


// 오류 처리 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}


ListNode* insert_first(ListNode *head, int value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;     // 헤드 포인터의 값을 복사
    head = p;           // 헤드 포인터 변경
    return head;        // 변경된 헤드 포인터 반환
}


// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    return head;
}


ListNode* delete_first(ListNode *head)
{
    ListNode *removed;
    if(head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}


ListNode* delete(ListNode *head, ListNode *pre)
{
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}


void print_list(ListNode *head)
{
    for(ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}


// 테스트 프로그램
int main(void)
{
    ListNode *head = NULL;
    
    for(int i = 0; i < 5; i++)
    {
        head = insert_first(head, i);       // insert_first()가 반환된 헤드 포인터를 head에 대입한다.
        print_list(head);
    }
    
    for(int i = 0; i < 5; i++)
    {
        head = delete_first(head);
        print_list(head);
    }
    
    return 0;
}
