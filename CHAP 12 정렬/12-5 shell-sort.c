//
//  12-5 shell-sort.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/05.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int list[MAX_SIZE];
int n;


// 쉘 정렬
// gap 만큼 떨어진 요소들을 삽입 정렬
// 정렬의 범위는 first에서 last
void inc_insertion_sort(int list[], int first, int last, int gap)
{
    int i, j, key;
    for(i = first + gap; i <= last; i = i + gap)
    {
        key = list[i];
        for(j = i - gap; j >= first && key < list[j]; j = j - gap)
            list[j + gap] = list[j];
        list[j + gap] = key;
    }
}

void shell_sort(int list[], int n)  // n = size
{
    int i, gap;
    for(gap = n/2; gap>0; gap = gap/2)
    {
        if((gap %2) == 0) gap++; // 홀수인게 더 좋음
        for(i = 0; i < gap; i++)    // 부분 리스트의 개수는 gap
        inc_insertion_sort(list, i, n-1, gap);
    }
}



// 버블정렬
void bubble_sort(int list[], int n)
{
    int i, j, temp;
    for(i = n - 1; i > 0; i--)
    {
        for(j = 0; j < i; j++)
        {
            // 앞뒤의 레코드를 비교한 후 교체
            if(list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], temp);
        }
    }
}


// 삽입정렬
void insertion_sort(int list[], int n)
{
    int i, j, key;
    for(i = 1; i<n; i ++)
    {
        key = list[i];
        for(j = i - 1; j >= 0 && list[j] > key; j--) // 레코드의 오른쪽 이동
            list[j + 1] = list[j];
        list[j + 1] = key;
    }
}


// 선택정렬
void selection_sort(int list[], int n)
{
    int i, j, least, temp;
    
    for(i = 0; i < n - 1; i++)
    {
        least = i;
        for(j = i + 1; j < n; j++)  // 최소값 탐색
            if(list[j] < list[least]) least = j;
        SWAP(list[i], list[least], temp);
        
    }
}




int main(void)
{
    int i;
    n = MAX_SIZE;
    for(i = 0; i<n; i++)            // 난수 생성 및 출력
        list[i] = rand() % 100;     // 난수 발생 범위 0~99
    
    /*
    selection_sort(list, n);
    for(i = 0; i<n; i++)
        printf("%d ", list[i]);
    printf("\n");
    */
    
    /*
    insertion_sort(list, n);
    for(i = 0; i<n; i++)
        printf("%d ", list[i]);
    printf("\n");
    */
    
    /*
    bubble_sort(list, n);
    for(i = 0; i<n; i++)
        printf("%d ", list[i]);
    printf("\n");
    */
    
    shell_sort(list, n);
    for(i = 0; i<n; i++)
        printf("%d ", list[i]);
    printf("\n");
    
    return 0;
}


