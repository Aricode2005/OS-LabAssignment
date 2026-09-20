#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

bool is_safe(int num_proc, int num_res, int *available, int **allocation, int **need, int *safe_seq) {
    int *work = (int *)malloc(num_res * sizeof(int));
    bool *finish = (bool *)calloc(num_proc, sizeof(bool));
    
    for (int i = 0; i < num_res; i++) {
        work[i] = available[i];
    }
    
    int count = 0;
    while (count < num_proc) {
        bool found = false;
        for (int p = 0; p < num_proc; p++) {
            if (!finish[p]) {
                bool can_allocate = true;
                for (int j = 0; j < num_res; j++) {
                    if (need[p][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    for (int j = 0; j < num_res; j++) {
                        work[j] += allocation[p][j];
                    }
                    safe_seq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            free(work);
            free(finish);
            return false;
        }
    }
    
    free(work);
    free(finish);
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char *)malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';
    fclose(file);

    int num_res = 0, num_proc = 0;
    int *total_res = NULL;
    int **max_needs = NULL;

    char *ptr = strstr(buffer, "<#no of resources>");
    if (ptr) {
        ptr += strlen("<#no of resources>");
        num_res = strtol(ptr, &ptr, 10);
    }

    ptr = strstr(ptr, "<#no of instances of each resource>");
    if (ptr) {
        ptr += strlen("<#no of instances of each resource>");
        total_res = (int *)malloc(num_res * sizeof(int));
        for (int i = 0; i < num_res; i++) {
            total_res[i] = strtol(ptr, &ptr, 10);
        }
    }

    ptr = strstr(ptr, "<#no of processes>");
    if (ptr) {
        ptr += strlen("<#no of processes>");
        num_proc = strtol(ptr, &ptr, 10);
    }

    ptr = strchr(ptr, '>'); 
    if (ptr) {
        ptr += 1;
        max_needs = (int **)malloc(num_proc * sizeof(int *));
        for (int i = 0; i < num_proc; i++) {
            max_needs[i] = (int *)malloc(num_res * sizeof(int));
            for (int j = 0; j < num_res; j++) {
                while (*ptr == ' ' || *ptr == ',' || *ptr == '\n' || *ptr == '\r') ptr++;
                max_needs[i][j] = strtol(ptr, &ptr, 10);
            }
        }
    }
    free(buffer);

    srand(time(NULL));
    int **allocation = (int **)malloc(num_proc * sizeof(int *));
    int **need = (int **)malloc(num_proc * sizeof(int *));
    int *available = (int *)malloc(num_res * sizeof(int));
    
    for (int i = 0; i < num_res; i++) {
        available[i] = total_res[i];
    }

    for (int i = 0; i < num_proc; i++) {
        allocation[i] = (int *)malloc(num_res * sizeof(int));
        need[i] = (int *)malloc(num_res * sizeof(int));
        for (int j = 0; j < num_res; j++) {
            int max_possible = (max_needs[i][j] < available[j]) ? max_needs[i][j] : available[j];
            int alloc = (max_possible > 0) ? (rand() % ((max_possible / 2) + 1)) : 0;
            
            allocation[i][j] = alloc;
            available[j] -= alloc;
            need[i][j] = max_needs[i][j] - alloc;
        }
    }

    printf("--- Initial State ---\n");
    printf("Available: ");
    for(int j=0; j<num_res; j++) printf("%d ", available[j]);
    printf("\n\n");

    int *safe_seq = (int *)malloc(num_proc * sizeof(int));
    if (!is_safe(num_proc, num_res, available, allocation, need, safe_seq)) {
        printf("Initial generated state is strictly unsafe. Please run the program again.\n");
        return 0;
    }
    
    printf("System is initially SAFE. Sequence: ");
    for(int i=0; i<num_proc; i++) printf("P%d ", safe_seq[i]);
    printf("\n\n");

    bool *finished = (bool *)calloc(num_proc, sizeof(bool));
    int finished_count = 0;
    int *request = (int *)malloc(num_res * sizeof(int));

    while (finished_count < num_proc) {
        int p = rand() % num_proc;
        if (finished[p]) continue;

        bool all_zero = true;
        for (int j = 0; j < num_res; j++) {
            if (need[p][j] > 0) {
                request[j] = rand() % (need[p][j] + 1);
                if (request[j] > 0) all_zero = false;
            } else {
                request[j] = 0;
            }
        }
        
        if (all_zero) continue;

        printf("-> Process P%d requests: ", p);
        for(int j=0; j<num_res; j++) printf("%d ", request[j]);
        printf("\n");

        bool can_grant = true;
        for (int j = 0; j < num_res; j++) {
            if (request[j] > available[j]) {
                can_grant = false;
                break;
            }
        }

        if (!can_grant) {
            printf("(1) Should request be granted? NO (Resources not available, P%d must wait)\n\n", p);
            continue;
        }

        for (int j = 0; j < num_res; j++) {
            available[j] -= request[j];
            allocation[p][j] += request[j];
            need[p][j] -= request[j];
        }

        if (is_safe(num_proc, num_res, available, allocation, need, safe_seq)) {
            printf("(1) Should request be granted? YES\n");
            printf("(2) Safe Sequence: ");
            for(int i = 0; i < num_proc; i++) printf("P%d ", safe_seq[i]);
            printf("\n");

            bool is_done = true;
            for (int j = 0; j < num_res; j++) {
                if (need[p][j] > 0) is_done = false;
            }

            if (is_done) {
                printf("*** Process P%d has finished and released all resources ***\n", p);
                finished[p] = true;
                finished_count++;
                for (int j = 0; j < num_res; j++) {
                    available[j] += allocation[p][j];
                    allocation[p][j] = 0;
                }
            }
            
            printf("Available pool now: ");
            for(int j = 0; j < num_res; j++) printf("%d ", available[j]);
            printf("\n\n");
            
        } else {
            printf("(1) Should request be granted? NO (Leads to unsafe state)\n");
            for (int j = 0; j < num_res; j++) {
                available[j] += request[j];
                allocation[p][j] -= request[j];
                need[p][j] += request[j];
            }
            printf("Request rolled back.\n\n");
        }
    }

    printf("All processes have successfully finished.\n");

    for(int i=0; i<num_proc; i++) {
        free(max_needs[i]);
        free(allocation[i]);
        free(need[i]);
    }
    free(max_needs); free(allocation); free(need);
    free(total_res); free(available); free(safe_seq); free(finished); free(request);

    return 0;
}