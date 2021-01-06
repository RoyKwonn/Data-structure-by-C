//
//  8-7 calc-dir-size.c
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


int calc_dir_size(TreeNode *root)
{
    int left_size, right_size;
    
    if(root == NULL) return 0;
    
    left_size = calc_dir_size(root->left);
    right_size = calc_dir_size(root->right);
    return (root->data + left_size + right_size);
}


int main(void)
{
    TreeNode n5 = { 500, NULL, NULL };
    TreeNode n4 = { 200, NULL, NULL };
    TreeNode n3 = { 100, &n4, &n5 };
    TreeNode n2 = { 50, NULL, NULL };
    TreeNode n1 = { 0, &n2, &n3 };
    
    printf("디렉토리의 크기 = %d\n", calc_dir_size(&n1));
}
