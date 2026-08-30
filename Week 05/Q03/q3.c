#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap_int(&arr[i], &arr[j]);
        }
    }

    swap_int(&arr[i + 1], &arr[high]);
    return i + 1;
}

static void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pivot_index = partition(arr, low, high);
        quick_sort(arr, low, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, high);
    }
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

static int save_array_to_file(const char *filename, const int *arr, int n) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        fprintf(file, "%d ", arr[i]);
    }

    fprintf(file, "\n");
    fclose(file);
    return 1;
}

int main(void) {
    int n;
    int choice;
    int *arr;

    srand((unsigned int)time(NULL));

    printf("Enter the size of the dataset: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid size.\n");
        return 0;
    }

    arr = malloc((size_t)n * sizeof(int));

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

    if (!save_array_to_file("q03_input.txt", arr, n)) {
        printf("Could not write q03_input.txt\n");
        free(arr);
        return 0;
    }

    printf("Original data: ");
    print_array(arr, n);

    quick_sort(arr, 0, n - 1);

    printf("Sorted data:   ");
    print_array(arr, n);

    if (!save_array_to_file("q03_sorted.txt", arr, n)) {
        printf("Could not write q03_sorted.txt\n");
        free(arr);
        return 0;
    }

    printf("Input saved to q03_input.txt\n");
    printf("Sorted output saved to q03_sorted.txt\n");

    free(arr);
    return 0;
}
