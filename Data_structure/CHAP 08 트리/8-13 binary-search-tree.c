//
//  8-13 binary-search-tree.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/09/27.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;


// 순환적인 탐색 함수
TreeNode* search(TreeNode* node, int key)
{
    // 만약에 노드가 비어있다면,
    if(node == NULL) return NULL;

    // 노드와 key의 대소 비교
    if(key == node->key) return node;
    else if(key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}


TreeNode* new_node(int item)
{
    TreeNode* temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}


TreeNode* insert_node(TreeNode* node, int key)
{
    // 트리가 공백이면 새로운 노드를 반환한다.
    if(node == NULL) return new_node(key);
    
    // 그렇지 않으면 순환적으로 트리를 내려간다.
    if(key < node->key)
        node->left = insert_node(node->left, key);
    else if(key > node->key)
        node->right = insert_node(node->right, key);
    
    
    // 변경된 루트 포인터를 반환한다.
    return node;
}


TreeNode* min_value_node(TreeNode* node)
{
    TreeNode* current = node;
    
    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while(current->left != NULL)
        current = current->left;
    
    return current;
}


// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고
// 새로운 루트 노드를 반환한다.
TreeNode* delete_node(TreeNode* root, int key)
{
    if(root == NULL) return root;
    
    // 키와 루트의 값을 비교하여 범위를 좁혀간다.
    if(key < root->key)
        root->left = delete_node(root->left, key);
    else if(key > root->key)
        root->right = delete_node(root->right, key);
    else    // 키와 루트와 같으면 이 노드를 삭제하면 됨
    {
        
        if (root->left == NULL)         // 첫번째일 경우
        {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)    // 마지막일 경우
        {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // 중간일 경우
        TreeNode* temp = min_value_node(root->right);
        
        // 중위 순회시 후계 노드를 복사한다.
        root->key = temp->key;
        
        // 중위 순회시 후계 노드를 삭제한다.
        root->right = delete_node(root->right, temp->key);
    }
    
    return root;
}


// 중위 순회
void inorder(TreeNode* root)
{
    if(root)
    {
        inorder(root->left);            // 왼쪽 서브트리 순회
        printf("[%d] ", root->key);     // 노드 방문
        inorder(root->right);           // 오른쪽 서브트리 순회
    }
}


int main(void)
{
    TreeNode* root = NULL;
    
    root = insert_node(root, 30);
    root = insert_node(root, 20);
    root = insert_node(root, 10);
    root = insert_node(root, 40);
    root = insert_node(root, 50);
    root = insert_node(root, 60);
    
    printf("이진 탐색 트리 중위 순회 결과 \n");
    inorder(root);
    printf("\n\n");
    if(search(root, 30) != NULL)
        printf("이진 탐색 트리에서 30을 발견함 \n");
    else
        printf("이진 탐색 트리에서 30을 발견못함 \n");
    
    return 0;
}
