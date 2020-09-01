//
//  3-7 array1.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//


// 배열을 함수의 매개변수로 사용하는 프로그램
#include <stdio.h>
#define SIZE 6

void get_integers(int list[])                   // 이 입력방법 기억해두자!!!!!!!!!!!!
{
    printf("6개의 정수를 입력하시오 : ");
    for (int i = 0; i < SIZE; ++i)
        scanf("%d", &list[i]);
}

int cal_sum(int list[])
{
    int sum = 0;
    for (int i = 0; i < SIZE; ++i)
        sum += *(list + i);                     // 이 표현방법 인지 !!!!!!!!!!!!!!!!
    
    return sum;
}

int main(void)
{
    int list[SIZE];
    get_integers(list);
    printf("합 = %d\n", cal_sum(list));
    return 0;
}
