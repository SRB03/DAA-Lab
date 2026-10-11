/*
 * Q05 - Candy Distribution (Bi-directional Slope Greedy)  (DAA Lab 09)
 *
 * Input representation : array rating[0..n-1].
 * Algorithm            : single left-to-right pass tracking the length of the
 *                        current increasing run (up), decreasing run (down) and
 *                        the length of the last peak's rising side (peak).
 *                        Every slope contributes the arithmetic series
 *                        1 + 2 + ... + len, so no candy array is needed (O(1) space).
 * Validation           : classic two-pass (left->right, right->left) algorithm
 *                        that also builds the explicit distribution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 1000000

/* ------------------------------------------------------------------ */
static int read_int(const char *prompt, int lo, int hi) {
    int val;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%d", &val) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Invalid input, try again.\n");
            continue;
        }
        if (val < lo || val > hi) { printf("  Value must be in [%d, %d].\n", lo, hi); continue; }
        return val;
    }
}

static int choose_input_method(void) {
    printf("Select input method:\n");
    printf("  1. Manual user input\n");
    printf("  2. Randomized data generation\n");
    return read_int("Enter choice (1/2): ", 1, 2);
}

/* ------------------------------------------------------------------ */
/* input                                                               */
/* ------------------------------------------------------------------ */
static int input_manual(int *rating) {
    int n = read_int("Number of children n (1..1000000): ", 1, MAX_N);
    printf("Enter %d integer ratings (0 <= rating <= 1000000): ", n);
    for (int i = 0; i < n; i++) {
        while (scanf("%d", &rating[i]) != 1 || rating[i] < 0 || rating[i] > 1000000) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Ratings must be integers in [0, 1000000]. Re-enter child %d: ", i + 1);
        }
    }
    return n;
}

/* Constraint: ratings are integers in [0, 10]. */
static int input_random(int *rating) {
    int n = read_int("Number of children n (1..1000000): ", 1, MAX_N);
    for (int i = 0; i < n; i++) rating[i] = rand() % 11;
    return n;
}

/* ------------------------------------------------------------------ */
/* core logic                                                          */
/* ------------------------------------------------------------------ */
static long long candies_slope(const int *r, int n) {
    long long total = 1;
    long long up = 0, down = 0, peak = 0;
    for (int i = 1; i < n; i++) {
        if (r[i] > r[i - 1]) {
            up++;
            peak = up;
            down = 0;
            total += 1 + up;
        } else if (r[i] == r[i - 1]) {
            up = down = peak = 0;
            total += 1;
        } else {
            up = 0;
            down++;
            total += 1 + down;
            if (peak >= down) total--; /* the peak already has enough candies */
        }
    }
    return total;
}

/* two-pass reference; fills candy[] and returns the total */
static long long candies_two_pass(const int *r, int n, int *candy) {
    for (int i = 0; i < n; i++) candy[i] = 1;
    for (int i = 1; i < n; i++)
        if (r[i] > r[i - 1]) candy[i] = candy[i - 1] + 1;
    for (int i = n - 2; i >= 0; i--)
        if (r[i] > r[i + 1] && candy[i] <= candy[i + 1]) candy[i] = candy[i + 1] + 1;
    long long total = 0;
    for (int i = 0; i < n; i++) total += candy[i];
    return total;
}

static int distribution_is_valid(const int *r, int n, const int *candy) {
    for (int i = 0; i < n; i++) {
        if (candy[i] < 1) return 0;
        if (i > 0 && r[i] > r[i - 1] && candy[i] <= candy[i - 1]) return 0;
        if (i + 1 < n && r[i] > r[i + 1] && candy[i] <= candy[i + 1]) return 0;
    }
    return 1;
}

/* ------------------------------------------------------------------ */
int main(void) {
    static int rating[MAX_N + 5], candy[MAX_N + 5];
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q05: Candy Distribution (Bi-directional Slope Greedy) ===\n");
    int n = choose_input_method() == 1 ? input_manual(rating) : input_random(rating);

    if (n <= 40) {
        printf("\nRatings: ");
        for (int i = 0; i < n; i++) printf("%d ", rating[i]);
        printf("\n");
    }

    long long ans = candies_slope(rating, n);
    printf("\nMinimum total candies (slope method) = %lld\n", ans);

    long long ref = candies_two_pass(rating, n, candy);
    if (n <= 40) {
        printf("Candies per child (two-pass) : ");
        for (int i = 0; i < n; i++) printf("%d ", candy[i]);
        printf("\n");
    }
    int valid = distribution_is_valid(rating, n, candy);
    printf("\nValidation\n");
    printf("  two-pass total = %lld -> %s\n", ref, ref == ans ? "PASSED (totals agree)" : "FAILED");
    printf("  distribution satisfies all neighbour rules -> %s\n", valid ? "PASSED" : "FAILED");
    return 0;
}
