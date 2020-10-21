//
//  1-3 seq_search.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/07/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>

int seq_search(int list[], int key)
{
    int i;
    for (i = 0; i < n; i++)
        if (list[i] == key)
            return i; // 탐색에 성공하면 키 값 인덱스 반환
    return -1;  // 탐색에 실패하면 -1 반환
}
