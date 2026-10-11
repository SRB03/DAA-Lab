/*
 * Q03 - Minimum Number of Refuelling Stops  (DAA Lab 09)
 *
 * Input representation : target distance D, starting fuel F (1 unit of fuel =
 *                        1 unit of distance), and n stations stored as two
 *                        parallel arrays dist[] / fuel[] (sorted by distance).
 * Algorithm            : "reverse" greedy - drive as far as possible, remembering
 *                        every station passed in a max-heap of fuel amounts;
 *                        when stuck, retroactively refuel at the passed
 *                        station that offers the most fuel.
 * Validation           : independent O(n^2) dynamic programme
 *                        dp[j] = farthest distance reachable with j stops.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 100000

typedef struct {
    long long dist, fuel;
} Station;

typedef struct {
    long long D, F;
    int n;
    Station *st;
} Problem;

static int heap[MAX_N + 5]; /* holds station indices, max-heap by fuel */
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

static int cmp_station(const void *a, const void *b) {
    const Station *p = a, *q = b;
    if (p->dist != q->dist) return (p->dist > q->dist) - (p->dist < q->dist);
    return (p->fuel > q->fuel) - (p->fuel < q->fuel);
}

/* ------------------------------------------------------------------ */
/* input                                                               */
/* ------------------------------------------------------------------ */
static void input_manual(Problem *p) {
    p->D = read_ll("Target distance D (>= 1): ", 1, 1000000000LL);
    p->F = read_ll("Starting fuel F (>= 0): ", 0, 1000000000LL);
    p->n = (int)read_ll("Number of stations n (0..100000): ", 0, MAX_N);
    p->st = malloc((size_t)(p->n + 1) * sizeof(Station));
    for (int i = 0; i < p->n; i++) {
        printf("  station %d  (distance from origin, refuel amount): ", i + 1);
        long long d, f;
        while (scanf("%lld %lld", &d, &f) != 2 || d < 1 || f < 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Both values must be positive integers. Re-enter station %d: ", i + 1);
        }
        p->st[i].dist = d;
        p->st[i].fuel = f;
    }
}

/* Constraints: D in [20,500], 1 <= F <= D/4, station distance in [1, D-1],
 * refuel amount in [1, 60].                                              */
static void input_random(Problem *p) {
    p->n = (int)read_ll("Number of stations n (0..100000): ", 0, MAX_N);
    p->D = 20 + rand() % 481;
    p->F = 1 + rand() % (int)(p->D / 4);
    p->st = malloc((size_t)(p->n + 1) * sizeof(Station));
    for (int i = 0; i < p->n; i++) {
        p->st[i].dist = 1 + rand() % (int)(p->D - 1);
        p->st[i].fuel = 1 + rand() % 60;
    }
}

/* ------------------------------------------------------------------ */
/* max-heap                                                            */
/* ------------------------------------------------------------------ */
static void heap_push(const Station *st, int idx) {
    int i = heap_size++;
    heap[i] = idx;
    while (i > 0) {
        int par = (i - 1) / 2;
        if (st[heap[par]].fuel >= st[heap[i]].fuel) break;
        int t = heap[par]; heap[par] = heap[i]; heap[i] = t;
        i = par;
    }
}

static int heap_pop(const Station *st) {
    int top = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < heap_size && st[heap[l]].fuel > st[heap[m]].fuel) m = l;
        if (r < heap_size && st[heap[r]].fuel > st[heap[m]].fuel) m = r;
        if (m == i) break;
        int t = heap[i]; heap[i] = heap[m]; heap[m] = t;
        i = m;
    }
    return top;
}

/* ------------------------------------------------------------------ */
/* core logic                                                          */
/* ------------------------------------------------------------------ */
/* Returns the minimum number of stops, or -1 if D is unreachable.
 * chosen[] receives the station indices used (in the order they were used). */
static int min_refuel_stops(const Problem *p, int *chosen) {
    long long reach = p->F;
    int stops = 0, i = 0;
    heap_size = 0;
    while (reach < p->D) {
        while (i < p->n && p->st[i].dist <= reach) heap_push(p->st, i++);
        if (heap_size == 0) return -1;
        int s = heap_pop(p->st);
        reach += p->st[s].fuel;
        chosen[stops++] = s;
    }
    return stops;
}

/* Independent check: dp[j] = farthest point reachable using exactly <= j stops */
static int min_stops_dp(const Problem *p) {
    long long *dp = calloc((size_t)p->n + 1, sizeof(long long));
    dp[0] = p->F;
    for (int i = 0; i < p->n; i++)
        for (int j = i + 1; j >= 1; j--)
            if (dp[j - 1] >= p->st[i].dist && dp[j - 1] + p->st[i].fuel > dp[j])
                dp[j] = dp[j - 1] + p->st[i].fuel;
    int ans = -1;
    for (int j = 0; j <= p->n; j++)
        if (dp[j] >= p->D) { ans = j; break; }
    free(dp);
    return ans;
}

/* ------------------------------------------------------------------ */
int main(void) {
    Problem p;
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q03: Minimum Number of Refuelling Stops ===\n");
    if (choose_input_method() == 1) input_manual(&p);
    else input_random(&p);

    qsort(p.st, (size_t)p.n, sizeof(Station), cmp_station);

    printf("\nInput: target D = %lld, initial fuel F = %lld, stations n = %d\n", p.D, p.F, p.n);
    if (p.n <= 30) {
        printf("  (distance, refuel):");
        for (int i = 0; i < p.n; i++) printf(" (%lld,%lld)", p.st[i].dist, p.st[i].fuel);
        printf("\n");
    }

    int *chosen = malloc((size_t)(p.n + 1) * sizeof(int));
    int ans = min_refuel_stops(&p, chosen);

    if (ans < 0) printf("\nResult: target is UNREACHABLE (-1)\n");
    else {
        printf("\nResult: minimum refuelling stops = %d\n", ans);
        if (ans > 0 && ans <= 30) {
            printf("  Stations used (in order of use, distance/fuel):");
            for (int i = 0; i < ans; i++)
                printf(" (%lld,%lld)", p.st[chosen[i]].dist, p.st[chosen[i]].fuel);
            printf("\n");
        }
    }

    if (p.n <= 5000) {
        int ref = min_stops_dp(&p);
        printf("\nValidation (O(n^2) dynamic programme): answer = %d -> %s\n", ref,
               ref == ans ? "PASSED" : "FAILED");
    } else {
        printf("\nValidation skipped (n > 5000, DP would be too slow).\n");
    }
    free(chosen);
    free(p.st);
    return 0;
}
