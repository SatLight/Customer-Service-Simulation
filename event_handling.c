#include <stdio.h>
#include <stdlib.h>
#include "events.h"
#include <time.h>

/*
    threads refers to servicemen.

    manage_events function checks if any thread is idle and if any customer is waiting in events queue, 
    it dequeues the customer from the queue, binds it to the thread and pushes it into the busy thread queue

    It also checks for completion of events in busy threads queue and if an event is completed,
    it removes the thread and enqueues it back to idle queue

*/

void manage_events(queue *idle_threads, queue **busy_threads, priority_queue *events, int current_time, int time_per_event)
{
    event e1;
    if (idle_threads->size > 0)
    {
        if (events->size > 0)
        {
            thread *th = dequeue(idle_threads)->th;
            e1 = priority_queue_delete(events);
            th->e = (event *)malloc(sizeof(event));
            th->e->c.user_id = e1.c.user_id;
            th->e->c.priority = e1.c.priority;
            th->e->startTime = current_time;
            printf("Service started for customer id = %d at time  = %d seconds\n", th->e->c.user_id, current_time);
            th->e->startTime = current_time;
            th->is_idle = 0;
            node *a = new_node(th);
            enqueue(*busy_threads, a);
        }
    }
    if ((*busy_threads)->size > 0)
    {
        int i = 0;
        node *p = (*busy_threads)->front;
        for (i = 0; i < (*busy_threads)->size; ++i)
        {

            if (current_time - p->th->e->startTime >= time_per_event)
            {
                thread *th = dequeue(*busy_threads)->th;
                printf("Service completed for customer id = %d at time = %d seconds \n", th->e->c.user_id, current_time);
                th->e = NULL;
                th->is_idle = 1;
                node *a = new_node(th);
                enqueue(idle_threads, a);
                return;
            }
            if (i != (*busy_threads)->size - 1)
            {
                p = p->next;
            }
        }
    }
}
