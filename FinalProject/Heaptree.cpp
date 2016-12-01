#include <stdio.h>
#include <stdlib.h>
#include "Heaptree.h"

using namespace std;

/*Constructor for Binary Tree Node*/
struct binaryTreeNode *
newBinaryTreeNode(){
	struct binaryTreeNode *n = (binaryTreeNode*) malloc(sizeof(struct binaryTreeNode));
	n->value = (int)NULL;
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
	return n;
}

/*Inserts a Binary Tree Node into the Tree*/
void 
insert(struct binaryTree *t,struct binaryTreeNode *n){

	if(isHeapEmpty(t) == 1){
		t->root = n;
		t->size += 1;
	}
	return;
}

/*Helper Method that determines if the Tree is empty.*/
int 
isHeapEmpty(struct binaryTree *t){

	if(t->size == 0){
		return 1;
	}
	else{
		return 0;	
	}

}

/*Method that 'Sifts-down' a Node until it reaches the proper position*/
void
heapify(struct binaryTreeNode *n, int optionD){

	struct binaryTreeNode *tNode = newBinaryTreeNode();
	tNode = n;
	//Max Heap for decreasing
	if(optionD == 1){
		//Find the most extreme child
		if(n->left != NULL){
			if(n->left->value >= tNode->value){
				tNode = n->left;	
			}	
		}		
		if(n->right != NULL){
			if(n->right->value >= tNode->value){
				tNode = n->right;	
			}	
		}
		//Swap the node's value with the most extreme child
		if(tNode != n){
			int temp = tNode->value;
			tNode->value = n->value;
			n->value = temp;
			heapify(tNode, optionD);	
		}
		return;
	}
	//Min-Heap
	else{
		//Find the most extreme child
		if(n->left != NULL){
			if(n->left->value <= tNode->value){
				tNode = n->left;
			}
		}
		if(n->right != NULL){
			if(n->right->value <= tNode->value){
				tNode = n->right;	
			}	
		}
		//Swap the node's value with the most extreme child
		if(tNode != n){
			int temp = tNode->value;
			tNode->value = n->value;
			n->value = temp;
			heapify(tNode, optionD);
		}
		return;	
	}
}

/*Removes the Root of the Tree*/
void 
extractTop(struct stack *s, int optionD){
	if(s->size != 1){

		//Replace root with last element in heap
		int temp;
		temp = s->rear->node->value;
		printf("%d ",temp);
		s->rear->node->value = s->front->node->value;
		s->front->node->value = temp;
		
		if(s->front->node->parent->left == s->front->node){
			s->front->node->parent->left = NULL;
		}
		else{
			s->front->node->parent->right = NULL;
		}
		//Prune the swap value
		pop(s,optionD);

		//Siftdown the new 'root' value 
		heapify(s->rear->node,optionD);	
	}
	else{
		printf("%d ",s->rear->node->value);			
		pop(s,optionD);
	}
	return;

}


void 
preOrderTraversal(struct binaryTreeNode *node){

        if (node){
                //print node
                printf("|%d|\n", node->value);

                //traverse left
                if (node->left){
                        preOrderTraversal(node->left);
                }

                //traverse right
                if (node->right){
                        preOrderTraversal(node->right);
                }
        }
	return;
}

void 
inOrderTraversal(struct binaryTreeNode *node){

        if (node){
                //traverse left
                if (node->left){
                        inOrderTraversal(node->left);
                }

                //print node
                printf("%d ", node->value);

                //traverse right
                if (node->right){
                        inOrderTraversal(node->right);
                }
        }
	return;
}

void 
postOrderTraversal(struct binaryTreeNode *node){

        if (node){
                //traverse left
                if (node->left){
                        postOrderTraversal(node->left);
                }

                //traverse right
                if (node->right){
                        postOrderTraversal(node->right);
                }

                //print node
                printf("%d ", node->value);
        }
	return;
}
