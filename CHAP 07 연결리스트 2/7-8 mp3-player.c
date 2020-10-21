//
//  7-8 mp3-player.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/09/21.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];  // typepdef로 배열을 선언하는 방법이 독특하다.

typedef struct DListNode {  // 이중연결 노드 타입
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

DListNode* current; // 현재 재생 목록

// 이중 연결 리스트를 초기화
void init(DListNode* phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}


// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* phead)
{
    DListNode* p;
    for(p = phead->rlink; p != phead; p = p->rlink)
    {
        if(p == current)                            // 현재 재생목록에만 # %s #으로 표시한다.
            printf("# %s # ", p->data);
        else
            printf("<-| %s |-> ", p->data);
    }
    printf("\n");
}

// newnode를 노드 before의 오른쪽에 삽입한다.
void dinsert(DListNode* before, element data)
{
    DListNode* newnode = (DListNode *)malloc(sizeof(DListNode)); // 새로운 노드 생성
    // newnode->data = data;       // int 형 데이터의 삽입
    strcpy(newnode->data, data);    // string 형 데이터 삽입
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

// 노드 removed를 삭제한다.
void ddelete(DListNode* head, DListNode* removed)
{
    if(removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}


int main()
{
    char ch;
    DListNode* head = (DListNode *)malloc(sizeof(DListNode));
    init(head); // 포인터 초기화를 위해 필요하다.
    
    dinsert(head, "Mamamia");
    dinsert(head, "Dancing Queen");
    dinsert(head, "Fernando");
    dinsert(head, "Dynamite");
    
    current = head->llink;
    print_dlist(head);
    
    do {
        printf("\n명령어를 입력하시오(<, >, q) : ");
        ch = getchar(); // char형 한글자만 입력받을때 쓰자 (편리하네 ㅋㅋ)
        if(ch == '<')
        {
            current = current->llink;
            if(current == head)         // 만약에 '<'를 누르며 head로 가면
                current = current->llink; // head는 아무런 데이터도 없기 때문에 한번더 llink를 해준다.
        }
        else if(ch == '>')
        {
            current = current->rlink;
            if(current == head)
                current = current->rlink;
        }
        print_dlist(head);
        getchar(); // 이게 왜 있는지 모르겠다.
    }while(ch != 'q');
    
    
    // 동적 메모리 해제 코드
    
    printf("삭제 단계\n");
    ddelete(head, head->rlink);
    ddelete(head, head->rlink);
    ddelete(head, head->rlink);
    ddelete(head, head->rlink);
    
    
    free(head);
    return 0;
}
