#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Binary_Tree.h"
#include "Tree_Queue.h"

treenode* complete_bt(char* string);
void breathfirst(treenode* root);

int main()
{
	char string[31];

	printf("input a string : ");
	scanf("%s", string);
	printf("\n");

	treenode* tree1 = complete_bt(string);
	
	printf("pre-order : ");
	preorder(tree1);
	printf("\n\n");

	printf("in-order : ");
	inorder(tree1);
	printf("\n\n");

	printf("post-order : ");
	postorder(tree1);
	printf("\n\n");

	printf("breath first : ");
	breathfirst(tree1);
	printf("\n");

	return 0;
}
treenode* complete_bt(char* string)
{
	int i;
	QUEUE* nodeq = createqueue();
	QUEUE* bfsq = createqueue();
	treenode* root, *bt_root;

	for (i = 0; i < strlen(string); i++) {
			//인풋 스트링 구성하는 문자들 각각을 데이터로 하는 트리 노드들 생성
		enqueue(nodeq, createtree(NULL, string[i], NULL));
	}

	bt_root = dequeue(nodeq);
	
	for (root = bt_root; root != NULL ; root = dequeue(bfsq))	
	{
		root->left = dequeue(nodeq);
		if (root->left != NULL)
			enqueue(bfsq, root->left);

		root->right = dequeue(nodeq);
		if (root->right != NULL)
			enqueue(bfsq, root->right);
	}

	return bt_root;
}
void breathfirst(treenode* root)
{
	QUEUE* bfsq = createqueue();

	for (; root != NULL; root = dequeue(bfsq))
	{
		printf("%c", root->data);

		if (root->left != NULL)
			enqueue(bfsq, root->left);

		if (root->right != NULL)
			enqueue(bfsq, root->right);
	}

	destroyqueue(bfsq);
}