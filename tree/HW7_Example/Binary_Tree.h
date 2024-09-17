#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef char Element;

typedef struct tTreeNode
{
	Element data;
	struct tTreeNode* left, * right;
}TreeNode;

TreeNode* CreateTree(TreeNode* left, Element item, TreeNode* right)
{
	TreeNode* pNewNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (pNewNode == NULL)
		return;

	pNewNode->data = item;
	pNewNode->left = left;
	pNewNode->right = right;

	return pNewNode;
}

TreeNode* LeftTree(TreeNode* root)
{
	if (root == NULL)
		return NULL;
	else
	{
		return root->left;
	}
}

Element TreeData(TreeNode* root)
{
	if (root == NULL)
		return NULL;
	else
	{
		return root->data;
	}
}

TreeNode* RightTree(TreeNode* root)
{
	if (root == NULL)
		return NULL;
	else
	{
		return root->right;
	}
}

bool IsEmpty(TreeNode* root)
{
	if (root == NULL)
		return true;
	else
		return false;
}

void DestroyTree(TreeNode* root)
{
	if (root == NULL)
		return;

	DestroyTree(root->left);
	DestroyTree(root->right);
	free(root);
}