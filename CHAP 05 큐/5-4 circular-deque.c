//
//  5-4 circular-deque.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} DequeType;


// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}


// 초기화
void init_deque(DequeType *q)
