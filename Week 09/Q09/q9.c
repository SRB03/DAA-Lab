/*
 * Q09 - Hu-Tucker Greedy Simulation (optimal alphabetic binary tree)  (DAA Lab 09)
 *
 * Input representation : ordered weights w[0..n-1] (positive integers); the
 *                        in-order sequence of the leaves must stay 1,2,...,n.
 *
 * Hu-Tucker algorithm
 *   Phase 1 (combination): keep a sequence of nodes; leaves are "terminal".
 *            Two nodes are COMPATIBLE if no terminal node lies strictly between
 *            them. Repeatedly merge the compatible pair of minimum total weight
 *            (ties: leftmost pair); the new internal node takes the position of
 *            the RIGHT member of the pair. The depth of every leaf in the
 *            resulting (possibly non-alphabetic) tree is its level.
 *   Phase 2 (levels)     : read the leaf levels l_i off that tree.
 *   Phase 3 (recombination): scan the leaves left to right with a stack and
 *            merge the two top entries whenever their levels are equal; this
 *            builds an ALPHABETIC tree with exactly the same leaf levels.
 *   Cost = sum w_i * l_i.
 *
 * Validation           : classic O(n^3) interval dynamic programme for the
 *                        optimal alphabetic tree.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 500
#define MAX_NODES (2 * MAX_N + 5)

typedef struct {
    long long w;
    int term; /* 1 = original leaf (terminal) */
    int id;   /* node id in the phase-1 tree  */
} SeqNode;

static int p1_left[MAX_NODES], p1_right[MAX_NODES];
static long long p1_w[MAX_NODES];
static int p1_count;

static int a_left[MAX_NODES], a_right[MAX_NODES]; /* final alphabetic tree */
static int a_count;

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
static int input_manual(long long *w) {
    int n = read_int("Number of weights n (1..500): ", 1, MAX_N);
    printf("Enter %d positive integer weights in sequence order: ", n);
    for (int i = 0; i < n; i++) {
        while (scanf("%lld", &w[i]) != 1 || w[i] < 1 || w[i] > 1000000000LL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Weights must be integers in [1, 1e9]. Re-enter weight %d: ", i + 1);
        }
    }
    return n;
}

/* Constraint: positive integer weights in [1, 50]. */
static int input_random(long long *w) {
    int n = read_int("Number of weights n (1..500): ", 1, MAX_N);
    for (int i = 0; i < n; i++) w[i] = 1 + rand() % 50;
    return n;
}

/* ------------------------------------------------------------------ */
/* Phase 1: combination                                                */
/* ------------------------------------------------------------------ */
static int find_min_compatible_pair(const SeqNode *seq, int m, int *bi, int *bj) {
    long long best = -1;
    long long run_w = 0;
    int run_idx = -1;
    /* scan right to left; run = lightest node in (p, next terminal after p] */
    for (int p = m - 2; p >= 0; p--) {
        int q = p + 1;
        /* a terminal q cuts the run; otherwise extend it, preferring the
         * left-most node among equal weights                              */
        if (seq[q].term || run_idx < 0 || seq[q].w <= run_w) { run_w = seq[q].w; run_idx = q; }
        long long cand = seq[p].w + run_w;
        if (best < 0 || cand <= best) { best = cand; *bi = p; *bj = run_idx; }
    }
    return best >= 0;
}

static int phase1_combine(const long long *w, int n) {
    if (n < 1) return -1;
    SeqNode *seq = calloc((size_t)n, sizeof(SeqNode));
    p1_count = 0;
    for (int i = 0; i < n; i++) {
        p1_left[p1_count] = p1_right[p1_count] = -1;
        p1_w[p1_count] = w[i];
        seq[i] = (SeqNode){w[i], 1, p1_count};
        p1_count++;
    }
    int m = n;
    while (m > 1) {
        int bi = 0, bj = 1;
        find_min_compatible_pair(seq, m, &bi, &bj);
        int id = p1_count++;
        p1_left[id] = seq[bi].id;
        p1_right[id] = seq[bj].id;
        p1_w[id] = seq[bi].w + seq[bj].w;
        seq[bj] = (SeqNode){p1_w[id], 0, id};  /* new node sits where the right one was */
        for (int k = bi; k < m - 1; k++) seq[k] = seq[k + 1];
        m--;
    }
    int root = seq[0].id;
    free(seq);
    return root;
}

/* Phase 2: leaf levels */
static void collect_levels(int node, int depth, int *level) {
    if (p1_left[node] < 0) { level[node] = depth; return; }
    collect_levels(p1_left[node], depth + 1, level);
    collect_levels(p1_right[node], depth + 1, level);
}

/* Phase 3: rebuild an alphabetic tree with the given levels.
 * Returns the root id or -1 if the levels are not realisable. */
static int phase3_rebuild(const int *level, int n) {
    int *stk_level = malloc((size_t)(n + 1) * sizeof(int));
    int *stk_node = malloc((size_t)(n + 1) * sizeof(int));
    int top = 0;
    a_count = n; /* ids 0..n-1 are the leaves */
    for (int i = 0; i < n; i++) {
        stk_level[top] = level[i];
        stk_node[top] = i;
        top++;
        while (top >= 2 && stk_level[top - 1] == stk_level[top - 2]) {
            int id = a_count++;
            a_left[id] = stk_node[top - 2];
            a_right[id] = stk_node[top - 1];
            top -= 2;
            stk_level[top] = stk_level[top + 1] - 1;
            stk_node[top] = id;
            top++;
        }
    }
    int root = (top == 1 && stk_level[0] == 0) ? stk_node[0] : -1;
    if (n == 1) root = 0;
    free(stk_level);
    free(stk_node);
    return root;
}

static void print_tree(int node, int n) {
    if (node < n) { printf("%d", node + 1); return; }
    printf("(");
    print_tree(a_left[node], n);
    printf(" ");
    print_tree(a_right[node], n);
    printf(")");
}

/* ------------------------------------------------------------------ */
/* validation: interval DP for the optimal alphabetic tree             */
/* ------------------------------------------------------------------ */
static long long optimal_alphabetic_cost(const long long *w, int n) {
    long long *pre = calloc((size_t)n + 1, sizeof(long long));
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + w[i];
    long long *cost = calloc((size_t)n * n, sizeof(long long));
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            long long best = -1;
            for (int k = i; k < j; k++) {
                long long c = cost[i * n + k] + cost[(k + 1) * n + j];
                if (best < 0 || c < best) best = c;
            }
            cost[i * n + j] = best + pre[j + 1] - pre[i];
        }
    long long ans = cost[0 * n + (n - 1)];
    free(pre);
    free(cost);
    return ans;
}

/* ------------------------------------------------------------------ */
int main(void) {
    static long long w[MAX_N + 5];
    static int level[MAX_NODES];
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q09: Hu-Tucker Optimal Alphabetic Tree ===\n");
    int n = choose_input_method() == 1 ? input_manual(w) : input_random(w);

    if (n <= 40) {
        printf("\nWeights: ");
        for (int i = 0; i < n; i++) printf("%lld ", w[i]);
        printf("\n");
    } else printf("\n%d weights generated.\n", n);

    long long cost = 0;
    int root = -1;
    if (n == 1) {
        level[0] = 0;
        root = 0;
        a_count = 1;
    } else {
        int p1root = phase1_combine(w, n);
        collect_levels(p1root, 0, level);
        root = phase3_rebuild(level, n);
    }
    for (int i = 0; i < n; i++) cost += w[i] * level[i];

    if (n <= 40) {
        printf("\nLeaf levels (depths): ");
        for (int i = 0; i < n; i++) printf("%d ", level[i]);
        printf("\n");
    }
    if (root < 0) {
        printf("\nERROR: levels could not be recombined into an alphabetic tree.\n");
    } else if (n <= 30) {
        printf("Alphabetic tree (leaf numbers, left-to-right order preserved):\n  ");
        print_tree(root, n);
        printf("\n");
    }
    printf("\nMinimum weighted path length  sum(w_i * depth_i) = %lld\n", cost);

    printf("\nValidation\n");
    printf("  alphabetic tree rebuilt from the levels : %s\n", root >= 0 ? "PASSED" : "FAILED");
    if (n <= 150) {
        long long ref = optimal_alphabetic_cost(w, n);
        printf("  interval-DP optimum = %lld -> %s\n", ref, ref == cost ? "PASSED" : "FAILED");
    } else {
        printf("  interval-DP check skipped (n > 150)\n");
    }
    return 0;
}
