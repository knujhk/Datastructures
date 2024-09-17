#define _CRT_SECURE_NO_WARNINGS
#include "Binary_Tree.h"
#include "Tree_Queue.h"
#include <stdio.h>

char tmp[20];
void Preorder(TreeNode* root);
void Inorder(TreeNode* root);
void Postorder(TreeNode* root);
void BreadthFrist(TreeNode* root);

int main(void)
{
	char c;
	int i = 0;
	printf("Input a string : ");
	scanf("%s", tmp);
	printf("\n");
	Queue* queue = CreateQueue();

	c = tmp[i];
	TreeNode * root = CreateTree(NULL, c, NULL);
	Enqueue(queue, root);
	i++;
	for(i ; i<strlen(tmp); i++)
	{
		c = tmp[i];
		
		TreeNode * p = CreateTree(NULL, c, NULL);
		if (queue->front->item->left == NULL)
		{
			Enqueue(queue, p);
			queue->front->item->left = p;
		}
		else if (queue->front->item->left != NULL)
		{
			Enqueue(queue, p);
			queue->front->item->right = p;
			Dequeue(queue);
		}

	}



	printf("Pre-order : ");  Preorder(root);
	printf("\n\n");
	printf("In-order : "); Inorder(root);
	printf("\n\n");
	printf("Post-order : "); Postorder(root);
	printf("\n\n");
	printf("Breadth First : "); BreadthFrist(root);
	return 0;
}

void Preorder(TreeNode* root)
{
	if (root == NULL)
		return;

	printf("%c", root->data);
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder(TreeNode* root)
{
	if (root == NULL)
		return;
	Inorder(root->left);
	printf("%c", root->data);
	Inorder(root->right);
}

void Postorder(TreeNode* root)
{
	if (root == NULL)
		return;
	Postorder(root->left);
	Postorder(root->right);
	printf("%c", root->data);
}

void BreadthFrist(TreeNode* root)
{
	char c;
	TreeNode* tmp;
	Queue* q1 = CreateQueue();
	Enqueue(q1, root);
	while (1)
	{
		Enqueue(q1, q1->front->item->left);
		if (q1->front->item->left == NULL)
			break;
		Enqueue(q1, q1->front->item->right);
		if (q1->front->item->right == NULL)
			break;
		tmp = Dequeue(q1);
		c = tmp->data;
		printf("%c", c);
	}
	while (q1->count > 0)
	{
		tmp = Dequeue(q1);
		if (tmp == NULL)
			break;
		c = tmp->data;
		printf("%c", c);
	}
}