#include <stdio.h>
#include <stdlib.h>
#include "events.h"

/*
   priority queue is used to store the customers in order of priority 
   customers with higher priority are serviced first
*/
priority_queue *priority_queue_initialize()
{
	priority_queue *pq = (priority_queue *)malloc(sizeof(priority_queue));
	pq->size = 0;
	pq->arr = (event *)malloc(500 * sizeof(event));		// 500 is the no. of requests.
	return pq;
}

void bottom_up_heapify(event *arr, int i)
{
	int parent = (i - 1) / 2;
	if (arr[i].c.priority > arr[parent].c.priority)
	{
		event temp = arr[i];
		arr[i] = arr[parent];
		arr[parent] = temp;

		bottom_up_heapify(arr, parent);
	}
}

void priority_queue_insert(priority_queue *pq, event e)
{
	if (pq->size < 500)
	{
		pq->arr[pq->size++] = e;
		bottom_up_heapify(pq->arr, pq->size - 1);
	}
	else
	{
		printf("Can't insert more than 500 people\n");
	}
}

void top_down_heapify(event *arr, int size, int start)
{

	int largest = start;

	int l = 2 * start + 1;
	int r = 2 * start + 2;

	if (l < size && arr[l].c.priority > arr[largest].c.priority)
	{
		largest = l;
	}

	if (r < size && arr[r].c.priority > arr[largest].c.priority)
	{
		largest = r;
	}

	if (largest != start)
	{
		event temp = arr[start];
		arr[start] = arr[largest];
		arr[largest] = temp;

		top_down_heapify(arr, size, largest);
	}
}

event priority_queue_delete(priority_queue *pq)
{
	if (pq->size > 0)
	{
		event temp = pq->arr[0];
		pq->arr[0] = pq->arr[pq->size - 1];
		pq->size--;
		top_down_heapify(pq->arr, pq->size, 0);
		return temp;
	}
}

void display_pq(priority_queue *pq)
{
	int i = 0;
	for (i = 0; i < pq->size; ++i)
	{
		event e = pq->arr[i];
		printf("Customer id = %d\n", e.c.user_id);
		printf("Customer priority = %d\n", e.c.priority);
		printf("\n\n");
	}
}