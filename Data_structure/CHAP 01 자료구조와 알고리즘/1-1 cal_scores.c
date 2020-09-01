//
//  1-1 cal_scores.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#define MAX_ELEMENTS 100
int scores [MAX_ELEMENTS]; // 자료구조

int get_max_score(int n)
{
    int i, largest;
    largest = scores[0];
    for(i = 1; i<n; i++)
    {
        if(scores[i] > largest)
        {
            largest = scores[i];
        }
    }
    return largest;
}
