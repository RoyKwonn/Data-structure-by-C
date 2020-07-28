//
//  2-3 factorial_iter.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>


// 반복적인 팩토리얼 계산 프로그램
int factorial_iter(int n)
{
    int i, result = 1;
    for (i = 1; i <= n; i++)
        result = result * i;
    return result;
}
