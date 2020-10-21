//
//  2-7 fib_iter.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>


// 반복적인 피보나치 수열 계산 프로그램
int fib_iter(int n)
{
    if(n == 0) return 0;
    if(n == 1) return 1;
    
    int pp = 0;
    int p = 1;
    int result = 0;
    
    for(int i = 2; i <= n; i++)
    {
        result = p + pp;
        pp = p;
        p = result;
    }
    
    return result;
}
