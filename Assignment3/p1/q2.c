#include <stdio.h>
#include <stdlib.h>


typedef struct Block{
   int is_free;
   int pid;
   int start;
   int size;
   struct Block *next
}Block;

Block*head=NULL;

Block*new_block(int is_free,int pid,int start,int size){
    Block*b=(Block*)malloc(sizeof(Block));
    b->is_free=is_free;
    b->pid=pid;
    b->start=start;
    b->size=size;
    b->next=NULL;
    return b;
}

void free_memory(){
    Block*curr=head;
    while(curr){
        Block*tmp=curr;
        curr=curr->next;
        free(tmp);
    }
    head=NULL;
}

void append(Block **tail,Block*b){
    if(head==NULL){
        head=b;
    }else{
        (*tail)->next=b;
    }
    (*tail)=b;
}

void init_memory(){
    free_memory();
    Block *tail = NULL;
    append(&tail,new_block(1, -1, 1, 99));
    append(&tail,new_block(0, 0, 100, 800));
    append(&tail,new_block(0, 0, 100, 800));
    append(&tail,new_block(0, 1, 1210, 300));
    append(&tail,new_block(1, -1, 1510, 360));
    append(&tail,new_block(0, 2, 1870, 550));
    append(&tail,new_block(1, -1, 2420, 100));
    append(&tail, new_block(0, 3, 2520, 700));
    append(&tail, new_block(1, -1, 3220, 6780));
}

void print_memory() {
    printf("------------------------------------------------------\n");
    printf("%-10s %-5s %-10s %-10s %-10s\n", "Type", "ID", "Start", "End", "Size");
    printf("------------------------------------------------------\n");
    for (Block *cur = head; cur; cur = cur->next) {
        int end_addr = cur->start + cur->size - 1;
        if (cur->is_free) {
            printf("%-10s %-5s %-10d %-10d %-10d\n", "Hole", "-", cur->start, end_addr, cur->size);
        } else {
            printf("%-10s P%-4d %-10d %-10d %-10d\n", "Process", cur->pid, cur->start, end_addr, cur->size);
        }
    }
    printf("------------------------------------------------------\n");
}

void allocate(int pid,int size,int strategy){
    Block *target = NULL;
    for(Block*curr=head;curr;curr=curr->next){
        if(!curr->is_free || curr->size<size){
            continue;
        }
        if(strategy==1){
            target=curr;
            break;
        }else if(strategy==2){
            if(target==NULL || curr->size<target->size){
                target=curr;
            }
        }else if (strategy == 3) {
            if (target == NULL || curr->size > target->size) {
                target = curr;
            }
        }
    }
    if (target == NULL) {
        printf("Error: Not enough memory for P%d (%d bytes).\n", pid, size);
        return;
    }


    if (target->size > size) {
        Block *rest = new_block(1, -1, target->start + size, target->size - size);
        rest->next = target->next;
        target->next = rest;
        target->size = size;
    }
    target->is_free = 0;
    target->pid = pid;


}


void simulate_sequence(int *pids, int *sizes, int count, int strategy, const char *strat_name, char seq_char) {
    printf("\n\n======================================================\n");
    printf("Simulating Sequence '%c' using %s Strategy\n", seq_char, strat_name);
    printf("======================================================\n");

    init_memory();

    printf("\ni. After P0 to P3 are accommodated:\n");
    print_memory();

    const char *roman_numerals[] = {"ii", "iii", "iv"};
    for (int i = 0; i < count; i++) {
        printf("\n%s. After P%d is accommodated (%d bytes):\n", roman_numerals[i], pids[i], sizes[i]);
        allocate(pids[i], sizes[i], strategy);
        print_memory();
    }
    free_memory();
}

int main() {
    int strat_ids[] = {1, 2, 3};
    const char *strat_names[] = {"First Fit", "Best Fit", "Worst Fit"};

    for (int s = 0; s < 3; s++) {
        int pidsA[] = {4, 5, 6};
        int sizesA[] = {350, 500, 150};
        simulate_sequence(pidsA, sizesA, 3, strat_ids[s], strat_names[s], 'a');

        int pidsB[] = {6, 5, 4};
        int sizesB[] = {150, 500, 350};
        simulate_sequence(pidsB, sizesB, 3, strat_ids[s], strat_names[s], 'b');

        int pidsC[] = {5, 4, 6};
        int sizesC[] = {500, 350, 150};
        simulate_sequence(pidsC, sizesC, 3, strat_ids[s], strat_names[s], 'c');

        int pidsD[] = {6, 4, 5};
        int sizesD[] = {150, 350, 500};
        simulate_sequence(pidsD, sizesD, 3, strat_ids[s], strat_names[s], 'd');
    }

    return 0;
}