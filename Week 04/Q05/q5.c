#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct to represent an interval with start and end times
struct Interval {
    int start;
    int end;
};

// Sort primarily by start time
int compareIntervals(const void *a, const void *b) {
    return (((struct Interval *)a)->start - ((struct Interval *)b)->start);
}

struct Interval *mergeIntervals(struct Interval arr[], int n, int *newSize) {
    if (n <= 0) {
        *newSize = 0;
        return NULL;
    }

    struct Interval *copy = (struct Interval *)malloc(n * sizeof(struct Interval));
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    // O(n log n) sorting
    qsort(copy, n, sizeof(struct Interval), compareIntervals);

    struct Interval *result = (struct Interval *)malloc(n * sizeof(struct Interval));
    int size = 0;
    result[size++] = copy[0];

    // O(n) merging phase
    for (int i = 1; i < n; i++) {
        if (copy[i].start <= result[size - 1].end) {
            if (copy[i].end > result[size - 1].end) {
                result[size - 1].end = copy[i].end;
            }
        } else {
            result[size++] = copy[i];
        }
    }

    free(copy);
    *newSize = size;
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
        arr[i].start = rand() % 50;
        arr[i].end = arr[i].start + rand() % 20 + 1;
    }
}

int main(void) {
    int n, choice;
    printf("Enter number of intervals (n): ");
    scanf("%d", &n);

    if (n <= 0) return 1;

    struct Interval *arr = (struct Interval *)malloc(n * sizeof(struct Interval));

    printf("Choose input method:\n1. Enter custom data\n2. Generate random data\nYour choice: ");
    scanf("%d", &choice);

    if (choice == 1) readCustomData(n, arr);
    else generateRandomData(n, arr);

    printf("Original intervals: ");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d) ", arr[i].start, arr[i].end);    
    }
    printf("\n");

    int newSize;
    struct Interval *merged = mergeIntervals(arr, n, &newSize);

    printf("Merged intervals: ");
    for (int i = 0; i < newSize; i++) {
        printf("(%d, %d) ", merged[i].start, merged[i].end);
    }
    printf("\n");

    free(arr); 
    free(merged);
    return 0;
}