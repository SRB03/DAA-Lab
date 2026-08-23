#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Interval {
    int start;
    int end;
};

int compareInts(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findPointInMaxIntervals(struct Interval S[], int n) {
    int *starts = (int *)malloc(n * sizeof(int));
    int *ends = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        starts[i] = S[i].start;
        ends[i] = S[i].end;
    }

    qsort(starts, n, sizeof(int), compareInts);
    qsort(ends, n, sizeof(int), compareInts);

    int i = 0, j = 0;
    int currentCount = 0, maxCount = 0;
    int result = starts[0];

    while (i < n && j < n) {
        if (starts[i] <= ends[j]) {
            currentCount++;
            if (currentCount > maxCount) {
                maxCount = currentCount;
                result = starts[i];
            }
            i++;
        } else {
            currentCount--;
            j++;
        }
    }

    free(starts); free(ends);
    return result;
}

void readCustomData(int n, struct Interval arr[]) {
    for (int i = 0; i < n; i++) {
        printf("Interval %d (start end): ", i + 1);
        scanf("%d %d", &arr[i].start, &arr[i].end);
        while (arr[i].end < arr[i].start) {
            printf("End must be >= start. Try again: ");
            scanf("%d %d", &arr[i].start, &arr[i].end);
        }
    }
}

void generateRandomData(int n, struct Interval arr[]) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i].start = rand() % 100;
        arr[i].end = arr[i].start + rand() % 50 + 1;
    }
}

int main(void) {
    int n, choice;
    printf("Enter number of intervals (n): ");
    scanf("%d", &n);

    if (n <= 0) return 1;

    struct Interval *S = (struct Interval *)malloc(n * sizeof(struct Interval));

    printf("Choose input method:\n1. Enter custom data\n2. Generate random data\nYour choice: ");
    scanf("%d", &choice);

    if (choice == 1) readCustomData(n, S);
    else generateRandomData(n, S);

    printf("Original intervals: ");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d) ", S[i].start, S[i].end);    
    }
    printf("\n");

    int point = findPointInMaxIntervals(S, n);
    printf("A point in the largest number of intervals is %d\n", point);

    free(S);
    return 0;
}