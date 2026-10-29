#include <stdio.h>

void fifo(int ref[], int n, int f) {
    int mem[20], head = 0, faults = 0, i, j;
    for(i = 0; i < f; i++) mem[i] = -1;
    
    for(i = 0; i < n; i++) {
        int hit = 0;
        for(j = 0; j < f; j++) {
            if(mem[j] == ref[i]) {
                hit = 1;
                break;
            }
        }
        if(!hit) {
            mem[head] = ref[i];
            head = (head + 1) % f;
            faults++;
        }
    }
    printf("FIFO (%d frames) Page Faults: %d\n", f, faults);
}

int main() {
    int ref[] = {9, 10, 11, 7, 12, 8, 7, 6, 12, 5, 4, 3, 10, 11, 12, 4, 5, 6, 9, 4, 5};
    int n = sizeof(ref) / sizeof(ref[0]);
    
    fifo(ref, n, 4);
    fifo(ref, n, 7);
    
    return 0;
}