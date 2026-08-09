#include <stdlib.h>

extern void merge(int* arr1, int size1, int* arr2, int size2, int* result);

// Method 1: Sequential Merging
int* method1_merge(int** arrays, int k, int n) {
    if (k == 0) return NULL;
    
    // The final array will hold k * n elements
    int* result = (int*)malloc(k * n * sizeof(int));
    
    // Initialize result with the first array
    for (int i = 0; i < n; i++) {
        result[i] = arrays[0][i];
    }
    
    int current_size = n;
    
    // Sequentially merge the remaining arrays
    for (int i = 1; i < k; i++) {
        int* temp = (int*)malloc((current_size + n) * sizeof(int));
        
        merge(result, current_size, arrays[i], n, temp);
        
        // Copy the merged data back to result array
        for (int j = 0; j < current_size + n; j++) {
            result[j] = temp[j];
        }
        
        free(temp);
        current_size += n;
    }
    
    return result;
}