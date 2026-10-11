/*
 * Q08 - Minimum Number of Meeting Rooms  (DAA Lab 09)
 *
 * Input representation : n intervals [s_i, e_i) with s_i < e_i (half-open, so a
 *                        meeting may start exactly when another one ends),
 *                        stored in two arrays start[] and end[].
 * Algorithm            : sort the start times and the end times separately and
 *                        sweep with two pointers; a start that happens before the
 *                        earliest unfinished end needs a new room, otherwise a room
 *                        is reused.
 * Validation           : brute force - the answer is the maximum number of
 *                        intervals covering any start point (O(n^2)).
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 200000

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

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

/* ------------------------------------------------------------------ */
/* input                                                               */
/* ------------------------------------------------------------------ */
static int input_manual(int *s, int *e) {
    int n = read_int("Number of meetings n (1..200000): ", 1, MAX_N);
    printf("Enter  start  end  for each meeting (0 <= start < end <= 1000000000):\n");
    for (int i = 0; i < n; i++) {
        printf("  meeting %d: ", i + 1);
        while (scanf("%d %d", &s[i], &e[i]) != 2 || s[i] < 0 || e[i] <= s[i] || e[i] > 1000000000) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Need 0 <= start < end <= 1e9. Re-enter meeting %d: ", i + 1);
        }
    }
    return n;
}

/* Constraints: start in [0,100], duration in [1,40], so start < end. */
static int input_random(int *s, int *e) {
    int n = read_int("Number of meetings n (1..200000): ", 1, MAX_N);
    for (int i = 0; i < n; i++) {
        s[i] = rand() % 101;
        e[i] = s[i] + 1 + rand() % 40;
    }
    return n;
}

/* ------------------------------------------------------------------ */
/* core logic                                                          */
/* ------------------------------------------------------------------ */
static int min_meeting_rooms(const int *s, const int *e, int n) {
    int *starts = malloc((size_t)n * sizeof(int));
    int *ends = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) { starts[i] = s[i]; ends[i] = e[i]; }
    qsort(starts, (size_t)n, sizeof(int), cmp_int);
    qsort(ends, (size_t)n, sizeof(int), cmp_int);

    int rooms = 0, j = 0;
    for (int i = 0; i < n; i++) {
        if (starts[i] < ends[j]) rooms++; /* nobody has left yet: open a room */
        else j++;                         /* a meeting finished: reuse its room */
    }
    free(starts);
    free(ends);
    return rooms;
}

static int brute_force_rooms(const int *s, const int *e, int n) {
    int best = 0;
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++)
            if (s[j] <= s[i] && s[i] < e[j]) c++;
        if (c > best) best = c;
    }
    return best;
}

/* ------------------------------------------------------------------ */
int main(void) {
    static int s[MAX_N + 5], e[MAX_N + 5];
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q08: Minimum Number of Meeting Rooms ===\n");
    int n = choose_input_method() == 1 ? input_manual(s, e) : input_random(s, e);

    printf("\nInput (n = %d)\n", n);
    if (n <= 30) {
        for (int i = 0; i < n; i++) printf("  [%d, %d)\n", s[i], e[i]);
    }

    int ans = min_meeting_rooms(s, e, n);
    printf("\nMinimum number of rooms required = %d\n", ans);

    if (n <= 5000) {
        int ref = brute_force_rooms(s, e, n);
        printf("Validation (maximum overlap, O(n^2)): %d -> %s\n", ref, ref == ans ? "PASSED" : "FAILED");
    } else {
        printf("Validation skipped (n > 5000).\n");
    }
    return 0;
}
