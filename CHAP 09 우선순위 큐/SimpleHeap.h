//
//  SimpleHeap.h
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/12/05.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#ifndef __SIMPLE_HEAP_H__
#define __SIMPLE_HEAP_H__

#define TRUE        1
#define FALSE       0

#define HEAP_LEN    100

typedef char HData;
typedef int Priority;

typedef struct _heapElem
{
    Priority pr;    // 값이 작을수록 높은 우선순위
    HData   data;
} HeapElem;

typedef struct _heap
{
    int numOfData;
    HeapElem heapArr[HEAP_LEN];
} Heap;

void HeapInit(Heap* ph);
int HIsEmpty(Heap* ph);

void HInsert(Heap* ph, HData data, Priority pr);
HData HDelete(Heap* ph);

#endif /* SimpleHeap_h */
