#include <stdio.h>
#include <stdlib.h>

int main() {
    int f[50] = {0};
    int index[50];
    int n, j, c, k, ind, count = 0;

    while (1) {
        printf("Enter index block: ");
        scanf("%d", &ind);

        if (f[ind] != 1) {
            printf("Enter no of blocks needed for the index %d on the disk: ", ind);
            scanf("%d", &n);
        } else {
            printf("%d index is already allocated\n", ind);
            continue;
        }

        count = 0;
        printf("Enter %d blocks: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &index[i]);
            if (f[index[i]] == 0) {
                count++;
            }
        }

        if (count == n) {
            for (j = 0; j < n; j++) {
                f[index[j]] = 1;
            }
            f[ind] = 1;
            printf("Allocated\n");
            printf("File Indexed\n");
            for (k = 0; k < n; k++) {
                printf("%d --------> %d : 1\n", ind, index[k]);
            }
        } else {
            printf("One or more blocks are already allocated.\n");
            printf("Enter another file indexed.\n");
        }

        printf("Do you want to enter more files (Yes - 1 / No - 0): ");
        scanf("%d", &c);
        if (c == 0) {
            break;
        }
    }
    return 0;
}
