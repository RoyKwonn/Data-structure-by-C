//
//  3-3 polynomial2.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//


// 다항식 덧셈 프로그램 #2
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
typedef struct {
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS] = {{8,3}, {7,1}, {1,0}, {10,3}, {3,2}, {1,0}};
int avail = 6;



// 두개의 정수를 비교
char compare(int a, int b)
{
    if (a > b)  return '>';
    else if (a == b) return '=';
    else return '<';
}


// 새로운 항을 다항식에 추가한다.
void attach(float coef, int expon)
{
    if(avail > MAX_TERMS)
    {
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}



// C = A + B
void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)
{
    float tempcoef;
    *Cs = avail;
    
    while (As <= Ae && Bs <= Be)
        switch (compare(terms[As].expon, terms[Bs].expon)) {
            case '>':
                attach(terms[As].coef, terms[As].expon);
                As++;
                break;
            case '<':
                attach(terms[Bs].coef, terms[Bs].expon);
                Bs++;
                break;
            case '=':
                tempcoef = terms[As].coef + terms[Bs].coef;
                if(tempcoef) // 만약 계수가 0이 아니라면
                    attach(tempcoef, terms[As].expon);
                As++; Bs++;
                break;
        }
    
    // A의 나머지 항들을 이동함
    for(; As <= Ae; As++)
        attach(terms[As].coef, terms[As].expon);
    
    // B의 나머지 항들을 이동함
    for(; Bs <= Be; Bs++)
        attach(terms[Bs].coef, terms[Bs].expon);
    
    *Ce = avail - 1; // 아하! C의 End point를 나타내는 구나.
}



void print_poly(int s, int e)
{
    for(int i = s; i < e; i++)
        printf("%3.1f x^%d + ", terms[i].coef, terms[i].expon);
    printf("%3.1f x^%d\n", terms[e].coef, terms[e].expon);
}



int main(void)
{
    int As = 0, Ae = 2, Bs = 3, Be = 5, Cs, Ce; //위의 terms 의 index를 가리킨다.
    poly_add2(As, Ae, Bs, Be, &Cs, &Ce);
    print_poly(As, Ae);
    print_poly(Bs, Be);
    printf("--------------------------------------\n");
    print_poly(Cs, Ce);
    return 0;
}
