#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
	Tree *root = initNode(97);
	for (int i = 98; i < 110; i++)
		root = insert(root, i);
	root = removeNode(root, 4);
	printTree(root);
	printf("\n");
	printTree(root->left);
	printf("\n%c\n", root->data);
	printTree(root->right);
	printf("\n");
	deleteTree(&root);
	printTree(root);
	return 0;
}
