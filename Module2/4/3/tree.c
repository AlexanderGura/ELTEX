#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Tree* initNode(typeData data)
{
	Tree *tree = (Tree*) malloc(sizeof(Tree));
	tree->data = data;
	tree->height = 1;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

static int getHeight(Tree *root)
{
	return root == NULL ? 0 : root->height;
}

static int diffHeight(Tree *root)
{
	return getHeight(root->right) - getHeight(root->left);
}

static void updateHeight(Tree *root)
{
	int r_l = getHeight(root->left);
	int r_h = getHeight(root->right);
	root->height = r_l > r_h ? r_l + 1: r_h + 1;
}

static Tree* rotateRight(Tree *root)
{
	Tree *tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	updateHeight(root);
	updateHeight(tmp);
	return tmp;
}

static Tree* rotateLeft(Tree *root)
{
	Tree *tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	updateHeight(root);
	updateHeight(tmp);
	return tmp;
}

static Tree* balance(Tree *root)
{
	updateHeight(root);
	if (diffHeight(root) == 2)
	{
		if (diffHeight(root->right) < 0)
			root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	if (diffHeight(root) == -2)
	{
		if (diffHeight(root->left) > 0)
			root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	return root;
}

static Tree* findMin(Tree *root)
{
	return (root->left == NULL) ? root : findMin(root->left);
}

static Tree* removeMin(Tree *root)
{
	if (root->left == NULL)
		return root->right;
	root->left = removeMin(root->left);
	return balance(root);
}


Tree* insert(Tree *root, typeData data)
{
	if (root == NULL)
	{
		return initNode(data);
	}
	if (root->data > data)
		root->left = insert(root->left, data);
	else
		root->right = insert(root->right, data);
	return balance(root);
}

Tree* removeNode(Tree *root, typeData data)
{
	if (root == NULL)
		return NULL;
	if (data < root->data)
		root->left = removeNode(root->left, data);
	else if (data > root->data)
		root->right = removeNode(root->right, data);
	else
	{
		Tree *l = root->left;
		Tree *r = root->right;
		free(root);
		if (r == NULL)
			return l;
		Tree *min = findMin(r);
		min->right = removeMin(r);
		min->left = l;
		return balance(min);
	}
	return balance(root);
}

void printTree(Tree *root)
{
	if (root != NULL)
	{
		printTree(root->left);
		printf("%c ", root->data);
		printTree(root->right);
	}
}

void deleteTree(Tree **root)
{
	if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
 		free(*root);
 		*root = NULL;
	}
}
