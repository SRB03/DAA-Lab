#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int number;
    char color;
} Item;

void printItems(const Item items[], int n, const char *label) {
    printf("%s: ", label);
    for (int i = 0; i < n; i++) {
        printf("%d%c ", items[i].number, items[i].color);
    }
    printf("\n");
}

void sortItemsByColor(Item items[], int n) {
    Item *red = (Item *)malloc((size_t)n * sizeof(Item));
    Item *blue = (Item *)malloc((size_t)n * sizeof(Item));
    Item *yellow = (Item *)malloc((size_t)n * sizeof(Item));

    int redCount = 0, blueCount = 0, yellowCount = 0;

    if (!red || !blue || !yellow) {
        free(red); free(blue); free(yellow);
        printf("Memory allocation failed.\n");
        return;
    }

    // O(n) distribution
    for (int i = 0; i < n; i++) {
        if (items[i].color == 'R') red[redCount++] = items[i];
        else if (items[i].color == 'B') blue[blueCount++] = items[i];
        else if (items[i].color == 'Y') yellow[yellowCount++] = items[i];
    }

    // O(n) merge maintaining numerical order
    int index = 0;
    for (int i = 0; i < redCount; i++) items[index++] = red[i];
    for (int i = 0; i < blueCount; i++) items[index++] = blue[i];
    for (int i = 0; i < yellowCount; i++) items[index++] = yellow[i];

    free(red); free(blue); free(yellow);
}

void readUserData(int n, Item items[]) {
    printf("Enter %d items (number and color R/B/Y) in non-decreasing order of numbers: (ex: 2B 3Y)\n", n);
    for (int i = 0; i < n; i++) {
        printf("Enter item %d: ", i + 1);
        
        // Read number and color together (e.g., "2 B" or "2B")
        if (scanf("%d %c", &items[i].number, &items[i].color) != 2) {
            // Handle invalid input format if necessary
            printf("Invalid input format. Try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            i--;
            continue;
        }

        // Convert color to uppercase just in case user types lowercase ('r', 'b', 'y')
        items[i].color = toupper(items[i].color);

        // Validate non-decreasing order for numbers
        if (i > 0 && items[i].number < items[i - 1].number) {
            printf("Numbers must be non-decreasing! Please re-enter.\n");
            i--; 
            continue;
        }

        // Validate color
        while (items[i].color != 'R' && items[i].color != 'B' && items[i].color != 'Y') {
            printf("Invalid color. Enter only R, B, or Y for item %d: ", i + 1);
            scanf(" %c", &items[i].color);
            items[i].color = toupper(items[i].color);
        }
    }
}

void generateRandomData(int n, Item items[]) {
    srand((unsigned)time(NULL));
    int previous = 0;
    for (int i = 0; i < n; i++) {
        previous += rand() % 10 + 1; // Ensures strictly increasing order
        items[i].number = previous;
        
        int c = rand() % 3;
        if (c == 0) items[i].color = 'R';
        else if (c == 1) items[i].color = 'B';
        else items[i].color = 'Y';
    }
}

int main(void) {
    int n, choice;
    printf("Enter size n: ");
    scanf("%d", &n);

    if (n <= 0) return 1;

    Item *items = (Item *)malloc((size_t)n * sizeof(Item));
    
    printf("Choose input method:\n1. Enter custom data\n2. Generate random data\nYour choice: ");
    scanf("%d", &choice);

    if (choice == 1) readUserData(n, items);
    else generateRandomData(n, items);

    printItems(items, n, "Original items");
    sortItemsByColor(items, n);
    printItems(items, n, "Sorted by color");

    free(items);
    return 0;
}