#include <stdio.h>
#include <stdlib.h>
#include "process.h"

// Comparador para qsort sobre punteros a Process
static int cmp_process_ptrs(const void *a, const void *b) {
    const Process *pa = *(const Process **)a;
    const Process *pb = *(const Process **)b;
    if (pa->arrival_time != pb->arrival_time)
        return pa->arrival_time - pb->arrival_time;
    return pa->id - pb->id;
}

void fcfs_schedule(Process p[], int n) {
    Process *order[n];
    for (int i = 0; i < n; i++) order[i] = &p[i];

    qsort(order, n, sizeof(Process *), cmp_process_ptrs);

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        Process *proc = order[i];
        if (current_time < proc->arrival_time)
            current_time = proc->arrival_time;
        proc->waiting_time = current_time - proc->arrival_time;
        proc->turnaround_time = proc->waiting_time + proc->burst_time;
        proc->completed = 1;
        current_time += proc->burst_time;
    }

    // Reorder p[] to match the FCFS order
    Process temp[n];
    for (int i = 0; i < n; i++) temp[i] = *order[i];
    for (int i = 0; i < n; i++) p[i] = temp[i];
}
