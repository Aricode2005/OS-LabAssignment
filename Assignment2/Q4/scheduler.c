#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_JOBS 20
#define MAX_BURSTS 50
#define TIME_QUANTUM 16

typedef enum { NEW, READY, RUNNING, WAITING, TERMINATED } State;

typedef struct {
    int pid;
    int priority;
    int arrival_time;
    int bursts[MAX_BURSTS]; 
    int burst_count;
    
    State state;
    int current_burst_index;
    int remaining_time_current_burst;
    int time_in_quantum;
    
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int total_cpu_time;
    int total_io_time;
} Process;

int read_jobs(const char *filename, Process jobs[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int count = 0;
    while (!feof(file)) {
        int pid;
        if (fscanf(file, "%d", &pid) != 1) break;
        
        jobs[count].pid = pid;
        fscanf(file, "%d %d", &jobs[count].priority, &jobs[count].arrival_time);
        
        int b_val, b_idx = 0;
        jobs[count].total_cpu_time = 0;
        jobs[count].total_io_time = 0;
        
        while (fscanf(file, "%d", &b_val) == 1 && b_val != -1) {
            jobs[count].bursts[b_idx] = b_val;
            if (b_idx % 2 == 0) jobs[count].total_cpu_time += b_val;
            else jobs[count].total_io_time += b_val;
            b_idx++;
        }
        jobs[count].burst_count = b_idx;
        count++;
    }
    fclose(file);
    return count;
}

void reset_jobs(Process jobs[], int n) {
    for (int i = 0; i < n; i++) {
        jobs[i].state = NEW;
        jobs[i].current_burst_index = 0;
        jobs[i].remaining_time_current_burst = jobs[i].bursts[0];
        jobs[i].time_in_quantum = 0;
        jobs[i].completion_time = 0;
        jobs[i].turnaround_time = 0;
        jobs[i].waiting_time = 0;
    }
}

bool all_terminated(Process jobs[], int n) {
    for (int i = 0; i < n; i++) {
        if (jobs[i].state != TERMINATED) return false;
    }
    return true;
}

void simulate(Process jobs[], int n, const char* algo_name, int algo_type) {
    reset_jobs(jobs, n);
    
    int time = 0;
    int running_pid = -1;
    
    int ready_queue[MAX_JOBS];
    int q_front = 0, q_rear = 0, q_size = 0;

    while (!all_terminated(jobs, n)) {
        for (int i = 0; i < n; i++) {
            if (jobs[i].state == NEW && jobs[i].arrival_time <= time) {
                jobs[i].state = READY;
                if (algo_type == 2) {
                    ready_queue[q_rear] = i;
                    q_rear = (q_rear + 1) % MAX_JOBS;
                    q_size++;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (jobs[i].state == WAITING) {
                jobs[i].remaining_time_current_burst--;
                if (jobs[i].remaining_time_current_burst == 0) {
                    jobs[i].current_burst_index++;
                    if (jobs[i].current_burst_index < jobs[i].burst_count) {
                        jobs[i].state = READY;
                        jobs[i].remaining_time_current_burst = jobs[i].bursts[jobs[i].current_burst_index];
                        if (algo_type == 2) {
                            ready_queue[q_rear] = i;
                            q_rear = (q_rear + 1) % MAX_JOBS;
                            q_size++;
                        }
                    } else {
                        jobs[i].state = TERMINATED;
                        jobs[i].completion_time = time;
                    }
                }
            }
        }

        if (running_pid != -1) {
            int i = running_pid;
            jobs[i].remaining_time_current_burst--;
            jobs[i].time_in_quantum++;

            if (jobs[i].remaining_time_current_burst == 0) {
                jobs[i].current_burst_index++;
                if (jobs[i].current_burst_index < jobs[i].burst_count) {
                    jobs[i].state = WAITING;
                    jobs[i].remaining_time_current_burst = jobs[i].bursts[jobs[i].current_burst_index];
                } else {
                    jobs[i].state = TERMINATED;
                    jobs[i].completion_time = time;
                }
                running_pid = -1;
            } 
            else if (algo_type == 2 && jobs[i].time_in_quantum == TIME_QUANTUM) {
                jobs[i].state = READY;
                ready_queue[q_rear] = i;
                q_rear = (q_rear + 1) % MAX_JOBS;
                q_size++;
                running_pid = -1;
            }
        }

        if (running_pid == -1) {
            if (algo_type == 0) { // FCFS
                int earliest_arrival = 999999, selected = -1;
                for (int i = 0; i < n; i++) {
                    if (jobs[i].state == READY && jobs[i].arrival_time < earliest_arrival) {
                        earliest_arrival = jobs[i].arrival_time;
                        selected = i;
                    }
                }
                running_pid = selected;
            } 
            else if (algo_type == 1) { 
                int highest_priority = 999999, earliest_arrival = 999999, selected = -1;
                for (int i = 0; i < n; i++) {
                    if (jobs[i].state == READY) {
                        if (jobs[i].priority < highest_priority || 
                           (jobs[i].priority == highest_priority && jobs[i].arrival_time < earliest_arrival)) {
                            highest_priority = jobs[i].priority;
                            earliest_arrival = jobs[i].arrival_time;
                            selected = i;
                        }
                    }
                }
                running_pid = selected;
            } 
            else if (algo_type == 2) { 
                if (q_size > 0) {
                    running_pid = ready_queue[q_front];
                    q_front = (q_front + 1) % MAX_JOBS;
                    q_size--;
                }
            }

            if (running_pid != -1) {
                jobs[running_pid].state = RUNNING;
                jobs[running_pid].time_in_quantum = 0; 
            }
        }

        time++;
    }

    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        jobs[i].turnaround_time = jobs[i].completion_time - jobs[i].arrival_time;
        jobs[i].waiting_time = jobs[i].turnaround_time - jobs[i].total_cpu_time - jobs[i].total_io_time;
        total_tat += jobs[i].turnaround_time;
        total_wt += jobs[i].waiting_time;
    }

    printf("\n=== %s Results ===\n", algo_name);
    printf("PID\tPriority\tArrival\tComp\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t%d\t%d\t%d\n", 
            jobs[i].pid, jobs[i].priority, jobs[i].arrival_time, 
            jobs[i].completion_time, jobs[i].turnaround_time, jobs[i].waiting_time);
    }
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

int main() {
    Process jobs[MAX_JOBS];
    int n = read_jobs("jobs.txt", jobs);
    
    if (n != 8) {
        printf("Warning: Found %d jobs, but requirements asked for 8. Proceeding anyway.\n", n);
    }

    simulate(jobs, n, "FCFS", 0);
    simulate(jobs, n, "Non-preemptive Priority", 1);
    simulate(jobs, n, "Round Robin (TQ=16)", 2);

    return 0;
}