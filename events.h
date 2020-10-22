#include<stdio.h>
#include<time.h>


typedef struct customer {
	int user_id;
	int priority;
}customer;

typedef struct event {
	customer c;
	int startTime;
}event;

typedef struct priority_queue{
	unsigned int size;
	event* arr;
}priority_queue;

typedef struct thread {
	int is_idle;
	event* e;
}thread;

typedef struct node{
	thread* th;
	struct node* next;
}node;

typedef struct queue {
	unsigned int size;
	node* front;
	node* rear;
}queue;

//typedef struct queue_node queue_node;

void manage_events(queue* idle_threads , queue** busy_threads , priority_queue* events,int current_time,int time_per_event);



priority_queue* priority_queue_initialize();
void priority_queue_insert(priority_queue* pq, event e);
event priority_queue_delete(priority_queue* pq);
void display_pq(priority_queue* pq);

queue* initialize_queue();
void enqueue(queue* q, node* e);
node* dequeue(queue* q);
void display_queue(queue* q);
node* new_node(thread* th);
void delay(int number_of_seconds);