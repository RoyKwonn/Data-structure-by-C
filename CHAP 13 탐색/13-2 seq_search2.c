//
//  13-2 seq_search2.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

int seq_search2(int key, int low, int high)
{
    int i;
    
    list[high + 1] = key;
    for (i = low; list[i] != key; i++)      // 키값을 찾으면 종료
    {
        ;
    }
    
    if(i == (high + 1)) return -1;          // 탐색 실패
    else return i;
}
