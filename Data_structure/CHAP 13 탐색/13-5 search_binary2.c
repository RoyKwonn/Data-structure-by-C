//
//  13-5 search_binary2.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

int search_binary2(int key, int low, int high)
{
    int middle;
    
    while(low <= high)      // 아직 숫자들이 남아 있으면
    {
        middle = (low + high) / 2;
        if (key == list[middle])
            return middle;
        else if (key > list[middle])
            low = middle + 1;
        else
            high = middle - 1;
    }
    
    return -1;      // 발견되지 않음
}
