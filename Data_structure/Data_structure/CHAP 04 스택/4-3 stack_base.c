//
//  4-3 stack_base.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//



// 일반적인 배열 스택 프로그램

#include <stdio.h>
#include <stdlib.h>


// 차후에 스택이 필요하면 여기만 복사하여 붙인다.
// ====== 스택 코드의 시작 ======

#define MAX_STACK_SIZE 100      // 스택의 최대 크기

typedef int element;            // 데이터의 자료형
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;


// 스택 초기화 함수
void init_stack(StackType *s)
{
    s->top = -1;
}


// 공백 상태 검출 함수
int is_empty(StackType *s)
{
    return (s->top == -1);
}


// 포화 상태 검출 함수
int is_full(StackType *s)
{
    return (s->top == (MAX_STACK_SIZE -1));
}


// 삽입 함수
void push(StackType *s, element item)
{
    if(is_full(s))
    {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}


// 삭제 함수
element pop(StackType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}


// 피크 함수
element peek(StackType *s)
{
    if(is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}

// ======== 스택 코드의 끝 ==========

int main(void)
{
    StackType s;
    
    init_stack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    
    printf("%d \n", pop(&s));
    printf("%d \n", pop(&s));
    printf("%d \n", pop(&s));
    
    return 0;
}

