//
//  4-7 stack_cals-posfix.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//



// 후위표기식 계산
#include <stdio.h>
#include <stdlib.h>


// ============================================
#define MAX_STACK_SIZE 100      // 스택의 최대 크기

typedef char element;            // 데이터의 자료형
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
// ============================================

int eval(char exp[])
{
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;
    
    init_stack(&s);
    
    for(i = 0; i < len; i++)
    {
        ch = exp[i];
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/') // 입력이 피 연산자이면
        {
            value = ch - '0'; // ASCII로 전단된 값을 real number로 변환
            push(&s, value);
        }
        else // 입력이 연산자이면
        {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) { // 연산을 수행하고 스택에 저장
                case '+':
                    push(&s, op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    break;
                case '*':
                        push(&s, op1 * op2);
                        break;
                case '/':
                        push(&s, op1 / op2);
                        break;
            }
        }
    }
    return pop(&s);
}



int main(void)
{
    int result;
    printf("후위표기식은 82/3-32*+\n");
    result = eval("82/3-32*+");
    printf("결과값은 %d\n", result);
    return 0;
}

