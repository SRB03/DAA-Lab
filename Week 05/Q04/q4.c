#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify(int *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap_int(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

static void heap_sort(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; --i) {
        swap_int(&arr[0], &arr[i]);
        heapify(arr, i, 0);
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

    if (!save_array_to_file("q04_input.txt", arr, n)) {
        printf("Could not write q04_input.txt\n");
        free(arr);
        return 0;
    }

    printf("Original data: ");
    print_array(arr, n);

    heap_sort(arr, n);

    printf("Sorted data:   ");
    print_array(arr, n);

    if (!save_array_to_file("q04_sorted.txt", arr, n)) {
        printf("Could not write q04_sorted.txt\n");
        free(arr);
        return 0;
    }

    printf("Input saved to q04_input.txt\n");
    printf("Sorted output saved to q04_sorted.txt\n");

    free(arr);
    return 0;
}
