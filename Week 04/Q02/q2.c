#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Comparator for qsort
int compareInts(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findPairSum(int S1[], int S2[], int n, int x) {
    // O(n log n) sorting
    qsort(S1, n, sizeof(int), compareInts);
    qsort(S2, n, sizeof(int), compareInts);

    int i = 0;
    int j = n - 1;

    // O(n) two-pointer search
    while (i < n && j >= 0) {
        int sum = S1[i] + S2[j];
        if (sum == x) return 1;
        else if (sum < x) i++;
        else j--;
    }
    return 0;
}

void readCustomData(int n, int S1[], int S2[]) {
    printf("Enter values for S1:\n");
    for (int i = 0; i < n; i++) scanf("%d", &S1[i]);
    printf("Enter values for S2:\n");
    for (int i = 0; i < n; i++) scanf("%d", &S2[i]);
}

void generateRandomData(int n, int S1[], int S2[]) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        S1[i] = rand() % 100 - 50; 
        S2[i] = rand() % 100 - 50;
    }
}

void printSets(int S[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", S[i]);
    }
    printf("\n");
}

int main(void) {
    int n, choice, x;
    printf("Enter size n: ");
    scanf("%d", &n);
    if (n <= 0) return 1;

    int *S1 = (int *)malloc(n * sizeof(int));
    int *S2 = (int *)malloc(n * sizeof(int));

    printf("Choose input method:\n1. Enter custom data\n2. Generate random data\nYour choice: ");
    scanf("%d", &choice);

    if (choice == 1) readCustomData(n, S1, S2);
    else generateRandomData(n, S1, S2);

    printf("Set S1: ");
    printSets(S1, n);
    printf("Set S2: ");
    printSets(S2, n);

    printf("Enter target sum x: ");
    scanf("%d", &x);

    if (findPairSum(S1, S2, n, x)) {
        printf("Pair with sum %d exists.\n", x);
    } else {
        printf("Pair with sum %d does not exist.\n", x);
    }

    free(S1); free(S2);
    return 0;
}