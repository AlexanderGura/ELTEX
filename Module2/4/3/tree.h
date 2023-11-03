#ifndef THREE_H_
#define THREE_H_

typedef char typeData;

typedef struct Tree
{
	typeData data;
	int height;
	struct Tree *left;
	struct Tree *right;
} Tree;

Tree* initNode(typeData );
static int getHeight(Tree *);
static int diffHeight(Tree *);
static void updateHeight(Tree *);
static Tree* rotateRight(Tree *);
static Tree* rotateLeft(Tree *);
static Tree* balance(Tree *);
static Tree* findMin(Tree *);
static Tree* removeMin(Tree *);
Tree* insert(Tree *, typeData );
Tree* removeNode(Tree *, typeData );
void printTree(Tree *);
void deleteTree(Tree **);

#endif
