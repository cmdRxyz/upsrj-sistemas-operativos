#include <limits.h>
#include <string.h> /* for memset */
#include "process.h"

/* Prototype: void rr_schedule(Process p[], int n, int quantum); */

void rr_schedule(Process p[], int n, int quantum) {
    int remaining[n];
    int completion_time[n];
    int in_queue[n];
    int queue[n];
    int front = 0, back = 0;
    int i;

    /* Initialize */
    for (i = 0; i < n; i++) {
        remaining[i] = p[i].burst_time;
        p[i].completed = 0;
        completion_time[i] = 0;
        in_queue[i] = 0;
    }

    int time = 0;
    int completed_count = 0;


    /* Prime queue with processes that arrive at time 0, or advance time to first arrival */
    for (i = 0; i < n; i++) {
        if (p[i].arrival_time <= time && !in_queue[i]) {
            queue[back] = i;
            back = (back + 1) % n;
            in_queue[i] = 1;
        }
    }
    if (front == back) {
        int next = INT_MAX;
        for (i = 0; i < n; i++) if (p[i].arrival_time < next) next = p[i].arrival_time;
        time = next;
        for (i = 0; i < n; i++) if (p[i].arrival_time <= time && !in_queue[i]) {
            queue[back] = i;
            back = (back + 1) % n;
            in_queue[i] = 1;
        }
    }

    while (completed_count < n) {
        int idx;
        if (front == back) {
            idx = -1;
        } else {
            idx = queue[front];
            front = (front + 1) % n;
            in_queue[idx] = 0;
        }
        if (idx == -1) {
            /* No ready processes: jump to next arrival */
            int next = INT_MAX;
            for (i = 0; i < n; i++) if (!p[i].completed && p[i].arrival_time < next) next = p[i].arrival_time;
            time = next;
            for (i = 0; i < n; i++) if (!p[i].completed && p[i].arrival_time <= time && !in_queue[i]) {
                queue[back] = i;
                back = (back + 1) % n;
                in_queue[i] = 1;
            }
            continue;
        }

        int run = remaining[idx] < quantum ? remaining[idx] : quantum;
        int start = time;
        time += run;
        remaining[idx] -= run;

        /* Add any newly arrived processes during this quantum */
        for (i = 0; i < n; i++) {
            if (!p[i].completed && !in_queue[i] && p[i].arrival_time > start && p[i].arrival_time <= time) {
                queue[back] = i;
                back = (back + 1) % n;
                in_queue[i] = 1;
            }
        }

        if (remaining[idx] == 0) {
            p[idx].completed = 1;
            completion_time[idx] = time;
            completed_count++;
        } else {
            /* Re-enqueue the process */
            queue[back] = idx;
            back = (back + 1) % n;
            in_queue[idx] = 1;
        }
    }

    /* Compute final waiting and turnaround times */
    for (i = 0; i < n; i++) {
        p[i].turnaround_time = completion_time[i] - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        if (p[i].waiting_time < 0) p[i].waiting_time = 0; /* defensive */
    }
}
