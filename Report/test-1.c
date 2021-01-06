//
//  test-1.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    int SampeRTT[] = { 106, 120, 140, 90, 115};
    double a = 0.125;
    int EstimatedRTT = 0;
    double B = 0.25;
    int DevRTT = 0;
    int TimeoutInterval = 0;
    
    for(int i = 0; i < 5; i++) {
        EstimatedRTT = (1 - a) * EstimatedRTT + a * SampeRTT[i];
        DevRTT = (1 - B) * DevRTT + B * abs(SampeRTT[i] - EstimatedRTT);
        TimeoutInterval = EstimatedRTT + 4 * DevRTT;
        printf("[%d 번째]\n", i+1);
        printf("EstimatedRTT : %d / DevRTT : %d / TimeoutInterval : %d\n\n", EstimatedRTT, DevRTT, TimeoutInterval);
    }
}
