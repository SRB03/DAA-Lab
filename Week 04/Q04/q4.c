#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compareInts(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function returns maxPeople, but also modifies timeOfMax pointer
int mostPeoplePresent(int entry[], int exit[], int n, int *timeOfMax) {
    int *entryCopy = (int *)malloc(n * sizeof(int));
    int *exitCopy = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        entryCopy[i] = entry[i];
        exitCopy[i] = exit[i];
    }

    qsort(entryCopy, n, sizeof(int), compareInts);
    qsort(exitCopy, n, sizeof(int), compareInts);

    int maxPeople = 0, currentPeople = 0;
    int i = 0, j = 0;
    *timeOfMax = -1;

    while (i < n && j < n) {
        if (entryCopy[i] <= exitCopy[j]) {
            currentPeople++;
            if (currentPeople > maxPeople) {
                maxPeople = currentPeople;
                *timeOfMax = entryCopy[i]; // Track the time it occurred
            }
            i++;
        } else {
            currentPeople--;
            j++;
        }
    }

    free(entryCopy); 
    free(exitCopy);
    return maxPeople;
}

void readCustomData(int n, int entry[], int exit[]) {
    for (int i = 0; i < n; i++) {
        printf("Guest %d Entry time: ", i + 1);
        scanf("%d", &entry[i]);
        do {
            printf("Guest %d Exit time (must be > entry): ", i + 1);
            scanf("%d", &exit[i]);
        } while (exit[i] <= entry[i]);
    }
}

void generateRandomData(int n, int entry[], int exit[]) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        entry[i] = rand() % 1000;
        exit[i] = entry[i] + rand() % 50 + 1; // Enforces exit > entry
    }
}

int main(void) {
    int n, choice, timeOfMax;
    printf("Enter number of guests (n): ");
    scanf("%d", &n);

    if (n <= 0) return 1;

    int *entry = (int *)malloc(n * sizeof(int));
    int *exit = (int *)malloc(n * sizeof(int));

    printf("Choose input method:\n1. Enter custom data\n2. Generate random data\nYour choice: ");
    scanf("%d", &choice);

    if (choice == 1) readCustomData(n, entry, exit);
    else generateRandomData(n, entry, exit);

    // Print data
    printf("\n");

    printf("Entry times: ");
    for (int i = 0; i < n; i++) 
        printf("%d ", entry[i]);

    printf("\nExit times: ");
    for (int i = 0; i < n; i++) 
    printf("%d ", exit[i]);

    printf("\n\n");

    int maxPeople = mostPeoplePresent(entry, exit, n, &timeOfMax);
    printf("The most people present simultaneously is %d, which occurred at time %d.\n", maxPeople, timeOfMax);

    free(entry); 
    free(exit);
    return 0;
}