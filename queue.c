#include<stdio.h>
#include<stdlib.h>
#include"events.h"

/*
  We will use 2 queues  - implemented using linked lists .
  One queue for storing busy threads and another queue for storing idle threads
  */


//To allocate memory for queue
queue* initialize_queue(){
	queue* q = (queue*)malloc(sizeof(queue));
	q->size = 0;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void enqueue(queue* q, node* e){
	if (q->front == NULL){
		q->front = q->rear = e;
	}
	else{
		q->rear->next = e;
		q->rear = e;
	}
	q->size++;
}

node* dequeue(queue* q){
	if (q->size > 0){
		node* temp = q->front;
		q->front = q->front->next;
		q->size--;
		temp->next = NULL;
		return temp;
	}
	else{
		return NULL;
	}
}


void display_queue(queue* q){
	node *p = q->front;
	int i ;
	if (p == NULL){
		printf("All threads are busy\n");
	}
	for ( i = 0; i < q->size ; ++i){
		if (p->th->e != NULL) {
			printf("Thread no - %d\n",i);
			printf("Customer = %d\n",p->th->e->c.user_id);
			printf("Customer priority = %d\n",p->th->e->c.priority);
			printf("Event start time is %d\n",p->th->e->startTime);
			printf("\n\n");
		}
		else{
			printf("thread %d is idle\n",i);
		}
		p = p->next;
	}
}

// To create a new node from a given thread
node* new_node(thread* th){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->th = th;
	newNode->next = NULL;
	return newNode;
}


