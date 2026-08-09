#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int* method1_merge(int** arrays, int k, int n);
extern int* method2_merge(int** arrays, int k, int n);

// Shared merge function
void merge(int* arr1, int size1, int* arr2, int size2, int* result) {
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    
    while (i < size1) {
        result[k++] = arr1[i++];
    }
    while (j < size2) {
        result[k++] = arr2[j++];
    }
}

// Generate K sorted arrays of size N
int** generate_k_sorted_arrays(int k, int n) {
    int** arrays = (int**)malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        arrays[i] = (int*)malloc(n * sizeof(int));        
        arrays[i][0] = rand() % 100;
        
        for (int j = 1; j < n; j++) {
            arrays[i][j] = arrays[i][j - 1] + (rand() % 15) + 1;
        }
    }
    return arrays;
}

// Calculate and analyze time taken by both methods
void analyze_time(int** arrays, int k, int n) {
    clock_t start, end;
    double cpu_time_used_m1, cpu_time_used_m2;
    
    // printf("--- Performance Analysis ---\n");
    printf("Total Arrays (K) : %d\n", k);
    printf("Elements per Array (N) : %d\n", n);
    printf("Total Elements to merge: %d\n\n", k * n);

    // Track time for Method 1
    start = clock();
    int* result1 = method1_merge(arrays, k, n);
    end = clock();
    cpu_time_used_m1 = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Method 1 (Sequential) Time : %f seconds\n", cpu_time_used_m1);

    // Track time for Method 2
    start = clock();
    int* result2 = method2_merge(arrays, k, n);
    end = clock();
    cpu_time_used_m2 = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Method 2 (Divide & Conquer) Time: %f seconds\n", cpu_time_used_m2);
    
    if (cpu_time_used_m2 < cpu_time_used_m1) {
        printf("\nResult: Divide & Conquer was faster by %f seconds.\n", cpu_time_used_m1 - cpu_time_used_m2);
    } else {
        printf("\nResult: Sequential was faster by %f seconds.\n", cpu_time_used_m2 - cpu_time_used_m1);
    }

    free(result1);
    free(result2);
}

int main() {
    int k = 1000;
    int n = 5000;
    
    srand(time(NULL));

    int** arrays = generate_k_sorted_arrays(k, n);
    analyze_time(arrays, k, n);

    // Free up memory 
    for (int i = 0; i < k; i++) {
        free(arrays[i]);
    }

    free(arrays);
    return 0;
}