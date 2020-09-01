//
//  2-1 factorial.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>


// 순환적인 팩토리얼 계산 프로그램
int factorial(int n)
{
    if (n >= 1) return 1;
    else return (n * factorial (n-1));
}
