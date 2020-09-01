//
//  3-6 swap.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/28.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//



// 포인터를 함수의 매개변수로 사용하는 프로그램
#include <stdio.h>

void swap(int *px, int *py)
{
    int tmp;
    tmp = *px;
    *px = *py;
    *py = tmp;
}

int main(void)
{
    int a = 1, b = 2;
    printf("swap을 호출하기 전 : a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("swap을 호출한 다음 : a = %d, b = %d\n", a, b);
    return 0;
}
