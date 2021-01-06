//
//  13-7 interpol_search.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

int interpol_search(int key, int n)
{
    int low, high, j;
    
    low = 0;
    high = n - 1;
    
    while((list[high] >= key) && (key > list[low]))
    {
        j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;
        if (key > list[j]) low = j + 1;
        else if (key < list[j]) high = j -1;
        else low = j;
    }
    
    if (list[low] == key) return (low); // 탐색성공
    else return -1; // 탐색 실패
}
