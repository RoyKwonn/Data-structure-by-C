//
//  7-4 multigame.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/09/21.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

ListNode* insert_first(ListNode* head, element data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    strcpy(node->data, data);   // 새로 생성한 노드에 data값을 넣어주기
    if(head == NULL)        // 만약 첫번째 노드이면
    {
        head = node;
        node->link = head;  // link가 자기 자신을 가리키게 해라
    }
    else
    {
        node->link = head->link; // head link가 가리키는 것을 가리키도록
        head->link = node;       // head link는 node를 가리키도록
    }
    
    return head;    // 변경된 헤드 포인터를 반환한다
}

int main(void)
{
    ListNode *head = NULL;
    
    head = insert_first(head, "KIM");
    head = insert_first(head, "LEE");
    head = insert_first(head, "PARK");
    
    ListNode* p = head;
    for(int i = 0; i < 10; i++)
    {
        printf("현재 차례=%s \n", p->data);
        p = p->link;
    }
    
    return 0;
}
