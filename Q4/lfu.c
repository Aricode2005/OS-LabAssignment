#include <stdio.h>

void lfu1(int ref[], int n, int f) {
    int mem[20], freq[20], arr[20], faults = 0, i, j, time = 0;
    for(i = 0; i < f; i++) { mem[i] = -1; freq[i] = 0; arr[i] = 0; }
    
    for(i = 0; i < n; i++) {
        int hit = 0;
        time++;
        for(j = 0; j < f; j++) {
            if(mem[j] == ref[i]) {
                hit = 1;
                freq[j]++;
                break;
            }
        }
        if(!hit) {
            faults++;
            int pos = -1;
            for(j = 0; j < f; j++) {
                if(mem[j] == -1) { pos = j; break; }
            }
            if(pos == -1) {
                int min_f = freq[0], min_a = arr[0];
                pos = 0;
                for(j = 1; j < f; j++) {
                    if(freq[j] < min_f || (freq[j] == min_f && arr[j] < min_a)) {
                        min_f = freq[j];
                        min_a = arr[j];
                        pos = j;
                    }
                }
            }
            mem[pos] = ref[i];
            freq[pos] = 1;
            arr[pos] = time;
        }
    }
    printf("LFU Method 1 (Local Freq, %d frames) Page Faults: %d\n", f, faults);
}

void lfu2(int ref[], int n, int f) {
    int mem[20], g_freq[100] = {0}, arr[20], faults = 0, i, j, time = 0;
    for(i = 0; i < f; i++) { mem[i] = -1; arr[i] = 0; }
    
    for(i = 0; i < n; i++) {
        int hit = 0;
        time++;
        g_freq[ref[i]]++;
        for(j = 0; j < f; j++) {
            if(mem[j] == ref[i]) {
                hit = 1;
                break;
            }
        }
        if(!hit) {
            faults++;
            int pos = -1;
            for(j = 0; j < f; j++) {
                if(mem[j] == -1) { pos = j; break; }
            }
            if(pos == -1) {
                int min_f = g_freq[mem[0]], min_a = arr[0];
                pos = 0;
                for(j = 1; j < f; j++) {
                    if(g_freq[mem[j]] < min_f || (g_freq[mem[j]] == min_f && arr[j] < min_a)) {
                        min_f = g_freq[mem[j]];
                        min_a = arr[j];
                        pos = j;
                    }
                }
            }
            mem[pos] = ref[i];
            arr[pos] = time;
        }
    }
    printf("LFU Method 2 (Global Freq, %d frames) Page Faults: %d\n", f, faults);
}

int main() {
    int ref[] = {9, 10, 11, 7, 12, 8, 7, 6, 12, 5, 4, 3, 10, 11, 12, 4, 5, 6, 9, 4, 5};
    int n = sizeof(ref) / sizeof(ref[0]);
    
    lfu1(ref, n, 4);
    lfu2(ref, n, 4);
    
    return 0;
}