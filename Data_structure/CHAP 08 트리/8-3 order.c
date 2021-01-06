//
//  8-3 order.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/09/24.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;


//             15
//      4              20
//    1             16    25

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode *root = &n6;


// 중위 순회
void inOrder(TreeNode *root)
{
    if(root != NULL)
    {
        inOrder(root->left);            // 왼쪽 서브트리 순회
        printf("[%d] ", root->data);    // 노드 방문
        inOrder(root->right);           // 오른쪽 서브트리 순회
    }
}

// 전위 순회
void preOrder(TreeNode *root)
{
    if(root != NULL)
    {
        printf("[%d] ", root->data);    // 노드 방문
        preOrder(root->left);           // 왼쪽 서브트리 순회
        preOrder(root->right);          // 오른쪽 서브트리 순회
    }
}


// 후위 순회
void postOrder(TreeNode *root)
{
    if(root != NULL)
    {
        postOrder(root->left);          // 왼쪽 서브트리 순회
        postOrder(root->right);         // 오른쪽 서브트리 순회
        printf("[%d] ", root->data);    // 노드 방문
    }
}


int main(void)
{
    printf("중위 순회=");
    inOrder(root);
    printf("\n");
    
    printf("전위 순회=");
    preOrder(root);
    printf("\n");
    
    printf("중위 순회=");
    postOrder(root);
    printf("\n");
    
    return 0;
}
