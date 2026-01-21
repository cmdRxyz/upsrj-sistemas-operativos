#include <stdlib.h>
#include "process.h"

/* comparator for pointers to Process */
static int cmp_process_ptrs(const void *a, const void *b) {
    const Process *pa = *(const Process **)a;
    const Process *pb = *(const Process **)b;
    if (pa->arrival_time != pb->arrival_time)
        return pa->arrival_time - pb->arrival_time;
    return pa->id - pb->id;
}

void fcfs_schedule(Process p[], int n) {
    if (n <= 0) return;

    /* build pointer array and sort by arrival_time then id */
    Process *order[n];
    for (int i = 0; i < n; ++i) order[i] = &p[i];
    qsort(order, n, sizeof(Process *), cmp_process_ptrs);

    /* simulate FCFS to compute waiting/turnaround/completed */
    int current_time = 0;
    for (int i = 0; i < n; ++i) {
        Process *proc = order[i];
        if (current_time < proc->arrival_time)
            current_time = proc->arrival_time;
        proc->waiting_time = current_time - proc->arrival_time;
        proc->turnaround_time = proc->waiting_time + proc->burst_time;
        proc->completed = 1;
        current_time += proc->burst_time;
    }
    
    /* NO DEBE HABER MÁS CÓDIGO DESPUÉS DE ESTO */
}