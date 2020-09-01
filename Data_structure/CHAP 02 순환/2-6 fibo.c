//
//  2-6 fibo.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>


// 순환적인 피보나치 수열 계산 프로그램
int fib(int n)
{
    if(n == 0) return 0;
    if(n == 1) return 1;
    return (fib(n-1) + fib(n-2));
}
