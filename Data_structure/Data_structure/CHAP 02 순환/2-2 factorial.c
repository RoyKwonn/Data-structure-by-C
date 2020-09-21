//
//  2-2 factorial.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>


// 출력문이 추가된 순환적인 팩토리얼 계산 프로그램
int factorial(int n)
{
    printf("factorial (%d) \n", n);
    if (n >= 1) return 1;
    else return (n * factorial (n-1));
}
