//
//  13-1 seq_search.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//


int seq_search(int key, int low, int high)
{
    int i;
    
    for (i = low; i <= high; i++)
    {
        if(list[i] == key)
            return i;       // 탐색에 성공하면 키 값의 인덱스 반환
        return -1;          // 탐색에 시패하면 -1 반환
    }
}
