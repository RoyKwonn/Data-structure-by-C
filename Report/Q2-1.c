//  Created by Seokhwan Kwon on 2020/10/01.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.

/*[!] 유의사항 : 각 단계의 출력에 대해서 입력 대비 결과가 올바르다는 것을 보여야 한다. 그렇지 않으면 점수를 받지 못함에 유의해야 한다.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256          // huff.txt 읽기용
#define MAX_COUNT 30            // 빈도수 측정용
#define MAX_LINE 10             // 읽어온 문자의 라인 수
#define MAX_FREQ 5              // freq.txt 읽어올 때 필요
#define MAX_ELEMENT 200         // for 허프만-트리
#define MAX_CODE 50
#define MAX_ENCODED 516         // 인코딩된 내용의 최대 글자수

typedef struct TreeNode {       // for huff-code
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {                // for huff-code
    TreeNode* ptree;
    char ch;
    int key;
} element;

typedef struct {                // for huff-code
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

typedef struct {                // for en/deconding
    char ch;
    char code[MAX_CODE];
} HuffCode;




// [1] 텍스트 파일(huff.txt)을 고려한다.
    // [huff.txt 포함조건] 이 파일은 적어도 3줄, 50개 문자를 포함하며, 영문 소문자 알파벳, 공백, 마침표, 새줄(\n), '파일끝 표시'를 포함한다.
    // [huff.txt 변환조건] 문자 빈도수를 나타내기 위해서 공백은 '-'으로, 마침표는 '.', 새줄은 '!', 파일 끝 표시는 '+'으로 나타내라.
int condition_1(char result[][MAX_BUFFER]);     // 라인 수를 리턴받는다.
void change_huff(char buffer[], char result[][MAX_BUFFER], int line);


// [2] huff.txt 파일을 읽어들여서 파일에 포함된 문자의 빈도수를 freq.txt파일에 출력하라.
void condition_2(char result[][MAX_BUFFER], int line, int count[]);
void count_freq(int count[], char result[][MAX_BUFFER], int line);
void print_freq(int count[]);
void write_freq(int count[]);


// [3] freq.txt 파일로 부터 문자와 빈도수를 읽어들여서 허프만-트리(huff-tree)를 구성하고, 이 트리를 전위 순서로 방문하면서 출력하라.
void condition_3(void);
void huffman_tree(int freq_list[], char ch_list[], int n);  // 허프만코드 생성 함수
void insert_min_heap(HeapType* h, element item);            // 삽입 함수
element delete_min_heap(HeapType* h);                       // 삭제 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right);       // 이진트리 생성 함수
void destroy_tree(TreeNode* root);                          // 이진트리 제거 함수
int is_leaf(TreeNode* root);                                // 단말노드 확인 함수
void print_array(int codes[], int n);
void print_codes(TreeNode* root, int codes[], int top);



// [4] 위에서 생성된 허프만 트리를 이용하여 각 문자에 대한 허프만 코드를 생성하고, 문자와 코드를 codes.txt 파일에 출력하라.
// 위에서 구현함


// [5] codes.txt 파일에 포함된 문자-코드를 이용하여 메시지 파일 (msg.txt)에 포함된 메시지를 인코딩하고, 그 결과를 encodedMsg.txt 파일에 출력하라.
void condition_5(void);
void read_huff(HuffCode hf[]);
int read_msg(char result[][MAX_BUFFER]);
void encode_huff(char result[][MAX_BUFFER], int line, HuffCode hf[]);
void insert_space(int idx, char list[], int len);

// [6] encodedMsg.txt 파일로부터 인코딩 메시지를 읽어들여서 3)에서 구성한 허프만 트리를 이용하여 메시지를 디코딩하여 그 결과를 출력하라.
    // (Hint : 코드를 따라서 트리 루트부터 잎노드(문자 포함)로 내려가라.)
void condition_6(void);
void erase_space(char result[]);

// [+] 최종
void result_func(void);

int main(int argc, char *argv[])
{
    int line;
    char result[MAX_LINE][MAX_BUFFER] = {0};
    int count[MAX_COUNT] = {0};
    
    // 1단계 : huff.txt 파일을 읽어들여서 문자 빈도수를 산출하여 freq.txt에 출력
    line = condition_1(result);
    condition_2(result, line, count);
    
    // 2단계 : freq.txt 파일을 이용하여 허프만-코드(huff-tree) 구성
    condition_3();
    
    // 3단계 : huff-tree를 이용하여 허프만-코드를 생성하여 codes.txt에 출력
        // condition_3()에서 구현함
    
    // 4단계 : codes.tt, msg.txt를 읽어들여서 msg.txt에 포함된 메시지를 허프만 인코딩하여 encodedMsg.txt에 출력
    condition_5();
    
    // 5단계 : encodedMsg.txt로 부터 허프만 인코딩 메시지를 읽어들여서 huff-tree를 이용하여 디코딩 후 decodedMsg.txt에 출력
    condition_6();
    
    // 6단계 : 결과 출력 : huff.txt, freq.txt, huff-tree(트리 preorder 순서로 방문 출력), codes.txt, msg.txt, encodedMsg.txt, decodedMsg.txt
    result_func();
    
    return 0;
}

void result_func()
{
    char buffer[MAX_BUFFER] = {0};
    FILE* f;
    
    
    // huff.txt를 읽기모드로 불러온다
    printf("\n");
    if(!(f = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/huff.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[huff.txt]\n");
    while(fgets(buffer, sizeof(buffer), f) != NULL)// huff.txt에서 문자열을 읽음
    {
        printf("%s", buffer);
    }
    printf("\n");
    
    fclose(f);
    
    
    // freq.txt를 읽기모드로 불러온다
    printf("\n");
    if(!(f = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/freq.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[freq.txt]\n");
    while(fgets(buffer, sizeof(buffer), f) != NULL)
    {
        printf("%s", buffer);
    }
    printf("\n");
    
    fclose(f);
    
    
    // codes.txt를 읽기모드로 불러온다
    // codes.txt내용이 허프만 preorder순으로 출력되도록 만들었다.
    printf("\n");
    if(!(f = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/codes.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[codes.txt]\n");
    while(fgets(buffer, sizeof(buffer), f) != NULL)
    {
        printf("%s", buffer);
    }
    printf("\n");
    
    fclose(f);
    
    // msg.txt를 읽기모드로 불러온다
    printf("\n");
    if(!(f = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/msg.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[msg.txt]\n");
    while(fgets(buffer, sizeof(buffer), f) != NULL)
    {
        printf("%s", buffer);
    }
    printf("\n");
    
    fclose(f);
    
    // encodedMsg.txt를 읽기모드로 불러온다
    printf("\n");
    if(!(f = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/encodedMsg.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[encodedMsg.txt]\n");
    while(fgets(buffer, sizeof(buffer), f) != NULL)
    {
        printf("%s", buffer);
    }
    printf("\n");
    
    fclose(f);
    
    // decoded.txt를 읽기모드로 불러온다
    printf("\n");
    if(!(f = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/decoded.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[decoded.txt]\n");
    while(fgets(buffer, sizeof(buffer), f) != NULL)
    {
        printf("%s", buffer);
    }
    printf("\n");
    
    fclose(f);
    
}


void read_encodedMsg(char result[])
{
    FILE* encodedMsg;
    char buffer[MAX_ENCODED];
    
    // msg.txt를 읽기모드로 불러온다
    if(!(encodedMsg = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/encodedMsg.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    
    printf("[encodedMsg.txt] 읽어오기\n");
    while(fgets(buffer, sizeof(buffer), encodedMsg) != NULL)// huff.txt에서 문자열을 읽음
    {
        printf("%s", buffer);
        strcpy(result, buffer);
    }
    printf("\n");
    
    
    fclose(encodedMsg);
}

void erase_space(char result[])
{
    int i, index = 0;
    
    for(i = 0; result[i] != '\0'; i++)
    {
        if(result[i] != ' ')
        {
            result[index] = result[i];
            index++;
        }
    }
    result[index] = '\0';
    
    printf("[스패이스 지우기]\n");
    printf("%s\n", result);
}


void decoding_huff(char read[], HuffCode hf[])
{
    FILE* decoded;
    int temp, k = 0, index = 0;
    char buffer[MAX_BUFFER] = {0};
    
    if(!(decoded = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/decoded.txt", "w")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    
    printf("[Decoding]\n");
    printf("Encoded : %s\n", read);
    
    printf("Decoded : ");
    
    for(int i = 0; i < (int)strlen(read); i++)  // 코드 끝가지 보기 (그리고 끝에 000...0 건너뛰기)
    {
        for(int j = 0; j < MAX_COUNT; j++)
        {
            temp = i;                           // 임시로 저장시키고 안에서 뺑뺑이 시켜보자.
            for(k = 0; k < (int)strlen(hf[j].code); k++)
            {  // 만약 read[i] == hf[j].code[k]라면 i와 j를 증가시켜 확인 ㄲ
                if(read[i++] != hf[j].code[k])
                    break;
            }
            if(k == (int)strlen(hf[j].code))
            {
                printf("%c", hf[j].ch);
                switch (hf[j].ch) {
                    case '-':
                        buffer[index++] = ' ';
                        break;
                    case '.':
                        buffer[index++] = '.';
                        break;
                    case '!':
                        buffer[index++] = '\n';
                        break;
                    case '+':
                        buffer[index++] = '\0';
                        break;
                    default:
                        buffer[index++] = hf[j].ch;
                }
            }
            else i = temp;
        }
    }
    printf("%s\n", buffer);
    fprintf(decoded, buffer);
    fclose(decoded);
}



void condition_6(void)
{
    char read[MAX_ENCODED] = {0};
    HuffCode hf[MAX_COUNT] = {0};
    
    
    // 인코딩된 내용 가져오기
    printf("\n");
    read_encodedMsg(read);
    printf("\n");
    
    // 인코딩된 내용 space 지우기
    erase_space(read);
    printf("\n");
    
    // codes.txt 일기
    read_huff(hf);
    
    decoding_huff(read, hf);
    
}



void insert_space(int idx, char list[], int len)
{
    memmove(list + idx + 1, list + idx, sizeof(char) * (len - idx));
    list[idx] = ' ';
}

void encode_huff(char result[][MAX_BUFFER], int line, HuffCode hf[])
{
    FILE* encodedMsg;
    char buffer[MAX_BUFFER] = {0};
    // encodeMsg.txt
    if(!(encodedMsg = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/encodedMsg.txt", "a")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
   
    
    for(int i = 0; i < line; i++)
    {
        for(int j = 0; j < (int)strlen(result[i]); j++)
        {
            if(result[i][j] >= 'a' && result[i][j] <= 'z')
            {
                strcat(buffer, hf[result[i][j] - 'a'].code);
            }
            else
            {
                switch (result[i][j]) {
                    case '-':
                        strcat(buffer, hf[26].code);
                        break;
                    case '.':
                        strcat(buffer, hf[27].code);
                        break;
                    case '!':
                        strcat(buffer, hf[28].code);
                        break;
                    case '+':
                        strcat(buffer, hf[29].code);
                        break;
                }
            }
        }
    }
    
    
    for(int i = 1; i*8 < (int)strlen(buffer); i++)
        insert_space(i*8, buffer, sizeof(buffer));
    if((int)strlen(buffer) % 8)
    {
        for(int i = 0; i <= (int)strlen(buffer) % 8; i++)
            strcat(buffer, "0");
    }
    printf("%s\n", buffer);
    fprintf(encodedMsg, "%s", buffer);
    fclose(encodedMsg);
}

int read_msg(char result[][MAX_BUFFER])
{
    FILE* msg;
    char buffer[MAX_BUFFER];
    int line = 0;
    
    // msg.txt를 읽기모드로 불러온다
    if(!(msg = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/msg.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[msg.txt 파일의 내용은 다음과 같습니다.]\n");
    while(fgets(buffer, sizeof(buffer), msg) != NULL)// huff.txt에서 문자열을 읽음
    {
        printf("%s", buffer);
        change_huff(buffer, result, line++);
        
    }
    
    // 마지막 줄 문자열의 끝을 찾는다.
    for(int i = 0; i < MAX_BUFFER; i++)
    {
        if(!(result[line-1][i]))       // 마지막 줄이 line-1이다.
        {
            result[line-1][i] = '+';
            break;
        }
    }
    
    printf("[변환 내용] 공백은 '-'으로, 마침표는 '.', 새줄은 '!', 파일 끝 표시는 '+'으로 변환한 내용은 아래와 같습니다.\n");
    for(int i = 0; i < line; i++)
    {
        printf(">> %s\n", result[i]);
    }
    
    printf("\n");
    
    return line;
}

void read_huff(HuffCode hf[])
{
    FILE* codes;
    char buffer[MAX_BUFFER] = {0};      // 파일을 읽을 때 사용할 임시 공간
    
    char* ptr;
    int i = 0, j = 0;
    
    
    if(!(codes = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/codes.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    
    // codes.txt 글의 형식을 알기때문에 문자배열의 절대 주소로 풀어냈다.
    printf("[codes.txt에서 huff-code를 읽어온다.]\n");
    while(fgets(buffer, sizeof(buffer), codes) != NULL)// codes.txt에서 문자열을 읽음
    {
        
        ptr = strtok(buffer, " ");
        ptr = strtok(NULL, " ");
        
        hf[i].ch = buffer[0];
        strcpy(hf[i].code, ptr);
        i++;
        
    }
    
    
    for(i = 0; i < MAX_COUNT; i++)
    {
        // 맨 끝에 '\n'값 지워주는 구문
        for(j = 0; j < (int)strlen(hf[i].code); j++);
        hf[i].code[j-1] = '\0';
            
        printf("ch : %c -> code : %s\n", hf[i].ch, hf[i].code);
    }
    
    printf("\n");
}


void condition_5(void)
{
    FILE* encodedMsg;
    char result[MAX_LINE][MAX_BUFFER] = {0};
    int line;
    
    HuffCode hf[MAX_COUNT] = {0};             // 글자 종류별로 허프만 코드 입력
    read_huff(hf);
    
    line = read_msg(result);                           // msg를 가져오기
    
    // encodeMsg.txt 초기화
    if(!(encodedMsg = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/encodedMsg.txt", "w")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    fclose(encodedMsg);
    
    encode_huff(result, line, hf);
}















void print_codes(TreeNode* root, int codes[], int top)
{
    FILE* codes_f;
    
    // 순서대로 출력할 때 쓴다.
    
    /*
    if(buffer[0] >= 'a' && buffer[0] <= 'z')
    {
        i = buffer[0]-'a';
        hf[i].ch = buffer[0];
    }
    else
    {
        // -(26), .(27), !(28), +(29)
        switch (buffer[0])
        {
            case '-':
                i = 26;
                hf[i].ch = buffer[0];
                break;
            case '.':
                i = 27;
                hf[i].ch = buffer[0];
                break;
            case '!':
                i = 28;
                hf[i].ch = buffer[0];
                break;
            case '+':
                i = 29;
                hf[i].ch = buffer[0];
                break;
        }
    }
    
    strcpy(hf[i].code, ptr);
    */
    
    // 단말노드이면 코드를 출력한다.
    if(is_leaf(root))
    {
        if(!(codes_f = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/codes.txt", "a")))
        {
            printf("파일 오픈 Error\n");
            exit(1);
        }
        printf("%c: ", root->ch);
        print_array(codes, top);
        
        fprintf(codes_f, "%c ", root->ch);
        for(int i = 0; i < top; i++)
            fprintf(codes_f, "%d", codes[i]);
        fprintf(codes_f, "\n");
        
        fclose(codes_f);
    }
    
    // 0을 저장하고 순환호출한다.
    if(root->left)
    {
        codes[top] = 0;
        print_codes(root->left, codes, top + 1);
    }
    
    
    // 1을 저장하고 순환호출한다.
    if(root->right)
    {
        codes[top] = 1;
        print_codes(root->right, codes, top + 1);
    }
    
}

void print_array(int codes[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}


// 단말노드 확인 함수
int is_leaf(TreeNode* root)
{
    return !(root->left) && !(root->right);
}


// 이진트리 제거 함수
void destroy_tree(TreeNode* root)
{
    if(root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}


// 이진트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 삭제 함수
element delete_min_heap(HeapType* h)
{
    int parent, child;
    element item, temp;
    
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    
    while(child <= h->heap_size)
    {
        // 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
        if((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) child++;
        if(temp.key < h->heap[child].key) break;
        
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}


// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_min_heap(HeapType* h, element item)
{
    int i;
    i = ++(h->heap_size);
    
    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while((i != 1) && (item.key < h->heap[i/2].key))
    {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;  // 새로운 노드를 삽입
}



void huffman_tree(int freq_list[], char ch_list[], int n)
{
    int i, top = 0;
    TreeNode *node, *x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];
    
    // HeapType의  초기화
    heap = (HeapType*)malloc(sizeof(HeapType));
    heap->heap_size = 0;
    
    for(i = 0; i < n; i++)
    {
        node = make_tree(NULL, NULL);               // TreeNode* make_tree(TreeNode* left, TreeNode* right);
                                                    // 새로운 노드 생성
    
        e.ch = node->ch = ch_list[i];               // 새로운 노드에 문자와 freq를 입력
        e.key = node->weight = freq_list[i];        // element에도 문자와 freq를 입력한다.
        e.ptree = node;                             // e.ptree가 새로만든 node를 가리키게 한다.
        insert_min_heap(heap, e);                   // insert함수에 첫번째로 만든 heap과 e를 보낸다.
    }
    
    for(i = 1; i < n; i++)
    {
        // 최소값을 가지는 두개의 노드를 삭제
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        
        // 두개의 노드를 합친다.
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("%d + %d -> %d \n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);
    }
    printf("\n");
    
    e = delete_min_heap(heap);      // 최종 트리
    print_codes(e.ptree, codes, top);
    destroy_tree(e.ptree);
    free(heap);
}


void condition_3()
{
    FILE* freq;
    FILE* codes_f;
    char buffer[MAX_FREQ] = {0};      // 파일을 읽을 때 사용할 임시 공간
    
    char ch_list[MAX_COUNT] = {0};
    int freq_list[MAX_COUNT] = {0};
    int i = 0;
    char *ptr;
    
    
    // 초기화
    ch_list[26] = '-';
    ch_list[27] = '.';
    ch_list[28] = '!';
    ch_list[29] = '+';
    for(i = 0; i < MAX_COUNT; i++)
    {
        if(i < 26)
            ch_list[i] = i + 'a';
        freq_list[i] = 0;
    }
    

    if(!(freq = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/freq.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[freq.txt에서 문자와 빈도수를 읽어온다.]\n");
    while(fgets(buffer, sizeof(buffer), freq) != NULL)// freq.txt에서 문자열을 읽음
    {
        ptr = strtok(buffer, " ");
        ptr = strtok(NULL, " ");
        
        if(buffer[0] >= 'a' && buffer[0] <= 'z')
        {
            i = buffer[0]-'a';
            freq_list[i] = atoi(ptr);
        }
        else
        {
            // -(26), .(27), !(28), +(29)
            switch (buffer[0])
            {
                case '-':
                    i = 26;
                    freq_list[i] = atoi(ptr);
                    break;
                case '.':
                    i = 27;
                    freq_list[i] = atoi(ptr);
                    break;
                case '!':
                    i = 28;
                    freq_list[i] = atoi(ptr);
                    break;
                case '+':
                    i = 29;
                    freq_list[i] = atoi(ptr);
                    break;
            }
        }
    }
    
    
    for(i = 0; i < MAX_COUNT; i++)
        printf("%c %d\n", ch_list[i], freq_list[i]);
    
    printf("\n\n");
    
    // codes.txt 초기화
    if(!(codes_f = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/codes.txt", "w")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    fclose(codes_f);
    
    huffman_tree(freq_list, ch_list, MAX_COUNT);
    
    printf("\n");
}


void write_freq(int count[])
{
    FILE* freq;
    // freq.txt 파일을 쓰기 모드로 열기.
    if(!(freq = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/freq.txt", "w")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    
    // freq.txt 쓰기
    for(int i = 0; i < MAX_COUNT; i++)
    {
        if(count[i])
        {
            if(i < 26)
                fprintf(freq, "%c %d\n", i+'a', count[i]);
            else
            {
                // -(26), .(27), !(28), +(29)
                switch (i)
                {
                    case 26:
                        fprintf(freq, "- %d\n", count[i]);
                        break;
                    case 27:
                        fprintf(freq, ". %d\n", count[i]);
                        break;
                    case 28:
                        fprintf(freq, "! %d\n", count[i]);
                        break;
                    case 29:
                        fprintf(freq, "+ %d\n", count[i]);
                        break;
                }
            }
        }
    }
    
    fclose(freq);   // freq.txt 닫기
}

void print_freq(int count[])    // 빈도수 검증을 위하여 출력하는 함수
{
    for(int i = 0; i < MAX_COUNT; i++)
    {
        if(count[i])
        {
            if(i < 26)
                printf("%c %d\n", i+'a', count[i]);
            else
            {
                // -(26), .(27), !(28), +(29)
                switch (i)
                {
                    case 26:
                        printf("-");
                        break;
                    case 27:
                        printf(".");
                        break;
                    case 28:
                        printf("!");
                        break;
                    case 29:
                        printf("+");
                        break;
                }
                printf(" %d\n", count[i]);
            }
        }
    }
    printf("\n");
}

void count_freq(int count[], char result[][MAX_BUFFER], int line)
{
    int len;
    
    // 한줄 단위로 빈도수 읽어오기
    for(int i = 0; i < line; i++) // 라인별로 파악하자.
    {
        len = (int)strlen(result[i]);   // 한줄의 최대 글자 개수를 파악한다.
        for(int j = 0; j < len; j++)
        {
            // 알파뱃은 if문으로 범위로 파악한다.
            // 대소문자를 통합하여 카운트한다. // 즉, 대소문자를 ASCII로 구분하여, 같은 값으로 저장해준다.
            if(result[i][j] >= 'A' && result[i][j] <= 'Z')  // 대문자
                count[result[i][j] - 'A']++;
            else if(result[i][j] >= 'a' && result[i][j] <= 'z') // 소문자
                count[result[i][j] - 'a']++;
            else
            {
                // 알파벳 26 + 공백(-) + 마침표(.) + 새줄(!) + 파일끝표시(+) = 30
                switch (result[i][j])
                {
                    case '-':
                        count[26]++;
                        break;
                    case '.':
                        count[27]++;
                        break;
                    case '!':
                        count[28]++;
                        break;
                    case '+':
                        count[29]++;
                        break;
                }
            }
        }
    }
}

void condition_2(char result[][MAX_BUFFER], int line, int count[])
{
    count_freq(count, result, line);
    print_freq(count);
    write_freq(count);
}


// 문자를 치환해준다.
void change_huff(char buffer[], char result[][MAX_BUFFER], int line)
{
    int len = (int)strlen(buffer);

    for(int i = 0; i < len; i++)
    {
        switch (buffer[i]) {
            case ' ':
                buffer[i] = '-';
                break;
            case '.':
                buffer[i] = '.';
                break;
            case '\n':
                buffer[i] = '!';
                break;
        }
        result[line][i] = buffer[i];
    }
}


int condition_1(char result[][MAX_BUFFER])
{
    FILE* huff;                         // huff 파일을 불러오기 위한 자료
    char buffer[MAX_BUFFER] = {0};      // 파일을 읽을 때 사용할 임시 공간
    int line = 0;
    
    // huff.txt를 읽기모드로 불러온다
    if(!(huff = fopen("/Users/skan/Documents/git/Data_structure/Data_structure/Report/huff.txt", "r")))
    {
        printf("파일 오픈 Error\n");
        exit(1);
    }
    
    printf("[huff.txt 파일의 내용은 다음과 같습니다.]\n");
    while(fgets(buffer, sizeof(buffer), huff) != NULL)// huff.txt에서 문자열을 읽음
    {
        printf("%s", buffer);
        change_huff(buffer, result, line++);
    }
    printf("\n");
    
    // 마지막 줄 문자열의 끝을 찾는다.
    for(int i = 0; i < MAX_BUFFER; i++)
    {
        if(!(result[line-1][i]))       // 마지막 줄이 line-1이다.
        {
            result[line-1][i] = '+';    // 마지막줄에 '+'를 추가해준다.
            break;
        }
    }
    
    printf("[변환된 huff.txt 내용]\n(공백은 '-'으로, 마침표는 '.', 새줄은 '!', 파일 끝 표시는 '+'으로 변환한 내용은 아래와 같습니다.)\n");
    for(int i = 0; i < line; i++)
    {
        printf(">> %s\n", result[i]);
    }
    printf("\n");
    
    // 읽기모드로 불러온 huff파일과 연결을 닫는다.
    fclose(huff);
    return line;
}
