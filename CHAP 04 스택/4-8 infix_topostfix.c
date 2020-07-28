//
//  4-8 infix_topostfix.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//



// 중위표기 수식을 후위 표기 수식으로 변환하는 프로그램
#include <stdio.h>
#include <stdlib.h>

// =================================================
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
// =================================================


// 연산자의 우선순위를 반환한다.
int prec(char op)
{
    switch (op) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}


// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char exp[])
{
    int i = 0;
    char ch, top_op;
    int len = strlen(exp);
    StackType s;
    
    init_stack(&s);
    for(i = 0; i < len; i++)
    {
        ch = exp[i];
        switch (ch) {
            case '+': case '-': case '*': case '/': // 연산자
                // 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
                while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
                    printf("%c", pop(&s));
                push(&s, ch);
                break;
            case '(':
                push(&s, ch);
                break;
            case ')':
                top_op = pop(&s);
                
                // 왼쪽 괄호를 만날때까지 출력
                while(top_op != '(')
                {
                    printf("%c", top_op);
                    top_op = pop(&s);
                }
                break;
            default:
                printf("%c", ch);
                break;
        }
    }
    while(!is_empty(&s))
        printf("%c", pop(&s));
}


int main(void)
{
    char *s = "(2+3)*4+9";
    printf("중위표시수식 %s \n", s);
    printf("후위표시수식 ");
    infix_to_postfix(s);
    printf("\n");
    return 0;
}

