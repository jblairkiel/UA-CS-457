#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Stack.h"

using namespace std;

/* Constructor for the Queue data structure*/
struct queue *newQueue(){
	struct queue *q = (queue*) malloc(sizeof(struct queue));
	q->front = newQueueNode();
	q->rear  = newQueueNode();
	q->size = 0;
	return q;
}

/* Constructor for the Queue Node Structure*/
struct queueNode *newQueueNode(){
	struct queueNode *q = (queueNode*) malloc(sizeof(struct queueNode));
	q->node = NULL;
	q->next = NULL;
	return q;
}

/*Method that 'adds' the node parameter to the Queue (FIFO)
	Also builds the Heap Structure in level order.*/
void
enqueue(struct queue *q, struct stack *s, struct binaryTreeNode *n, int optionD){
	//Add node to the Queue
        if (isQueueEmpty(q) == 1){
		q->front->node = n;
		q->front->next = NULL;
		q->rear = q->front;
        }
        else{
		struct queueNode *temp = (queueNode*) malloc(sizeof(struct queueNode));
		temp->next = NULL;
		temp->node = n;
                q->rear->next = temp;
                q->rear = temp;

		//'Adds' the Node to the Heap in level order (priority of left to right)
		if(q->front->node->left == NULL){
			q->front->node->left = n;	
			n->parent = q->front->node;
		}
		else if(q->front->node->right == NULL){
			q->front->node->right = n;
			n->parent = q->front->node;
		}
		else{
			//The front of the queue has full children so dequeue it
			dequeue(q,s, optionD);
			q->front->node->left = n;
			n->parent = q->front->node;
		}	
        }
	q->size += 1;
	return;
}

/*'Removes' the Node that has 'Waited' the Longest in the Queue
	Also pushes the Node to our Stack Structure*/
struct binaryTreeNode * 
dequeue(struct queue *q, struct stack *s, int optionD){
        struct binaryTreeNode *temp = (binaryTreeNode*) malloc(sizeof(struct binaryTreeNode));
	if (isQueueEmpty(q) == 0){
		if (q->front == q->rear){
			temp = q->front->node;
			q->front->node = NULL;
			q->front->next = NULL;
			q->rear->node = NULL;
			q->rear->next = NULL;
		}
		else{
			temp = q->front->node;
			q->front = q->front->next;
		}
		q->size -= 1;
		push(s,temp, optionD);
		return temp;
	}
	else{
		return NULL;
	}
}

/*Helper Method adds the rest of the queue to our stack*/
void
dequeueRest(struct queue *q, struct stack *s, int optionD){
	while(isQueueEmpty(q) == 0){
		dequeue(q,s,optionD);
	}
}

/*Helper method that determines if a Queue is empty*/
int 
isQueueEmpty(struct queue *q){

	//printf("Checking if empty\n");
	if (q->size == 0){
		//printf("Queue is empty\n");
		return 1;
	}
	else{
		//printf("Queue is not empty\n");
		return 0;
	}

}

/*Helper method that determines if the Node parameter is the last Node in the Structure*/
int
isLastQueueNode(struct queueNode *tNode){
	if(tNode->next == NULL){
		return 1;
	}
	else{
		return 0;
	}
}


/*Method that prints the Linked List structure of the Queue*/
void 
printQueue(struct queue *q){
        if(isQueueEmpty(q) == 0){
                struct queueNode *tNode = (queueNode*) malloc(sizeof(struct queueNode));
		tNode = q->front;
                printf("\nQueue Structure is \n");
		while(tNode->next != NULL){
                        printf("%d->",tNode->node->value);
                        tNode = tNode->next;
                }
                printf("%d\n",tNode->node->value);
        }
	return;
}
