//
//  8-6 evaluate.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/09/25.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;


//             +
//      *              +
//    1   4         16    25

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, NULL, NULL };
TreeNode n3 = { '*', &n1, &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { '+', &n4, &n5 };
TreeNode n7 = { '+', &n3, &n6 };
TreeNode *Exp = &n7;


// 수식 계산 함수
int evaluate(TreeNode *root)
{
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        return root->data;
    else
    {
        int op1 = evaluate(root->left);
        int op2 = evaluate(root->right);
        printf("%d %c %d을 계산합니다.\n", op1, root->data, op2);
        switch (root->data) {
            case '+':
                return op1 + op2;
            case '-':
                return op1 - op2;
            case '*':
                return op1 * op2;
            case '/':
                return op1 / op2;
        }
    }
    return 0;
}


int main(void)
{
    printf("수식의 값은 %d 입니다. \n", evaluate(Exp));
    
    return 0;
}

