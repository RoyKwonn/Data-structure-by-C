//  Created by Seokhwan Kwon on 2020/10/14.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time()은 초단위로 컴퓨터 내부 시간을 읽어오는 <time.h>에 정의된 함수

// 데이터 항목 개수
#define MAX_SIZE 100000
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_TRY 5   // 5회씩 실시하여 평균치로 테이블을 구성한다.

// ------------- 힙 정렬 관련 -----------------------
// #define MAX_ELEMENT 100000

typedef struct {
    int key;
} element;
typedef struct {
    //element heap[MAX_ELEMENT];
    element* heap;
    int heap_size;
} HeapType;
// --------------- 권석환 커스텀 함수 -------------------
typedef struct {
    double elapsed;
    long cmp_freq;
    long mv_freq;
} StateElement;
typedef struct {
    StateElement selection;
    StateElement insertion;
    StateElement bubble;
    StateElement shell;
    StateElement heap;
    StateElement merge;
    StateElement quick;
} SortStates;

void print(int list[], int n);
void total_sort(void);
void print_line(char c);
// --------------- 메인 요구 조건 함수 ------------------
void caclStatistics(SortStates* stats, int n);      // 7가지 정렬방법에 대한 항목 개수별 실행시간, 비교회수, 이동회수 산출
void cmpSortsByTable(SortStates stats);     // 테이블 기반 비교 데이터 디스플레이
void cmpSortsByGraph(SortStates stats);  // 그래프 기반 비교 데이터 디스플레이
// =================================================


// int list[MAX_SIZE];


// [1] (1~1000) 범위의 난수를 발생
        void init_rand(int list[], int n);
// [2] 데이터 항목의 개수 (20,000 / 40,000 / 60,000 / 80,000 / 100,000)의 순으로 증가
// [3] 7가지 정렬 알고리즘 (오름 차순으로 정렬)
    // (1) 선택 정렬
        void selection_sort(int list[], int n, StateElement* result);
    // (2) 삽입 정렬
        void insertion_sort(int list[], int n, StateElement* result);
    // (3) 버블 정렬
        void bubble_sort(int list[], int n, StateElement* result);
    // (4) 쉘 정렬
        void shell_sort(int list[], int n, StateElement* result);
        void inc_insertion_sort(int list[], int first, int last, int gap, StateElement* result);
    // (5) 히프 정렬
        void insert_max_heap(HeapType* h, element item, StateElement* result);    // 삽입 함수
        element delete_max_heap(HeapType* h, StateElement* result);               // 삭제 함수
        void heap_sort(element a[], int n, StateElement* result);                 // 정렬 함수
    // (6) 합병 정렬
        void merge(int list[], int left, int mid, int right, StateElement* result);
        void merge_sort(int list[], int left, int right, StateElement* result);
    // (7) 퀵 정렬
        int partition(int list[], int left, int right, StateElement* result);
        void quick_sort(int list[], int left, int right, StateElement* result);
// [4] 실행시간, 비교회수, 이동회수 파악 (단, 5번의 실행결과에 대한 평균치로 계산)
// [5] 테이블, 그래프로 표현


// 다음은 여러분이 작성할 main() 프로그램의 골격이다.

int main()
{
    int n = 20000;                      // 데이터 항목의 개수 20,000 / 40,000 / 60,000 / 80,000 / 100,000
    SortStates stats;
    
    for(n = 20000; n <= 100000; n += 20000)
    {
        printf("데이터 항목 개수 : %d\n\n", n);
        caclStatistics(&stats, n);     // 7가지 정렬방법에 대한 항목 개수별 실행시간, 비교회수, 이동회수 산출
        cmpSortsByTable(stats);    // 테이블 기반 비교 데이터 디스플레이
        printf("\n\n");
        
    }
    
    cmpSortsByGraph(stats);  // 그래프 기반 비교 데이터 디스플레이
    
    
    return 0;
}

void cmpSortsByGraph(SortStates stats)  // 그래프 기반 비교 데이터 디스플레이
{
    printf("\n\n소요시간\n^\n");
    for(int i = 0; i < 15; i++)
    {
        if(i != 14)
        {
            for(int j = 0; j < 15; j++)
            {
                if(j == 0)
                    printf("|");
                else
                    printf(" ");
            }
            printf("\n");
        }
        else
        {
            for(int j = 0; j < 65; j++)
                printf("-");
            printf("> 원소 개수\n");
            for(int j = 20000; j <= 100000; j += 20000)
            {
                printf("%12d",j);
            }
            printf("\n");
        }
    }
}


void caclStatistics(SortStates* stats, int n)
{
    clock_t start, end;
    StateElement result, average;
    int* list = NULL;
    element* heap_list = NULL; // [5] 히프정렬-요소
    
    list = (int *)malloc(sizeof(int) * n);
    heap_list = (element *)malloc(sizeof(element) * (n+1));
    
    
    
    // [1] 선택 정렬
    
    average.cmp_freq = 0;
    average.elapsed = 0.0;
    average.mv_freq = 0;
    
    for(int i = 0; i < MAX_TRY; i++)
    {
        start = clock();                                                                // Start Count
        init_rand(list, n);                                                             // 랜덤한 수 만들기
        // printf("[1] 선택 정렬 (%d)\n", n);
        selection_sort(list, n, &result);                                        // 선택정렬
        average.cmp_freq += result.cmp_freq;                                    // 비교회수
        average.mv_freq += result.mv_freq;                                      // 이동회수
        //print(list, n);                                                                        // 정렬된 결과 출력
        end = clock();                                                                  // END Count
        average.elapsed += (double)((end - start) * 1000) / CLOCKS_PER_SEC;     // 소요 시간 측정값
    }
    stats->selection.cmp_freq = average.cmp_freq / MAX_TRY;
    stats->selection.mv_freq = average.mv_freq / MAX_TRY;
    stats->selection.elapsed = average.elapsed / MAX_TRY;
    
    
    // [2] 삽입 정렬
    
    average.cmp_freq = 0;
    average.elapsed = 0.0;
    average.mv_freq = 0;
    
    for(int i = 0; i < MAX_TRY; i++)
    {
        start = clock();                                                                // Start Count
        init_rand(list, n);                                                             // 랜덤한 수 만들기
        // printf("[2] 삽입 정렬 (%d)\n", n);
        insertion_sort(list, n, &result);
        average.cmp_freq += result.cmp_freq;                                    // 비교회수
        average.mv_freq += result.mv_freq;                                      // 이동회수
        //print(list, n);                                                                        // 정렬된 결과 출력
        end = clock();                                                                  // END Count
        average.elapsed += (double)((end - start) * 1000) / CLOCKS_PER_SEC;     // 소요 시간 측정값
    }
    stats->insertion.cmp_freq = average.cmp_freq / MAX_TRY;
    stats->insertion.mv_freq = average.mv_freq / MAX_TRY;
    stats->insertion.elapsed = average.elapsed / MAX_TRY;
    
    
    
    // [3] 버블 정렬
    
    average.cmp_freq = 0;
    average.elapsed = 0.0;
    average.mv_freq = 0;
    
    for(int i = 0; i < MAX_TRY; i++)
    {
        start = clock();                                                                // Start Count
        init_rand(list, n);                                                             // 랜덤한 수 만들기
        // printf("[3] 버블 정렬 (%d)\n", n);
        bubble_sort(list, n, &result);
        average.cmp_freq += result.cmp_freq;                                    // 비교회수
        average.mv_freq += result.mv_freq;                                      // 이동회수
        //print(list, n);                                                                        // 정렬된 결과 출력
        end = clock();                                                                  // END Count
        average.elapsed += (double)((end - start) * 1000) / CLOCKS_PER_SEC;     // 소요 시간 측정값
    }
    stats->bubble.cmp_freq = average.cmp_freq / MAX_TRY;
    stats->bubble.mv_freq = average.mv_freq / MAX_TRY;
    stats->bubble.elapsed = average.elapsed / MAX_TRY;
    
    
        
    
    // [4] 쉘 정렬
    
    average.cmp_freq = 0;
    average.elapsed = 0.0;
    average.mv_freq = 0;
    
    for(int i = 0; i < MAX_TRY; i++)
    {
        start = clock();                                                                // Start Count
        init_rand(list, n);                                                             // 랜덤한 수 만들기
        // printf("[4] 쉘 정렬 (%d)\n", n);
        shell_sort(list, n, &result);
        average.cmp_freq += result.cmp_freq;                                    // 비교회수
        average.mv_freq += result.mv_freq;                                      // 이동회수
        //print(list, n);                                                                        // 정렬된 결과 출력
        end = clock();                                                                  // END Count
        average.elapsed += (double)((end - start) * 1000) / CLOCKS_PER_SEC;     // 소요 시간 측정값
    }
    stats->shell.cmp_freq = average.cmp_freq / MAX_TRY;
    stats->shell.mv_freq = average.mv_freq / MAX_TRY;
    stats->shell.elapsed = average.elapsed / MAX_TRY;
         
    
    
    // [5] 히프 정렬 (출력값이 조금 이상하다)
    
    average.cmp_freq = 0;
    average.elapsed = 0.0;
    average.mv_freq = 0;
    
    for(int j = 0; j < MAX_TRY; j++)
    {
        start = clock();
        // printf("[5] 히프 정렬 (%d)\n", n);
        for(int i = 0; i < n; i++)
            heap_list[i].key = (rand() % 1000) + 1;     // 난수 발생 범위 1~1000
        heap_sort(heap_list, n, &result);     // 히프 솔트
        average.cmp_freq += result.cmp_freq;
        average.mv_freq += result.mv_freq;
        /*
         for(int i = 0; i < MAX_SIZE; i++)
         {
            printf("%d ", heap_list[i].key);
         } printf("\n\n");
         */
        end = clock();
        average.elapsed += (double)((end - start) * 1000) / CLOCKS_PER_SEC;
    }
    stats->heap.cmp_freq = average.cmp_freq / MAX_TRY;
    stats->heap.mv_freq = average.mv_freq / MAX_TRY;
    stats->heap.elapsed = average.elapsed / MAX_TRY;
    
    
    
    // [6] 합병 정렬
    
    average.cmp_freq = 0;
    average.elapsed = 0.0;
    average.mv_freq = 0;
    
    for(int i = 0; i < MAX_TRY; i++)
    {
        start = clock();                                                                // Start Count
        init_rand(list, n);                                                             // 랜덤한 수 만들기
        result.cmp_freq = 0;            // merge는 재귀함수라서 여기서 초기화시켜준다.
        result.mv_freq = 0;
        // printf("[6] 합병 정렬 (%d)\n", n);
        merge_sort(list, 0, n - 1, &result);
        average.cmp_freq += result.cmp_freq;                                    // 비교회수
        average.mv_freq += result.mv_freq;                                      // 이동회수
        //print(list, n);                                                                        // 정렬된 결과 출력
        end = clock();                                                                  // END Count
        average.elapsed += (double)((end - start) * 1000) / CLOCKS_PER_SEC;     // 소요 시간 측정값
    }
    stats->merge.cmp_freq = average.cmp_freq / MAX_TRY;
    stats->merge.mv_freq = average.mv_freq / MAX_TRY;
    stats->merge.elapsed = average.elapsed / MAX_TRY;
    
    
    
    // [7] 퀵 정렬
    
    average.cmp_freq = 0;
    average.elapsed = 0.0;
    average.mv_freq = 0;
    
    for(int i = 0; i < MAX_TRY; i++)
    {
        start = clock();                                                                // Start Count
        init_rand(list, n);                                                             // 랜덤한 수 만들기
        result.cmp_freq = 0;            // merge는 재귀함수라서 여기서 초기화시켜준다.
        result.mv_freq = 0;
        // printf("[7] 퀵 정렬 (%d)\n", n);
        quick_sort(list, 0, n - 1, &result);     // 퀵정렬 호출
        average.cmp_freq += result.cmp_freq;                                    // 비교회수
        average.mv_freq += result.mv_freq;                                      // 이동회수
        //print(list, n);                                                                        // 정렬된 결과 출력
        end = clock();                                                                  // END Count
        average.elapsed += (double)((end - start) * 1000) / CLOCKS_PER_SEC;     // 소요 시간 측정값
    }
    stats->quick.cmp_freq = average.cmp_freq / MAX_TRY;
    stats->quick.mv_freq = average.mv_freq / MAX_TRY;
    stats->quick.elapsed = average.elapsed / MAX_TRY;
    
    free(list);
    free(heap_list);
}


void print_line(char c)
{
    int n = 60;
    for(int i = 0; i < n; i++)
        printf("%c", c);
    printf("\n");
}

void cmpSortsByTable(SortStates stats)
{
    
    printf("   구분  |     소요 시간     |     비교 회수     |    이동 회수\n");
    print_line('=');
    printf(" 선택정렬 |  %12lf  |   %12ld   |  %12ld   \n", stats.selection.elapsed, stats.selection.cmp_freq, stats.selection.mv_freq);
    print_line('-');
    printf(" 삽입정렬 |  %12lf  |   %12ld   |  %12ld   \n", stats.insertion.elapsed, stats.insertion.cmp_freq, stats.insertion.mv_freq);
    print_line('-');
    printf(" 버블정렬 |  %12lf  |   %12ld   |  %12ld   \n", stats.bubble.elapsed, stats.bubble.cmp_freq, stats.bubble.mv_freq);
    print_line('-');
    printf(" 쉘 정렬 |  %12lf  |   %12ld   |  %12ld   \n", stats.shell.elapsed, stats.shell.cmp_freq, stats.shell.mv_freq);
    print_line('-');
    printf(" 히프정렬 |  %12lf  |   %12ld   |  %12ld   \n", stats.heap.elapsed, stats.heap.cmp_freq, stats.heap.mv_freq);
    print_line('-');
    printf(" 합병정렬 |  %12lf  |   %12ld   |  %12ld   \n", stats.merge.elapsed, stats.merge.cmp_freq, stats.merge.mv_freq);
    print_line('-');
    printf(" 퀵 정렬 |  %12lf  |   %12ld   |  %12ld   \n", stats.quick.elapsed, stats.quick.cmp_freq, stats.quick.mv_freq);
    
}



// 퀵 정렬
int partition(int list[], int left, int right, StateElement* result)
{
    int pivot, temp;
    int low, high;
    
    low = left;                     result->mv_freq++;
    high = right + 1;               result->mv_freq++;
    pivot = list[left];             result->mv_freq++;
    
    do{
        do{
            low++;                  result->mv_freq++;
                                    result->cmp_freq++;
        } while(list[low] < pivot);
        do{
            high--;                 result->mv_freq++;
                                    result->cmp_freq++;
        } while(list[high] > pivot);
        
        result->cmp_freq++;
        if(low < high)
        {
            SWAP(list[low], list[high], temp);      result->mv_freq += 3;
        }
                                    result->cmp_freq++;
    }while (low < high);
    
    SWAP(list[left], list[high], temp);             result->mv_freq += 3;
    
    return high;
}

void quick_sort(int list[], int left, int right, StateElement* result)
{
    result->cmp_freq++;
    if (left < right)
    {
        int q = partition(list, left, right, result);
        quick_sort(list, left, q - 1, result);
        quick_sort(list, q + 1, right, result);
    }
}



// 합병 정렬
int sorted[MAX_SIZE];   // 추가 공간이 필요

/*  i는 정렬된 왼쪽 리스트에 대한 인덱스
    j는 정렬된 오른쪽 리스트에 대한 인덱스
    k는 정렬될 리스트에 대한 인덱스*/

void merge(int list[], int left, int mid, int right, StateElement* result)
{
    int i, j, k, l;
    
    i = left;                           result->mv_freq++;
    j = mid + 1;                        result->mv_freq++;
    k = left;                           result->mv_freq++;
    
    /* 분할 정렬된 list의 합병 */
    while( i <= mid && j <= right)
    {                                   result->cmp_freq++; result->mv_freq++;
        
        result->cmp_freq++;
        if(list[i] <= list[j])
        {
            sorted[k++] = list[i++];    result->mv_freq++;
        }
        else
        {
            sorted[k++] = list[j++];    result->mv_freq++;
        }
    }
    
    result->mv_freq++;
    if(i > mid)     // 남아 있는 레코드의 일괄 복사
    {
        for(l = j; l <= right; l++)
        {                               result->cmp_freq++; result->mv_freq++;
            sorted[k++] = list[l];      result->mv_freq++;
        }
    }
    else            // 남아 있는 레코드의 일괄 복사
    {
        for(l = i; l <= mid; l++)
        {                               result->cmp_freq++; result->mv_freq++;
            sorted[k++] = list[l];      result->mv_freq++;
        }
    }
    
    // 배열 sorted[]의 리스트를 배열 list[]로 재복사
    for(l = left; l <= right; l++)
    {                                   result->cmp_freq++; result->mv_freq++;
        list[l] = sorted[l];            result->mv_freq++;
    }
}


void merge_sort(int list[], int left, int right, StateElement* result)
{
    int mid;
    
    result->cmp_freq++;
    if(left < right)
    {
        
        mid = (left + right) / 2;                       result->mv_freq++;// 리스트의 균등 분할
        merge_sort(list, left, mid, result);            // 부분 리스트 정렬
        merge_sort(list, mid + 1, right, result);       // 부분 리스트 정렬
        merge(list, left, mid, right, result);          // 합병
    }
}




// 힙 정렬




// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item, StateElement* result)
{
    int i;
    i = ++(h->heap_size);                           result->mv_freq++;
    
    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while ((i != 1) && (item.key > h->heap[i / 2].key))
    {                                               result->cmp_freq++; result->mv_freq++;
        
        h->heap[i] = h->heap[i / 2];                result->mv_freq++;
        i /= 2;                                     result->mv_freq++;
    }
    h->heap[i] = item; // 새로운 노드를 삽입
                                                    result->mv_freq++;
}

// 삭제 함수
element delete_max_heap(HeapType* h, StateElement* result)
{
    int parent, child;
    element item, temp;
    
    item = h->heap[1];                      result->mv_freq++;
    temp = h->heap[(h->heap_size)--];       result->mv_freq++;
    h->heap_size--;
    parent = 1;                             result->mv_freq++;
    child = 2;                              result->mv_freq++;
    
    while(child <= h->heap_size)
    {                                       result->cmp_freq++; result->mv_freq++;
        
                                            result->cmp_freq++;// 현재 노드의 자식노드 중 더 큰 자식노드를 찾는다.
        if((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
        {
            child++; result->mv_freq++;
        }
        
                                            result->cmp_freq++;
        if(temp.key >= h->heap[child].key) break;
        
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];   result->mv_freq++;
        parent = child;                     result->mv_freq++;
        child *= 2;                         result->mv_freq++;
    }
    h->heap[parent] = temp;                 result->mv_freq++;
    return item;
}


// 정렬 함수
void heap_sort(element a[], int n, StateElement* result)
{
    int i;
    HeapType* h;
    h = (HeapType*)malloc(sizeof(HeapType)); // 힙 생성
    h->heap_size = 0;   // 초기화
    h->heap = (element *)malloc(sizeof(element) * n);
    
    result->cmp_freq = 0;
    result->mv_freq = 0;
    
    for(i = 0; i < n; i++)
    {
        insert_max_heap(h, a[i], result);
    }
    
    for(i = (n - 1); i >= 0; i--)
    {
        a[i] = delete_max_heap(h, result);
    }
    
    free(h->heap);
    free(h);
}



// 쉘 정렬
// gap 만큼 떨어진 요소들을 삽입 정렬
// 정렬의 범위는 first에서 last
void inc_insertion_sort(int list[], int first, int last, int gap, StateElement* result)
{
    int i, j, key;
    
    for(i = first + gap; i <= last; i = i + gap)
    {   result->cmp_freq++; result->mv_freq++;
        
        key = list[i]; result->mv_freq++;
        
        for(j = i - gap; j >= first && key < list[j]; j = j - gap)
        {   result->cmp_freq++; result->mv_freq++;
            
            list[j + gap] = list[j]; result->mv_freq++;
        }
        list[j + gap] = key; result->mv_freq++;
    }
}

void shell_sort(int list[], int n, StateElement* result)  // n = size
{
    int i, gap;
    
    result->cmp_freq = 0;
    result->mv_freq = 0;
    
    for(gap = n/2; gap>0; gap = gap/2)
    { result->cmp_freq++; result->mv_freq++;
        
        result->cmp_freq++;
        if((gap %2) == 0)
        {
            gap++; // 홀수인게 더 좋음
            result->mv_freq++;
        }
        
        
        for(i = 0; i < gap; i++)    // 부분 리스트의 개수는 gap
        {   result->cmp_freq++; result->mv_freq++;
            
            inc_insertion_sort(list, i, n-1, gap, result);
        }
    }
    
}


// 버블정렬
void bubble_sort(int list[], int n, StateElement* result)
{
    int i, j, temp;
    result->cmp_freq = 0;
    result->mv_freq = 0;
    
    for(i = n - 1; i > 0; i--)
    {   result->cmp_freq++; result->mv_freq++;
        
        for(j = 0; j < i; j++)
        {   result->cmp_freq++; result->mv_freq++;
            
            // 앞뒤의 레코드를 비교한 후 교체
            result->cmp_freq++;
            if(list[j] > list[j + 1])
            {
                SWAP(list[j], list[j + 1], temp); result->mv_freq += 3; // Swap은 총 3번 이동한다.
            }
        }
    }
}


// 삽입정렬
void insertion_sort(int list[], int n, StateElement* result)
{
    int i, j, key;
    
    result->cmp_freq = 0;
    result->mv_freq = 0;
    
    for(i = 1; i<n; i ++)
    {   result->cmp_freq++; result->mv_freq++;
        
        key = list[i]; result->mv_freq++;
        
        for(j = i - 1; j >= 0 && list[j] > key; j--) // 레코드의 오른쪽 이동
        {   result->cmp_freq++; result->mv_freq++;
            
            list[j + 1] = list[j];  result->mv_freq++;
        }
        list[j + 1] = key; result->mv_freq++;
    }
}




// 선택정렬
void selection_sort(int list[], int n, StateElement* result)
{
    int i, j, least, temp;
    
    result->cmp_freq = 0;
    result->mv_freq = 0;
    
    for(i = 0; i < n - 1; i++)
    {   result->cmp_freq++; result->mv_freq++;
        
        least = i; result->mv_freq++;
        for(j = i + 1; j < n; j++)  // 최소값 탐색
        {   result->cmp_freq++; result->mv_freq++;
            
            result->cmp_freq++; // 비교 연산
            if(list[j] < list[least])
            {
                least = j; result->mv_freq++;
            }
        }
        SWAP(list[i], list[least], temp); result->mv_freq += 3; // Swap은 총 3번 이동한다.
    }
}


// 권석환 커스텀 함수
void init_rand(int list[], int n)
{
    int i;
    
    // 난수 발생을 위해서 다음의 코드를 이용한다.
    // 다음은 주어진 코드의 실행시간을 milisecond 단위로 측정하는 코드이다.
    srand(time(NULL));     // 시드를 초기화하여 rand()에 전달한다.
    
    for(i = 0; i< n; i++)            // 난수 생성 및 출력
        list[i] = (rand() % 1000) + 1;     // 난수 발생 범위 1~1000
}

void print(int list[], int n)
{
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n\n");
}
