#include <stdlib.h>

extern void merge(int* arr1, int size1, int* arr2, int size2, int* result);

// Method 2 Helper: Recursive Divide and Conquer
int* method2_recursive(int** arrays, int l, int r, int n, int* out_size) {
    if (l == r) {
        *out_size = n;
        int* res = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) res[i] = arrays[l][i];
        return res;
    }
    
    int mid = l + (r - l) / 2;
    int size_left, size_right;
    
    int* left = method2_recursive(arrays, l, mid, n, &size_left);
    int* right = method2_recursive(arrays, mid + 1, r, n, &size_right);
    
    *out_size = size_left + size_right;
    int* merged = (int*)malloc((*out_size) * sizeof(int));
    
    merge(left, size_left, right, size_right, merged);
    
    free(left);
    free(right);
    
    return merged;
}

// Method 2: Pairwise Merging
int* method2_merge(int** arrays, int k, int n) {
    if (k == 0) return NULL;
    int final_size;
    return method2_recursive(arrays, 0, k - 1, n, &final_size);
}