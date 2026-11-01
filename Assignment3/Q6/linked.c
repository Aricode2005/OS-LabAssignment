#include <stdio.h>
#include <stdlib.h>

int main() {
    int f[50] = {0};
    int p, i, st, len, c, a;

    printf("Enter how many blocks are already allocated: ");
    scanf("%d", &p);
    
    if (p > 0) {
        printf("Enter block numbers that are already allocated: ");
        for (i = 0; i < p; i++) {
            scanf("%d", &a);
            f[a] = 1;
        }
    }

    while (1) {
        printf("Enter starting block and length: ");
        scanf("%d %d", &st, &len);

        if (f[st] == 0) {
            int allocated = 0;
            int current = st;
            
            while (allocated < len && current < 50) {
                if (f[current] == 0) {
                    f[current] = 1;
                    printf("%d -----> Allocated\n", current);
                    allocated++;
                } else {
                    printf("%d -----> Block is already allocated\n", current);
                }
                current++;
            }
            
            if (allocated == len) {
                printf("The file is successfully allocated to the disk.\n");
            } else {
                printf("Not enough free space available. Allocation incomplete.\n");
            }
        } else {
            printf("Starting block %d is already allocated.\n", st);
        }

        printf("Do you want to enter more files (Yes - 1 / No - 0): ");
        scanf("%d", &c);
        if (c == 0) {
            break;
        }
    }
    return 0;
}
