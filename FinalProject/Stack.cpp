#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

using namespace std;
/*Constructor for the Stack Data Structure*/
struct stack *
newStack(){
    	struct stack *s = (stack*) malloc(sizeof(struct stack));
	s->front = newStackNode();
	s->rear = newStackNode();
	s->size = 0;
	return s;
}

/*Constructor for the Stack Data Structure*/
struct stackNode *newStackNode(){
	struct stackNode *s = (stackNode*) malloc(sizeof(struct stackNode));
	s->node = NULL;
	s->next = NULL;
	return s;
}

/*'Pushes' a Binary Node structure to the front of the Stack (LIFO)*/
void push(struct stack *s, struct binaryTreeNode *n, int optionD){

	//If the stack is empty, set the front and rear to 'n'
	if (isStackEmpty(s) == 1){
		s->front->node = n;
		s->front->next = NULL;
		s->rear->node = n;
		s->rear->next = NULL;
		s->start = clock();
	}
	//append the node to the Stack and move the 'front' pointer
	else{
		struct stackNode *temp = (stackNode*) malloc(sizeof(struct stackNode));
		temp->next = s->front;
		temp->node = n;
		s->front = temp;
	}
	s->size += 1;
	return;
}


/*'Pops' a Binary Node structure from the top of the Stack (LIFO)*/
struct stackNode *
pop(struct stack *s, int optionD){

    	if (isStackEmpty(s) == 0){
    		struct stackNode *tNode = (stackNode*) malloc(sizeof(struct stackNode));
		//If the stack size = 1
		if(s->front == s->rear){
			tNode = s->front;	
			s->front = NULL;
			s->rear = NULL;
		}
		//The stack is larger than 1
		else{
			tNode = s->front;
			s->front = s->front->next;
		}
		s->size -= 1;
		return tNode;
    	}
    	else{
        	return NULL;
    	}
}

/*Helper method to determine if the Stack Structure is Empty*/
int 
isStackEmpty(struct stack *s){

    	if (s->size == 0){
		return 1;
    	}
    	else{
		return 0;
    	}
}

/*Helper method to determine if the Node parameter is the Last Node in the Stack Structure*/
int 
isLastStackNode(struct stackNode *tNode, struct stack *s){
    	if ((tNode == s->rear) && (tNode == s->front)){
       		return 1;
    	}
    	else{
        	return 0;
    	}
}

/*Method that prints the contents of the Stack Structure*/
void 
printStack(struct stack *s){
	//printf("While printing stack");
	if(isStackEmpty(s) == 0){
		struct stackNode *tNode = (stackNode*) malloc(sizeof(struct stackNode));
		tNode = s->front;
		printf("Stack Structure is \n");
		printf("Stack size is %d\n",s->size);
		while(tNode->next != NULL){
			printf("%d->",tNode->node->value);
			tNode = tNode->next;
		}
		printf("%d\n",tNode->node->value);
	}	
	return;

}

