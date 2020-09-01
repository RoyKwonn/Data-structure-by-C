//
//  3-8 malloc.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//


// 동적 메모리 할당의 예
// MALLOC.C : malloc을 이용하여 정수 10을 저장할 수 있는 동적 메모리를
// 할당하고 free를 이용하여 메모리를 반납한다.
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main(void)
{
    int *p;
    p = (int *)malloc(SIZE * sizeof(int));          // malloc은 배열형식으로 할당된다.
    
    if(p == NULL)
    {
        fprintf(stderr, "메모리가 부족해서 할당할 수 없습니다.\n");
        exit(1);
    }
    
    for(int i = 0; i < SIZE; i++)
        p[i] = i;
    
    for(int i = 0; i < SIZE; i++)
        printf("%d ", p[i]);
    
    free(p);                                        // malloc은 free로 꼭 해제해주어야 한다.
    return 0;
}
