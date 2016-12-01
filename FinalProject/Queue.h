#include "Heaptree.h"
#include "Stack.h"
#ifndef Queue
#define Queue

/*Structure for Queue Data Structure*/
struct queue{

	/*vars*/
	struct queueNode *front;
	struct queueNode *rear;
	int size;

};

/*Methods*/
struct queueNode *newQueueNode();
void enqueue(struct queue *, struct stack *,struct binaryTreeNode *, int OptionD);
struct binaryTreeNode *dequeue(struct queue *, struct stack *, int optionD);
void dequeueRest(struct queue *, struct stack *, int optionD);
int isQueueEmpty(struct queue *);
int isLastQueueNode(struct queueNode *);
void printQueue(struct queue *);

/*Structure for the Queue Node Structure
	This is a Node that holds our Binary Tree Nodes*/
struct queueNode{

	/*vars*/
	struct binaryTreeNode *node;
	struct queueNode *next;
};

/*methods*/
struct queue *newQueue();

#endif
