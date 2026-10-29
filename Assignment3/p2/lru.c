#include <stdio.h>
#include <stdlib.h>

int ref[] = {9, 10, 11, 7, 12, 8, 7, 6, 12, 5, 4, 3, 10, 11, 12, 4, 5, 6, 9, 4, 5};
int n = 21;

struct node {
    int page;
    struct node *prev, *next;
};

int lru_stack(int frames)
{
    struct node *top = NULL, *bottom = NULL, *p, *t;
    int count = 0, faults = 0, i;

    printf("\nMethod 1: Stack (doubly linked list), %d frames\n", frames);
    printf("Page\tStack (top -> bottom)\tResult\n");

    for (i = 0; i < n; i++) {
        p = top;
        while (p != NULL && p->page != ref[i])
            p = p->next;

        if (p != NULL) {
            if (p != top) {
                p->prev->next = p->next;
                if (p == bottom)
                    bottom = p->prev;
                else
                    p->next->prev = p->prev;
                p->prev = NULL;
                p->next = top;
                top->prev = p;
                top = p;
            }
            printf("%d\t", ref[i]);
        } else {
            faults++;
            if (count == frames) {
                t = bottom;
                bottom = t->prev;
                if (bottom != NULL)
                    bottom->next = NULL;
                else
                    top = NULL;
                free(t);
                count--;
            }
            p = (struct node *)malloc(sizeof(struct node));
            p->page = ref[i];
            p->prev = NULL;
            p->next = top;
            if (top != NULL)
                top->prev = p;
            else
                bottom = p;
            top = p;
            count++;
            printf("%d\t", ref[i]);
        }

        for (t = top; t != NULL; t = t->next)
            printf("%d ", t->page);
        printf("\n");
    }

    while (top != NULL) {
        t = top;
        top = top->next;
        free(t);
    }
    return faults;
}

int lru_counter(int frames)
{
    int pg[10], tm[10];
    int used = 0, faults = 0, clock = 0;
    int i, j, found, min;

    printf("\nMethod 2: Counter (time of use), %d frames\n", frames);
    printf("Page\tFrames\n");

    for (i = 0; i < n; i++) {
        clock++;
        found = -1;
        for (j = 0; j < used; j++)
            if (pg[j] == ref[i])
                found = j;

        if (found != -1) {
            tm[found] = clock;
        } else {
            faults++;
            if (used < frames) {
                pg[used] = ref[i];
                tm[used] = clock;
                used++;
            } else {
                min = 0;
                for (j = 1; j < frames; j++)
                    if (tm[j] < tm[min])
                        min = j;
                pg[min] = ref[i];
                tm[min] = clock;
            }
        }

        printf("%d\t", ref[i]);
        for (j = 0; j < used; j++)
            printf("%d(t=%d) ", pg[j], tm[j]);
        printf("\n");
    }
    return faults;
}

int main()
{
    int f[2] = {5, 6};
    int s[2], c[2], i;

    for (i = 0; i < 2; i++) {
        s[i] = lru_stack(f[i]);
        c[i] = lru_counter(f[i]);
    }

    printf("\nComparison\n");
    printf("Frames\tStack faults\tCounter faults\n");
    for (i = 0; i < 2; i++)
        printf("%d\t%d\t\t%d\n", f[i], s[i], c[i]);

    return 0;
}