#ifndef Heaptree_H_
#define Heaptree_H_
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

/*Structure for Binary Tree Node*/
struct binaryTreeNode{

	/*vars*/
	int value;
	struct binaryTreeNode *left, *right, *parent;

};

/*Methods*/
struct binaryTreeNode *newBinaryTreeNode();

/*Structure for Binary Tree*/
struct binaryTree{

	/*vars*/
	struct binaryTreeNode *root;
	int size;
		
};
	
/*methods*/
struct binaryTree *newTree();
void insert(struct binaryTree *,struct binaryTreeNode *);
int isHeapEmpty(struct binaryTree *);
void heapify(struct binaryTreeNode *, int optionD);
void extractTop(struct stack *, int optionD);

//Traversals
void preOrderTraversal(struct binaryTreeNode *);
void inOrderTraversal(struct binaryTreeNode *);
void postOrderTraversal(struct binaryTreeNode *);

#endif
