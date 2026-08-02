#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to find the transition point using Binary Search
int findPartition(int arr[], int n) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if mid is the first 1
        if (arr[mid] == 1 && (mid == 0 || arr[mid - 1] == 0)) {
            return mid; 
        } 
        // If mid is 1, the first 1 must be to the left
        else if (arr[mid] == 1) {
            high = mid - 1;
        } 
        // If mid is 0, the first 1 must be to the right
        else {
            low = mid + 1;
        }
    }
    // Return -1 if array is all 0s or empty
    return -1; 
}

int main() {
    // 1. Define the size of the array
    int size_arr = 1000; 
    int arr[size_arr];
    srand(time(NULL));

    // Pick a random transition index between 0 and size_arr
    int random_transition = rand() % (size_arr + 1);

    // Fill the array: 0s before the transition, 1s from the transition onward
    for (int i = 0; i < size_arr; i++) {
        if (i < random_transition) {
            arr[i] = 0;
        } else {
            arr[i] = 1;
        }
    }

    // Print the actual transition point we generated for comparison
    if (random_transition < size_arr) {
        printf("The actual random transition point is at index: %d\n", random_transition);
    } else {
        printf("The array was filled completely with 0s.\n");
    }

    // 4. Test the algorithm on the randomly generated array
    int index = findPartition(arr, size_arr);
    
    if (index != -1)
        printf("-> Algorithm found partition point at index: %d\n", index);
    else
        printf("-> Algorithm found no partition point (no 1s in array).\n");

    return 0;
}