#include <stdio.h>
#include <stdlib.h>
#include "process.h"

<<<<<<< HEAD
// Comparador para qsort sobre punteros a Process
static int cmp_process_ptrs(const void *a, const void *b) {
    const Process *pa = *(const Process **)a;
    const Process *pb = *(const Process **)b;
    if (pa->arrival_time != pb->arrival_time)
        return pa->arrival_time - pb->arrival_time;
    return pa->id - pb->id;
}

int main() {
=======
/* ============================================================
 * Student implementation area
 * ============================================================ */
void fcfs_schedule(Process p[], int n)
{
    (void)p;
    (void)n;
    /* TODO: Implement FCFS scheduling algorithm here */
}

/* ============================================================
 * DO NOT MODIFY MAIN
 * ============================================================ */
#ifndef UNIT_TEST
int main(void)
{
>>>>>>> 412d236 (Merge branch 'feature/schedulers' into develop)
    int n;
    printf("Número de procesos: ");
    scanf("%d", &n);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);
    // Crear array de punteros para ordenar por tiempo de llegada
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

<<<<<<< HEAD
    print_results(p, n, "FCFS Scheduling");
    return 0;
}
=======
    fcfs_schedule(p, n);

    print_results(p, n, "FCFS Scheduling");
    return 0;
}
#endif
>>>>>>> 412d236 (Merge branch 'feature/schedulers' into develop)
