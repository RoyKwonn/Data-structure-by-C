//
//  2-4 slow_power.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>


// 반복적인 거듭제곱 계산 프로그램
double slow_power(double x, int n)
{
    int i;
    double result = 1.0;
    
    for(i=0; i<n; i++)
        result = result * x;
    return result;
}
