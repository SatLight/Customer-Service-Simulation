#include <stdio.h>
#include <stdlib.h>
#include "events.h"
#include <time.h>
/* Simulate Customer Service

	Name - Satyam Priyam SRN - PES2201800595
	Name - Sanketh B.K SRN - PES2201800769
	
*/

/*
	Number of threads and time required for completion of one event are taken from user 

	queues 
	   idle threads - used to store idle threads 
	   busy threads - used to store threads which are in process 

	priority queue 
	    event_queue  -  request from customers are converted into events and stored in priority 
		queue

	time() function is used to measure the current time
	
*/
int main()
{
	int no_of_threads, time_per_event, i;

	printf("Enter the number of  threads\n");
	scanf("%d", &no_of_threads);
	fflush(stdin);
	queue *idle_threads = initialize_queue();

	if (no_of_threads >500 ){
		printf("Maximum limit is 500\n");
		return 0;
	}

	if (no_of_threads <= 0){
		printf("Minimum threads should be 1\n");
		return 0;
	}
	for (i = 0; i < no_of_threads; ++i)
	{
		thread *th;
		th = (thread *)malloc(sizeof(thread));
		th->is_idle = 1;
		th->e = NULL;
		node *n = new_node(th);
		enqueue(idle_threads, n);
	}

	queue *busy_threads = initialize_queue();
	printf("size of idle threads %d\n", idle_threads->size);
	display_queue(idle_threads);

	printf("Enter the time required for completion of one event in seconds\n");
	scanf("%d", &time_per_event);

	if (time_per_event <= 0){
		printf("Minimum time given should be 1 seconds\n");
		return 0;
	}
	int choice = 1;
	customer k;
	priority_queue *event_queue = priority_queue_initialize();
	time_t start_time;
	time(&start_time);

	time_t current_time;

	while (choice != 0)
	{
		printf("Enter your choice\n1.Add a new customer\n2.Print the contents of event queue\n");
		printf("3.Display the idle threads\n4.Display the busy threads\n");

		scanf("%d", &choice);

		time(&current_time);
		current_time -= start_time;
		switch (choice)
		{
		case 1:
			printf("Enter the coustomer id\n");
			scanf("%d", &k.user_id);
			fflush(stdin);
			printf("Enter his priority\n");
			scanf("%d", &k.priority);
			event e;
			e.c = k;
			priority_queue_insert(event_queue, e);
			break;
		case 2:
			display_pq(event_queue);
			break;
		case 3:
			display_queue(idle_threads);
			break;
		case 4:
			display_queue(busy_threads);
			break;

		default:
			return 0;
		}
		manage_events(idle_threads, &busy_threads, event_queue, current_time, time_per_event);
		printf("Current time = %d seconds\n", current_time);
	}
}