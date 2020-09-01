//
//  3-1 structure.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>

typedef struct studentTag{
    char name[10];
    int age;
    double gpa;
} student;

int main(void)
{
    student a = {"kim", 20, 4.3};
    student b = {"park", 21, 4.2};
    
    return 0;
}
