//
//  12-11 dictionary.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_WORD_SIZE 50
#define MAX_MEANING_SIZE 500
#define SIZE 5


typedef struct {
    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_SIZE];
} element;

element list[SIZE];     // 구조체 배열 선언

int main(void)
{
    int i, j;
    element temp;
    
    printf("5개의 단어와 의미를 입력하시오\n");
    
    for(i = 0; i < SIZE; i++)
    {
        scanf("%s[^\n]", list[i].word);         // 엔터키만을 제외하고 받는다.
        scanf("%s[^\n]", list[i].meaning);      // 엔터키만을 제외하고 받는다.
    }
    
    // 버블 정렬
    for(i = 0; i < SIZE - 1; ++i)
    {
        for(j = i + 1; j < SIZE; ++j)
        {
            if(strcmp(list[i].word, list[j].word) > 0)
            {
                SWAP(list[i], list[j], temp);
            }
        }
    }
    
    
    printf("\n정렬 후 사전의 내용 : \n");
    for (i = 0; i < SIZE; i++) {
        printf("%s : %s \n", list[i].word, list[i].meaning);
    }
    
    return 0;
}

