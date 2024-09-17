#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef char element;

typedef struct treenode {
	element data;
	struct treenode* left, * right;
}treenode;

treenode* createtree(treenode* left, element item, treenode* right)
{
	treenode* pnewnode = NULL;

	pnewnode = (treenode*)malloc(sizeof(treenode));
	if (pnewnode == NULL)
		return NULL;

	pnewnode->data = item;

	pnewnode->left = left;
	pnewnode->right = right;
	
	return pnewnode;
}
element treedata(treenode* node)
{
	if (node == NULL)
	{
		printf("the node is empty.\n");
		return 0;
	}

	return node->data;
}
void preorder(treenode* root)
{
	if (root == NULL)
		return;

	printf("%c", root->data);
	preorder(root->left);
	preorder(root->right);
}
void inorder(treenode* root)
{
	if (root == NULL)
		return;

	inorder(root->left);
	printf("%c", root->data);
	inorder(root->right);
}
void postorder(treenode* root)
{
	if (root == NULL)
		return;

	postorder(root->left);
	postorder(root->right);
	printf("%c", root->data);
}
void destroytree(treenode* root)
{
	if (root == NULL)
		return;

	destroytree(root->left);
	destroytree(root->right);
	free(root);
}