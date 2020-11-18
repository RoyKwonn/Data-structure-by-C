//
//  middle.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/22.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>

int main()
{
    int a[9] = { 23, 56, 11, 9, 56, 99, 27, 34, 0 };
    int temp1, temp2;
    int n = 8;
    int i = 3;
    
    
    temp1 = a[i];
    a[i] = 0;
    for(int j = i; j < n + 1; j += 2)
    {
        temp2 = a[j+1];
        a[j+1] = temp1;
        temp1 = a[j+2];
        a[j+2] = temp2;
    }
    
    for(int k = 0; k < n+1; k++)
    {
        printf("%d ", a[k]);
    }
    printf("\n");
}
