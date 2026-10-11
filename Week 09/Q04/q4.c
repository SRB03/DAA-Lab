/*
 * Q04 - Minimum Cost to Connect Sticks  (DAA Lab 09)
 *
 * Input representation : array L[0..n-1] of positive stick lengths.
 * Algorithm            : greedy - always join the two shortest sticks (min-heap).
 *                        This is exactly Huffman merging.
 * Validation           : naive O(n^2) version (linear scan for the two minima).
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 200000

static long long heap[MAX_N + 5];
static int heap_size;

/* ------------------------------------------------------------------ */
static long long read_ll(const char *prompt, long long lo, long long hi) {
    long long val;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%lld", &val) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Invalid input, try again.\n");
            continue;
        }
        if (val < lo || val > hi) { printf("  Value must be in [%lld, %lld].\n", lo, hi); continue; }
        return val;
    }
}

static int choose_input_method(void) {
    printf("Select input method:\n");
    printf("  1. Manual user input\n");
    printf("  2. Randomized data generation\n");
    return (int)read_ll("Enter choice (1/2): ", 1, 2);
}

/* ------------------------------------------------------------------ */
/* input                                                               */
/* ------------------------------------------------------------------ */
static int input_manual(long long *L) {
    int n = (int)read_ll("Number of sticks n (1..200000): ", 1, MAX_N);
    printf("Enter %d positive stick lengths: ", n);
    for (int i = 0; i < n; i++) {
        while (scanf("%lld", &L[i]) != 1 || L[i] < 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Lengths must be positive integers. Re-enter stick %d: ", i + 1);
        }
    }
    return n;
}

/* Constraint: every length is a positive integer in [1, 100]. */
static int input_random(long long *L) {
    int n = (int)read_ll("Number of sticks n (1..200000): ", 1, MAX_N);
    for (int i = 0; i < n; i++) L[i] = 1 + rand() % 100;
    return n;
}

/* ------------------------------------------------------------------ */
/* min-heap                                                            */
/* ------------------------------------------------------------------ */
static void heap_push(long long v) {
    int i = heap_size++;
    heap[i] = v;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] <= heap[i]) break;
        long long t = heap[p]; heap[p] = heap[i]; heap[i] = t;
        i = p;
    }
}

static long long heap_pop(void) {
    long long top = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < heap_size && heap[l] < heap[m]) m = l;
        if (r < heap_size && heap[r] < heap[m]) m = r;
        if (m == i) break;
        long long t = heap[i]; heap[i] = heap[m]; heap[m] = t;
        i = m;
    }
    return top;
}

/* ------------------------------------------------------------------ */
/* core logic                                                          */
/* ------------------------------------------------------------------ */
static long long min_connect_cost(const long long *L, int n, int verbose) {
    heap_size = 0;
    for (int i = 0; i < n; i++) heap_push(L[i]);
    long long total = 0;
    int step = 1;
    while (heap_size > 1) {
        long long a = heap_pop();
        long long b = heap_pop();
        total += a + b;
        if (verbose) printf("  step %2d: join %lld + %lld -> %lld (cost %lld)\n", step, a, b, a + b, a + b);
        step++;
        heap_push(a + b);
    }
    return total;
}

static long long naive_cost(const long long *L, int n) {
    long long *a = malloc((size_t)n * sizeof(long long));
    for (int i = 0; i < n; i++) a[i] = L[i];
    long long total = 0;
    int m = n;
    while (m > 1) {
        int i1 = 0;
        for (int i = 1; i < m; i++) if (a[i] < a[i1]) i1 = i;
        long long x = a[i1];
        a[i1] = a[--m];
        int i2 = 0;
        for (int i = 1; i < m; i++) if (a[i] < a[i2]) i2 = i;
        long long y = a[i2];
        a[i2] = x + y;
        total += x + y;
    }
    free(a);
    return total;
}

/* ------------------------------------------------------------------ */
int main(void) {
    static long long L[MAX_N + 5];
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q04: Minimum Cost to Connect Sticks ===\n");
    int n = choose_input_method() == 1 ? input_manual(L) : input_random(L);

    printf("\nInput (n = %d)", n);
    if (n <= 30) {
        printf(": ");
        for (int i = 0; i < n; i++) printf("%lld ", L[i]);
    }
    printf("\n");

    printf("\nMerge sequence%s\n", n <= 30 ? "" : " (hidden for n > 30)");
    long long cost = min_connect_cost(L, n, n <= 30);
    printf("\nMinimum total cost = %lld\n", cost);

    if (n <= 3000) {
        long long ref = naive_cost(L, n);
        printf("Validation (naive O(n^2) greedy): cost = %lld -> %s\n", ref,
               ref == cost ? "PASSED" : "FAILED");
    } else {
        printf("Validation skipped (n > 3000).\n");
    }
    return 0;
}
