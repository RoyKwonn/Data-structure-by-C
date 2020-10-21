//
//  12-9 qsort.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

// 퀵 정렬 라이브러리 함수의 사용

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int compare(const void *arg1, const void *arg2)
{
    if (*(double *)arg1 > *(double *)arg2) return 1;
    else if (*(double *)arg1 == *(double *)arg2) return 0;
    else return -1;
}

int main(void)
{
    int i;
    double list[5] = { 2.1, 0.9, 1.6, 3.8, 1.2 };
    
    qsort((void *)list, (size_t)5, sizeof(double), compare);
    for(i = 0; i < 5; i++)
        printf("%f ", list[i]);
    
    return 0;
}
