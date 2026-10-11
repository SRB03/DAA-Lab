/*
 * Q06 - Reorganise String with K-Distance Apart  (DAA Lab 09)
 *
 * Input representation : string S and integer K; character frequencies are
 *                        kept in a 256-entry count table.
 * Algorithm            : greedy with a max-heap of (remaining count, character)
 *                        and a FIFO "cool-down" queue of length K.
 *                        At each position the most frequent character that is
 *                        not cooling down is placed; it re-enters the heap
 *                        only after K-1 further positions have been filled.
 *                        If the heap is empty before the string is complete,
 *                        no valid arrangement exists -> empty string.
 * Validation           : checks the output is a permutation of S with equal
 *                        characters >= K apart; for |S| <= 9 an exhaustive
 *                        search also confirms feasibility/infeasibility.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 100000
#define ALPHA 256

typedef struct {
    int count;
    unsigned char ch;
} Entry;

static Entry heap[ALPHA + 5];
static int heap_size;

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
static void input_manual(char *s, int *k) {
    for (;;) {
        printf("Enter string S (no spaces, 1..%d characters): ", MAX_LEN);
        static char buf[MAX_LEN + 10];
        if (scanf("%100008s", buf) != 1) exit(1);
        if (strlen(buf) >= 1 && strlen(buf) <= MAX_LEN) { strcpy(s, buf); break; }
        printf("  String too long.\n");
    }
    *k = read_int("Enter K (1..length of S): ", 1, (int)strlen(s));
}

/* Constraints: |S| in [4,16], letters drawn from the first 2..5 letters of
 * the alphabet, 1 <= K <= 4 (K <= |S|).                                   */
static void input_random(char *s, int *k) {
    int len = 4 + rand() % 13;
    int alpha = 2 + rand() % 4;
    for (int i = 0; i < len; i++) s[i] = (char)('a' + rand() % alpha);
    s[len] = '\0';
    *k = 1 + rand() % 4;
    if (*k > len) *k = len;
}

/* ------------------------------------------------------------------ */
/* max-heap on (count desc, char asc)                                  */
/* ------------------------------------------------------------------ */
static int better(Entry a, Entry b) {
    if (a.count != b.count) return a.count > b.count;
    return a.ch < b.ch;
}

static void heap_push(Entry e) {
    int i = heap_size++;
    heap[i] = e;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!better(heap[i], heap[p])) break;
        Entry t = heap[i]; heap[i] = heap[p]; heap[p] = t;
        i = p;
    }
}

static Entry heap_pop(void) {
    Entry top = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < heap_size && better(heap[l], heap[m])) m = l;
        if (r < heap_size && better(heap[r], heap[m])) m = r;
        if (m == i) break;
        Entry t = heap[i]; heap[i] = heap[m]; heap[m] = t;
        i = m;
    }
    return top;
}

/* ------------------------------------------------------------------ */
/* core logic                                                          */
/* ------------------------------------------------------------------ */
/* Writes the rearranged string into out (empty string if impossible).
 * Returns 1 on success, 0 if impossible.                              */
static int reorganize(const char *s, int k, char *out) {
    int n = (int)strlen(s);
    int cnt[ALPHA] = {0};
    for (int i = 0; i < n; i++) cnt[(unsigned char)s[i]]++;

    heap_size = 0;
    for (int c = 0; c < ALPHA; c++)
        if (cnt[c] > 0) heap_push((Entry){cnt[c], (unsigned char)c});

    Entry *queue = malloc((size_t)(n + 1) * sizeof(Entry));
    int qh = 0, qt = 0;

    for (int i = 0; i < n; i++) {
        if (heap_size == 0) { out[0] = '\0'; free(queue); return 0; }
        Entry e = heap_pop();
        out[i] = (char)e.ch;
        e.count--;
        queue[qt++] = e;                 /* cool down for the next k-1 positions */
        if (qt - qh == k) {
            Entry back = queue[qh++];
            if (back.count > 0) heap_push(back);
        }
    }
    out[n] = '\0';
    free(queue);
    return 1;
}

/* ------------------------------------------------------------------ */
/* validation                                                          */
/* ------------------------------------------------------------------ */
static int arrangement_ok(const char *s, const char *t, int k) {
    int n = (int)strlen(s);
    if ((int)strlen(t) != n) return 0;
    int a[ALPHA] = {0}, b[ALPHA] = {0};
    for (int i = 0; i < n; i++) { a[(unsigned char)s[i]]++; b[(unsigned char)t[i]]++; }
    if (memcmp(a, b, sizeof a) != 0) return 0;
    int last[ALPHA];
    for (int c = 0; c < ALPHA; c++) last[c] = -1000000000;
    for (int i = 0; i < n; i++) {
        unsigned char c = (unsigned char)t[i];
        if (i - last[c] < k) return 0;
        last[c] = i;
    }
    return 1;
}

static int brute(int *cnt, int *last, int pos, int n, int k) {
    if (pos == n) return 1;
    for (int c = 0; c < ALPHA; c++) {
        if (cnt[c] == 0 || pos - last[c] < k) continue;
        int old = last[c];
        cnt[c]--; last[c] = pos;
        int ok = brute(cnt, last, pos + 1, n, k);
        cnt[c]++; last[c] = old;
        if (ok) return 1;
    }
    return 0;
}

static int brute_feasible(const char *s, int k) {
    int cnt[ALPHA] = {0}, last[ALPHA];
    int n = (int)strlen(s);
    for (int i = 0; i < n; i++) cnt[(unsigned char)s[i]]++;
    for (int c = 0; c < ALPHA; c++) last[c] = -1000000000;
    return brute(cnt, last, 0, n, k);
}

/* ------------------------------------------------------------------ */
int main(void) {
    static char s[MAX_LEN + 10], out[MAX_LEN + 10];
    int k;
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q06: Reorganise String with K-Distance Apart ===\n");
    if (choose_input_method() == 1) input_manual(s, &k);
    else input_random(s, &k);

    printf("\nInput: S = \"%s\", K = %d\n", strlen(s) <= 60 ? s : "(long string)", k);

    int ok = reorganize(s, k, out);
    if (ok) printf("Result: \"%s\"\n", strlen(out) <= 60 ? out : "(long string)");
    else printf("Result: \"\"  (impossible)\n");

    printf("\nValidation\n");
    if (ok) printf("  valid permutation with equal characters >= K apart -> %s\n",
                   arrangement_ok(s, out, k) ? "PASSED" : "FAILED");
    if (strlen(s) <= 9) {
        int feasible = brute_feasible(s, k);
        printf("  exhaustive search says feasible = %s -> %s\n", feasible ? "yes" : "no",
               feasible == ok ? "PASSED (agrees with greedy)" : "FAILED");
    } else {
        printf("  exhaustive feasibility check skipped (|S| > 9)\n");
    }
    return 0;
}
