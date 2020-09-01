//
//  4-9 maze_search.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//



// 스택을 이용한 미로탐색 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6

// ============================================
#define MAX_STACK_SIZE 100      // 스택의 최대 크기

typedef struct {
    short r;
    short c;
} element;            // 데이터의 자료형

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


element here = {1, 0}, entry = {1, 0};
char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'},
};

// 위치를 스택에 삽입
void push_loc(StackType *s, int r, int c)
{
    if(r < 0 || c < 0) return;                  // 잘못된 길을 갈 경우 되돌아옴으로 문제 풀이 해결가능
    if(maze[r][c] != '1' && maze[r][c] != '.')
    {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}


// 미로를 화면에 출력한다.
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for(int r = 0; r < MAZE_SIZE; r++)
    {
        for(int c = 0; c < MAZE_SIZE; c++)
        {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void)
{
    int r, c;
    StackType s;
    
    init_stack(&s);
    here = entry;
    while(maze[here.r][here.c] != 'x')
    {
        r = here.r;
        c = here.c;
        
        maze[r][c] = '.'; // 지나간 자리 바꾸기
        maze_print(maze);
        
        push_loc(&s, r, c + 1);
        push_loc(&s, r + 1, c);
        push_loc(&s, r - 1, c);
        push_loc(&s, r, c - 1);
        
        
        if(is_empty(&s))
        {
            printf("실패\n");
            return 1;
        }
        else
            here = pop(&s); // 이게 탐색에 핵심 포인트였군!!!!!!!!!!!!!
    }
    printf("성공\n");
    return 0;
}
