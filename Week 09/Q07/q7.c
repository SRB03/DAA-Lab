/*
 * Q07 - Minimise Deviation in Array (Two-Way Greedy with Max-Heap)  (DAA Lab 09)
 *
 * Input representation : array A[0..n-1] of positive integers.
 * Operations           : odd x -> 2x   |   even x -> x/2.
 * Algorithm            : 1. Double every odd element (the only upward move that
 *                            is ever useful). All elements are now even-capable:
 *                            they can only be HALVED from here on.
 *                         2. Keep a max-heap of the current values and track the
 *                            running minimum. Repeatedly halve the maximum while it
 *                            is even; record max - min after each step.
 *                         3. Stop when the maximum is odd (it cannot decrease).
 * Validation           : exhaustive candidate-window search. Each element can only
 *                        take the values {o*2^j}; for every candidate minimum m we
 *                        take the smallest value >= m of every element.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 100000

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
static int input_manual(long long *a) {
    int n = (int)read_ll("Array size n (1..100000): ", 1, MAX_N);
    printf("Enter %d positive integers (<= 1000000000): ", n);
    for (int i = 0; i < n; i++) {
        while (scanf("%lld", &a[i]) != 1 || a[i] < 1 || a[i] > 1000000000LL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Elements must be integers in [1, 1e9]. Re-enter element %d: ", i + 1);
        }
    }
    return n;
}

/* Constraint: positive integers in [1, 1000]. */
static int input_random(long long *a) {
    int n = (int)read_ll("Array size n (1..100000): ", 1, MAX_N);
    for (int i = 0; i < n; i++) a[i] = 1 + rand() % 1000;
    return n;
}

/* ------------------------------------------------------------------ */
/* max-heap                                                            */
/* ------------------------------------------------------------------ */
static void heap_push(long long v) {
    int i = heap_size++;
    heap[i] = v;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] >= heap[i]) break;
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
        if (l < heap_size && heap[l] > heap[m]) m = l;
        if (r < heap_size && heap[r] > heap[m]) m = r;
        if (m == i) break;
        long long t = heap[i]; heap[i] = heap[m]; heap[m] = t;
        i = m;
    }
    return top;
}

/* ------------------------------------------------------------------ */
/* core logic                                                          */
/* ------------------------------------------------------------------ */
static long long minimum_deviation(const long long *a, int n) {
    heap_size = 0;
    long long mn = -1;
    for (int i = 0; i < n; i++) {
        long long v = (a[i] % 2) ? a[i] * 2 : a[i]; /* step 1: lift odd numbers */
        if (mn < 0 || v < mn) mn = v;
        heap_push(v);
    }
    long long best = heap[0] - mn;
    for (;;) {
        long long mx = heap[0];
        if (mx - mn < best) best = mx - mn;
        if (mx % 2) break;                           /* odd maximum: cannot shrink */
        heap_pop();
        mx /= 2;                                     /* step 2: halve the maximum  */
        if (mx < mn) mn = mx;
        heap_push(mx);
    }
    return best;
}

/* ------------------------------------------------------------------ */
/* validation                                                          */
/* ------------------------------------------------------------------ */
static int build_candidates(long long x, long long *cand) {
    long long o = x;
    int k = 0;
    while (o % 2 == 0) { o /= 2; k++; }
    int top = k > 1 ? k : 1;               /* odd numbers may be doubled once */
    int c = 0;
    for (int j = 0; j <= top; j++) cand[c++] = o << j;
    return c;
}

static long long brute_deviation(const long long *a, int n) {
    long long (*cand)[40] = malloc((size_t)n * sizeof *cand);
    int *cn = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) cn[i] = build_candidates(a[i], cand[i]);

    long long best = -1;
    for (int e = 0; e < n; e++)
        for (int c = 0; c < cn[e]; c++) {
            long long m = cand[e][c], mx = m;
            int ok = 1;
            for (int i = 0; i < n && ok; i++) {
                long long pick = -1;
                for (int j = 0; j < cn[i]; j++)
                    if (cand[i][j] >= m && (pick < 0 || cand[i][j] < pick)) pick = cand[i][j];
                if (pick < 0) ok = 0;
                else if (pick > mx) mx = pick;
            }
            if (ok && (best < 0 || mx - m < best)) best = mx - m;
        }
    free(cand);
    free(cn);
    return best;
}

/* ------------------------------------------------------------------ */
int main(void) {
    static long long a[MAX_N + 5];
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q07: Minimise Deviation in Array ===\n");
    int n = choose_input_method() == 1 ? input_manual(a) : input_random(a);

    if (n <= 40) {
        printf("\nArray: ");
        for (int i = 0; i < n; i++) printf("%lld ", a[i]);
        printf("\n");
    } else printf("\nArray of %d elements generated.\n", n);

    long long ans = minimum_deviation(a, n);
    printf("\nMinimum deviation = %lld\n", ans);

    if (n <= 200) {
        long long ref = brute_deviation(a, n);
        printf("Validation (exhaustive candidate window): %lld -> %s\n", ref,
               ref == ans ? "PASSED" : "FAILED");
    } else {
        printf("Validation skipped (n > 200).\n");
    }
    return 0;
}
