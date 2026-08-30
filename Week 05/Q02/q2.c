#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int partition(int *arr, int left, int right) {
    int pivot = arr[right];
    int store_index = left;

    for (int i = left; i < right; ++i) {
        if (arr[i] <= pivot) {
            swap_int(&arr[store_index], &arr[i]);
            ++store_index;
        }
    }

    swap_int(&arr[store_index], &arr[right]);
    return store_index;
}

static int quickselect(int *arr, int left, int right, int k_index) {
    while (left <= right) {
        int pivot_index = partition(arr, left, right);

        if (pivot_index == k_index) {
            return arr[pivot_index];
        }

        if (pivot_index < k_index) {
            left = pivot_index + 1;
        } else {
            right = pivot_index - 1;
        }
    }

    return -1;
}

static void fill_random(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;
    }
}

static void fill_user_input(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
}

static void print_array(const int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int n;
    int choice;
    int k;

    srand((unsigned int)time(NULL));

    printf("Enter the size of the dataset: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid size.\n");
        return 0;
    }

    int *arr = malloc((size_t)n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("Choose data input method:\n");
    printf("1. Random data\n");
    printf("2. User input\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        fill_random(arr, n);
    } else {
        fill_user_input(arr, n);
    }

    printf("Dataset: ");
    print_array(arr, n);

    printf("Enter k (1 to %d): ", n);
    scanf("%d", &k);

    if (k < 1 || k > n) {
        printf("Invalid k.\n");
        free(arr);
        return 0;
    }

    int *copy = malloc((size_t)n * sizeof(int));

    if (copy == NULL) {
        printf("Memory allocation failed.\n");
        free(arr);
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        copy[i] = arr[i];
    }

    printf("%d-th smallest element: %d\n", k, quickselect(copy, 0, n - 1, k - 1));

    free(copy);
    free(arr);
    return 0;
}
