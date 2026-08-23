#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compareInts(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Recursive k-sum checker
int checkKSum(int S[], int n, int k, int T, int start) {
    // Base Case 1: 1-Sum is essentially Binary Search O(log n)
    if (k == 1) {
        int left = start, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (S[mid] == T) 
                return 1;
            if (S[mid] < T) 
                left = mid + 1;
            else 
                right = mid - 1;
        }
        return 0;
    }
    
    // Base Case 2: 2-Sum using Two Pointers O(n)
    if (k == 2) {
        int left = start, right = n - 1;
        while (left < right) {
            int sum = S[left] + S[right];
            if (sum == T) 
                return 1;
            if (sum < T) 
                left++;
            else
                right--;
        }
        return 0;
    }

    // General Case: Reduce k-sum to (k-1)-sum O(n^{k-1})
    for (int i = start; i <= n - k; i++) {
        if (checkKSum(S, n, k - 1, T - S[i], i + 1)) 
            return 1;
    }
    return 0;
}

int findKSum(int S[], int n, int k, int T) {
    if (k <= 0 || n <= 0 || k > n) 
        return 0;

    qsort(S, n, sizeof(int), compareInts); // Sort in O(n log n)
    return checkKSum(S, n, k, T, 0);
}

void readCustomData(int n, int S[]) {
    printf("Enter values for S:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);
}

void generateRandomData(int n, int S[]) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) 
        S[i] = rand() % 100 + 1;
}

int main(void) {
    int n, k, T, choice;
    printf("Enter size n: ");
    scanf("%d", &n);

    if (n <= 0) return 1;
    int *S = (int *)malloc(n * sizeof(int));

    printf("Choose input method:\n1. Enter custom data\n2. Generate random data\nYour choice: ");
    scanf("%d", &choice);

    if (choice == 1) readCustomData(n, S);
    else generateRandomData(n, S);

    printf("Set S: ");
    for (int i = 0; i < n; i++)
        printf("%d ", S[i]);
    printf("\n");

    printf("Enter k (number of elements to sum): ");
    scanf("%d", &k);
    printf("Enter target sum T: ");
    scanf("%d", &T);

    if (findKSum(S, n, k, T)) {
        printf("Yes, there exist %d elements that sum to %d.\n", k, T);
    } else {
        printf("No such %d elements sum to %d.\n", k, T);
    }

    free(S);
    return 0;
}