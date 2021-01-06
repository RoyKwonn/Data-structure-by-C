//
//  13-4 search_binary.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

int search_binary(int key, int low, int high)
{
    int middle;
    
    if (low <= high)
    {
        middle = (low + high) / 2;
        if (key == list[middle])        // 탐색 성공
            return middle;
        else if (key < list[middle])    // 왼쪽 부분리스트 탐색
            return search_binary(key, low, middle -1);
        else
            return search_binary(key, middle + 1, high);
    }
    
    return -1;  // 탐색 실패
}
