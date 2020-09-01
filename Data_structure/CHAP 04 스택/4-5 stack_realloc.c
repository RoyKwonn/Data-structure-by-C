//
//  4-5 stack_realloc.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//



// 동적 배열 스택 프로그램2 (realloc의 활용)
// 최대 저장용량의 한계를 극복하였다.

#include <stdio.h>
#include <stdlib.h>

// ====== 스택 코드의 시작 ======

#define MAX_STACK_SIZE 100      // 스택의 최대 크기

typedef int element;            // 데이터의 자료형
typedef struct {
    element *data;              // data은 포인터로 정의된다.
    int capacity;               // 현재 크기
    int top;
} StackType;


// 스택 초기화 함수
void init_stack(StackType *s)
{
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
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
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
        // - 이미 할당한 공간의 크기를 바꿀 때 realloc 함수를 사용한다.
        // void* realloc(void* memblock, size_t size);    // realloc 함수의 원형 #include <stdlib.h>
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
    free(s.data);
    return 0;
}
