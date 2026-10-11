/*
 * Q02 - Huffman Coding with canonical codebook  (DAA Lab 09)
 *
 * Input representation : n symbols (single characters) with positive
 *                        integer frequencies  ->  arrays sym[] and freq[].
 * Algorithm            : classic greedy Huffman construction with a binary
 *                        min-heap (ties broken by node creation order so the
 *                        result is deterministic), then the code LENGTHS are
 *                        turned into the canonical codebook.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_SYM 256
#define MAX_NODES (2 * MAX_SYM)

typedef struct {
    long long freq;
    int left, right; /* -1 for a leaf          */
    int sym_index;   /* index into sym[], leaf */
} Node;

typedef struct {
    int n;
    char sym[MAX_SYM];
    long long freq[MAX_SYM];
} Input;

typedef struct {
    int len[MAX_SYM];
    char code[MAX_SYM][MAX_SYM + 2];
    int order[MAX_SYM]; /* symbol indices sorted by (length, symbol) */
} Codebook;

static Node tree[MAX_NODES];
static int node_count;
static int heap[MAX_NODES];
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
static void input_manual(Input *in) {
    in->n = read_int("Number of symbols n (1..256): ", 1, MAX_SYM);
    printf("Enter  symbol  frequency  for each symbol (distinct non-space characters, freq >= 1):\n");
    for (int i = 0; i < in->n; i++) {
        for (;;) {
            char c;
            long long f;
            printf("  symbol %d: ", i + 1);
            if (scanf(" %c %lld", &c, &f) != 2 || f < 1) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                if (ch == EOF) exit(1);
                printf("  Enter a character and a positive integer.\n");
                continue;
            }
            int dup = 0;
            for (int j = 0; j < i; j++) if (in->sym[j] == c) dup = 1;
            if (dup) { printf("  Symbol '%c' already used.\n", c); continue; }
            in->sym[i] = c;
            in->freq[i] = f;
            break;
        }
    }
}

/* Constraints: n <= 94 distinct printable characters, freq in [1, 100]. */
static void input_random(Input *in) {
    in->n = read_int("Number of symbols n (1..94): ", 1, 94);
    char pool[94];
    for (int i = 0; i < 94; i++) pool[i] = (char)(33 + i);
    for (int i = 93; i > 0; i--) { /* shuffle */
        int j = rand() % (i + 1);
        char t = pool[i]; pool[i] = pool[j]; pool[j] = t;
    }
    for (int i = 0; i < in->n; i++) {
        in->sym[i] = pool[i];
        in->freq[i] = 1 + rand() % 100;
    }
}

/* ------------------------------------------------------------------ */
/* min-heap on node indices ordered by (freq, index)                   */
/* ------------------------------------------------------------------ */
static int heap_less(int a, int b) {
    if (tree[a].freq != tree[b].freq) return tree[a].freq < tree[b].freq;
    return a < b;
}

static void heap_push(int v) {
    int i = heap_size++;
    heap[i] = v;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!heap_less(heap[i], heap[p])) break;
        int t = heap[i]; heap[i] = heap[p]; heap[p] = t;
        i = p;
    }
}

static int heap_pop(void) {
    int top = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < heap_size && heap_less(heap[l], heap[m])) m = l;
        if (r < heap_size && heap_less(heap[r], heap[m])) m = r;
        if (m == i) break;
        int t = heap[i]; heap[i] = heap[m]; heap[m] = t;
        i = m;
    }
    return top;
}

/* ------------------------------------------------------------------ */
/* Huffman tree and code lengths                                       */
/* ------------------------------------------------------------------ */
static int build_huffman_tree(const Input *in) {
    node_count = 0;
    heap_size = 0;
    for (int i = 0; i < in->n; i++) {
        tree[node_count] = (Node){in->freq[i], -1, -1, i};
        heap_push(node_count++);
    }
    while (heap_size > 1) {
        int a = heap_pop();
        int b = heap_pop();
        tree[node_count] = (Node){tree[a].freq + tree[b].freq, a, b, -1};
        heap_push(node_count++);
    }
    return heap_pop();
}

static void assign_lengths(int root, int depth, Codebook *cb) {
    if (tree[root].left < 0) {
        cb->len[tree[root].sym_index] = depth;
        return;
    }
    assign_lengths(tree[root].left, depth + 1, cb);
    assign_lengths(tree[root].right, depth + 1, cb);
}

/* ------------------------------------------------------------------ */
/* canonical codebook: codes ordered by (length, symbol)               */
/* ------------------------------------------------------------------ */
static const Input *g_sort_input;
static const Codebook *g_sort_cb;

static int cmp_canonical(const void *a, const void *b) {
    int i = *(const int *)a, j = *(const int *)b;
    if (g_sort_cb->len[i] != g_sort_cb->len[j]) return g_sort_cb->len[i] - g_sort_cb->len[j];
    return (unsigned char)g_sort_input->sym[i] - (unsigned char)g_sort_input->sym[j];
}

static void increment_binary(char *s, int len) {
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == '0') { s[i] = '1'; return; }
        s[i] = '0';
    }
}

static void assign_canonical_codes(const Input *in, Codebook *cb) {
    for (int i = 0; i < in->n; i++) cb->order[i] = i;
    g_sort_input = in;
    g_sort_cb = cb;
    qsort(cb->order, (size_t)in->n, sizeof(int), cmp_canonical);

    char cur[MAX_SYM + 2];
    int cur_len = 0;
    for (int k = 0; k < in->n; k++) {
        int s = cb->order[k];
        int L = cb->len[s];
        if (k == 0) {
            memset(cur, '0', (size_t)L);
        } else {
            increment_binary(cur, cur_len);
            for (int p = cur_len; p < L; p++) cur[p] = '0'; /* append zeros */
        }
        cur[L] = '\0';
        cur_len = L;
        strcpy(cb->code[s], cur);
    }
}

static void build_codebook(const Input *in, Codebook *cb) {
    memset(cb, 0, sizeof(*cb));
    if (in->n == 1) { cb->len[0] = 1; } /* single symbol still needs 1 bit */
    else {
        int root = build_huffman_tree(in);
        assign_lengths(root, 0, cb);
    }
    assign_canonical_codes(in, cb);
}

/* ------------------------------------------------------------------ */
/* reporting and validation                                            */
/* ------------------------------------------------------------------ */
static void print_codebook(const Input *in, const Codebook *cb) {
    long long total = 0, bits = 0;
    printf("\nCanonical Huffman codebook\n");
    printf("%8s %10s %7s  %s\n", "symbol", "frequency", "length", "code");
    for (int k = 0; k < in->n; k++) {
        int s = cb->order[k];
        printf("%8c %10lld %7d  %s\n", in->sym[s], in->freq[s], cb->len[s], cb->code[s]);
        total += in->freq[s];
        bits += in->freq[s] * cb->len[s];
    }
    printf("\nTotal weighted length (bits) : %lld\n", bits);
    printf("Expected code length         : %.6f bits/symbol\n", (double)bits / (double)total);
}

static int validate_codebook(const Input *in, const Codebook *cb) {
    int ok = 1;
    /* 1. prefix-free */
    for (int i = 0; i < in->n && ok; i++)
        for (int j = 0; j < in->n; j++) {
            if (i == j) continue;
            if (strncmp(cb->code[i], cb->code[j], (size_t)cb->len[i]) == 0 && cb->len[i] <= cb->len[j]) {
                ok = 0;
                break;
            }
        }
    int prefix_ok = ok;
    /* 2. Kraft sum = 1 for a full binary tree (n >= 2) */
    long double kraft = 0;
    for (int i = 0; i < in->n; i++) kraft += powl(2.0L, -(long double)cb->len[i]);
    int kraft_ok = (in->n == 1) || fabsl(kraft - 1.0L) < 1e-9L;
    /* 3. optimal cost = sum of internal-node weights of the Huffman tree */
    long long bits = 0, internal = 0;
    for (int i = 0; i < in->n; i++) bits += in->freq[i] * cb->len[i];
    for (int i = 0; i < node_count; i++) if (tree[i].left >= 0) internal += tree[i].freq;
    int cost_ok = (in->n == 1) || bits == internal;
    /* 4. canonical order: codes strictly increase when read as binary strings padded right */
    int canon_ok = 1;
    for (int k = 1; k < in->n; k++) {
        int a = cb->order[k - 1], b = cb->order[k];
        if (cb->len[a] > cb->len[b]) canon_ok = 0;
        char pa[MAX_SYM + 2], pb[MAX_SYM + 2];
        int L = cb->len[b];
        strcpy(pa, cb->code[a]);
        for (int p = cb->len[a]; p < L; p++) pa[p] = '0';
        pa[L] = '\0';
        strcpy(pb, cb->code[b]);
        if (strcmp(pa, pb) >= 0) canon_ok = 0;
    }
    printf("\nValidation\n");
    printf("  prefix-free property         : %s\n", prefix_ok ? "PASSED" : "FAILED");
    printf("  Kraft sum equals 1           : %s\n", kraft_ok ? "PASSED" : "FAILED");
    printf("  cost equals sum of internal  : %s\n", cost_ok ? "PASSED" : "FAILED");
    printf("  canonical (sorted) ordering  : %s\n", canon_ok ? "PASSED" : "FAILED");
    return prefix_ok && kraft_ok && cost_ok && canon_ok;
}

/* ------------------------------------------------------------------ */
int main(void) {
    static Input in;
    static Codebook cb;
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q02: Huffman Coding (canonical codebook) ===\n");
    if (choose_input_method() == 1) input_manual(&in);
    else input_random(&in);

    printf("\nInput (n = %d)\n", in.n);
    if (in.n <= 40) {
        for (int i = 0; i < in.n; i++) printf("  '%c' : %lld\n", in.sym[i], in.freq[i]);
    }

    build_codebook(&in, &cb);
    print_codebook(&in, &cb);
    validate_codebook(&in, &cb);
    return 0;
}
