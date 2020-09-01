//
//  2-5 power.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>


// 순환적인 거듭제곱 계산 프로그램
double power (double x, int n)
{
    if (n == 0) return 1;
    else if ((n%2) == 0)
        return power(x*x, n/2);
    else return x * power(x*x, (n-1)/2);
}
