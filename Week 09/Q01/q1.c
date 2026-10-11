/*
 * Q01 - Fractional Knapsack with Deterioration Rate  (DAA Lab 09)
 *
 * Model
 *   - Item i has base value v_i, weight w_i, decay rate lambda_i > 0.
 *   - Base density d_i = v_i / w_i.
 *   - Consumption speed is 1 unit of weight per unit of time, so the time at
 *     which a unit of mass is consumed equals the weight consumed before it.
 *   - A unit of item i consumed at time t earns   d_i - lambda_i * t.
 *   - Capacity W is the total weight that may be consumed.
 *
 * Algorithm (greedy / homotopy on the marginal gain)
 *   Let x_i be the amount taken from item i. The total value is
 *        F(x) = sum d_i x_i - 1/2 * sum_{i,j} min(lambda_i, lambda_j) x_i x_j
 *   once the items are scheduled in DECREASING order of lambda.
 *   The program grows x greedily: at every step the item with the best
 *   marginal gain g_i = dF/dx_i is "led"; among all items tied at the top the
 *   one with the SMALLEST lambda receives the mass. Each step ends at the next
 *   event (item full, a new item ties, capacity used, gain reaches 0).
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_N 1000
#define EPS 1e-9

typedef struct {
    double v, w, lambda, d; /* input data and base density          */
    double x;               /* amount of weight taken                */
    double g;               /* current marginal gain                 */
    int full;               /* x == w                                */
    int member;             /* belongs to the tied "leader" set      */
} Item;

typedef struct {
    double lambda, d, x;
    int id;
} Slot;

/* small input helpers                                                 */
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
        if (val < lo || val > hi) {
            printf("  Value must be in [%d, %d].\n", lo, hi);
            continue;
        }
        return val;
    }
}

static double read_positive_double(const char *prompt) {
    double val;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%lf", &val) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  Invalid input, try again.\n");
            continue;
        }
        if (val <= 0) {
            printf("  Value must be > 0.\n");
            continue;
        }
        return val;
    }
}

static double rand_range(double lo, double hi) {
    return lo + (hi - lo) * ((double)rand() / (double)RAND_MAX);
}

static int choose_input_method(void) {
    printf("Select input method:\n");
    printf("  1. Manual user input\n");
    printf("  2. Randomized data generation\n");
    return read_int("Enter choice (1/2): ", 1, 2);
}

/* input                                                               */
static void input_manual(Item *it, int *n, double *W) {
    *n = read_int("Number of items n (1..1000): ", 1, MAX_N);
    printf("Enter  value  weight  decay_rate  for each item (all > 0):\n");
    for (int i = 0; i < *n; i++) {
        printf("  item %d: ", i + 1);
        double v, w, l;
        while (scanf("%lf %lf %lf", &v, &w, &l) != 3 || v <= 0 || w <= 0 || l <= 0) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (c == EOF) exit(1);
            printf("  All three numbers must be positive. Re-enter item %d: ", i + 1);
        }
        it[i].v = v; it[i].w = w; it[i].lambda = l;
    }
    *W = read_positive_double("Knapsack capacity W (> 0): ");
}

/* Constraints: v_i in [10,200], w_i in [1,20], lambda_i in [0.01,1.00],
 * 0 < W <= sum of weights.                                              */
static void input_random(Item *it, int *n, double *W) {
    *n = read_int("Number of items n (1..1000): ", 1, MAX_N);
    double total = 0;
    for (int i = 0; i < *n; i++) {
        it[i].v = 10 + rand() % 191;
        it[i].w = 1 + rand() % 20;
        it[i].lambda = 0.01 * (1 + rand() % 100);
        total += it[i].w;
    }
    *W = floor(rand_range(total / 4.0, total / 2.0));
    if (*W < 1) *W = 1;
}

/* value of a given amount vector, items scheduled by decreasing lambda */
static int cmp_slot(const void *a, const void *b) {
    const Slot *p = a, *q = b;
    if (p->lambda > q->lambda) return -1;
    if (p->lambda < q->lambda) return 1;
    return p->id - q->id;
}

static void build_slots(const Item *it, int n, const double *x, Slot *s) {
    for (int i = 0; i < n; i++) {
        s[i].lambda = it[i].lambda;
        s[i].d = it[i].d;
        s[i].x = x[i];
        s[i].id = i;
    }
    qsort(s, (size_t)n, sizeof(Slot), cmp_slot);
}

static double schedule_value(const Item *it, int n, const double *x) {
    Slot *s = malloc((size_t)n * sizeof(Slot));
    build_slots(it, n, x, s);
    double t = 0, total = 0;
    for (int i = 0; i < n; i++) {
        total += s[i].d * s[i].x - s[i].lambda * (t * s[i].x + 0.5 * s[i].x * s[i].x);
        t += s[i].x;
    }
    free(s);
    return total;
}

/* core greedy algorithm                                               */
static void init_state(Item *it, int n) {
    for (int i = 0; i < n; i++) {
        it[i].d = it[i].v / it[i].w;
        it[i].x = 0;
        it[i].g = it[i].d;
        it[i].full = 0;
        it[i].member = 0;
    }
}

/* Re-create the leader set: all non-full items whose gain is the maximum.
 * Returns 0 when no item with a positive gain is left.                    */
static int refill_leader_set(Item *it, int n) {
    double best = -1e300;
    for (int i = 0; i < n; i++)
        if (!it[i].full && it[i].g > best) best = it[i].g;
    if (best <= EPS) return 0;
    for (int i = 0; i < n; i++)
        if (!it[i].full && it[i].g >= best - 1e-7 * (1.0 + fabs(best))) it[i].member = 1;
    return 1;
}

/* Returns the total time (weight) consumed. */
static double solve_knapsack(Item *it, int n, double W) {
    double used = 0;
    init_state(it, n);
    for (;;) {
        /* grower = member with the smallest lambda */
        int k = -1;
        for (int i = 0; i < n; i++)
            if (it[i].member && !it[i].full && (k < 0 || it[i].lambda < it[k].lambda)) k = i;
        if (k < 0) {
            if (!refill_leader_set(it, n)) break;
            continue;
        }
        double mu = it[k].g;
        if (mu <= EPS || used >= W - EPS) break;

        double step = it[k].w - it[k].x;    /* item becomes full        */
        int event = 0, joiner = -1;
        if (W - used < step) { step = W - used; event = 1; }          /* capacity */
        if (mu / it[k].lambda < step) { step = mu / it[k].lambda; event = 2; } /* gain 0 */
        for (int i = 0; i < n; i++) {                                 /* new tie  */
            if (it[i].full || it[i].member || it[i].lambda >= it[k].lambda) continue;
            double gap = mu - it[i].g;
            if (gap < 0) gap = 0;
            double dj = gap / (it[k].lambda - it[i].lambda);
            if (dj < step) { step = dj; event = 3; joiner = i; }
        }

        it[k].x += step;
        used += step;
        for (int i = 0; i < n; i++)
            it[i].g -= fmin(it[i].lambda, it[k].lambda) * step;

        if (event == 0) { it[k].full = 1; it[k].x = it[k].w; it[k].member = 0; }
        else if (event == 3) it[joiner].member = 1;
        else break;                         /* capacity reached / gain 0 */
    }
    return used;
}

/* reporting                                                           */
static void print_instance(const Item *it, int n, double W) {
    printf("\nInput (n = %d, W = %.2f)\n", n, W);
    if (n <= 30) {
        printf("%5s %10s %10s %10s %10s\n", "item", "value", "weight", "lambda", "density");
        for (int i = 0; i < n; i++)
            printf("%5d %10.2f %10.2f %10.4f %10.4f\n", i + 1, it[i].v, it[i].w, it[i].lambda,
                   it[i].v / it[i].w);
    }
}

static double print_schedule(const Item *it, int n) {
    double *x = calloc((size_t)n, sizeof(double));
    Slot *s = malloc((size_t)n * sizeof(Slot));
    for (int i = 0; i < n; i++) x[i] = it[i].x;
    build_slots(it, n, x, s);

    printf("\nOptimal schedule (decreasing decay rate)\n");
    printf("%5s %9s %9s %10s %12s %12s %12s\n", "item", "start t", "taken", "fraction",
           "density@start", "density@end", "value");
    double t = 0, total = 0;
    for (int i = 0; i < n; i++) {
        if (s[i].x <= EPS) continue;
        double gain = s[i].d * s[i].x - s[i].lambda * (t * s[i].x + 0.5 * s[i].x * s[i].x);
        printf("%5d %9.3f %9.3f %9.1f%% %12.4f %12.4f %12.4f\n", s[i].id + 1, t, s[i].x,
               100.0 * s[i].x / it[s[i].id].w, s[i].d - s[i].lambda * t,
               s[i].d - s[i].lambda * (t + s[i].x), gain);
        total += gain;
        t += s[i].x;
    }
    printf("\nTotal time used : %.4f\n", t);
    printf("Maximum value   : %.6f\n", total);
    free(x);
    free(s);
    return total;
}

/* validation: no feasible local move may improve the value            */
/* F is concave, so "no improving move" means globally optimal.        */
static int validate_solution(Item *it, int n, double W, double used) {
    double *x = malloc((size_t)n * sizeof(double));
    double *y = malloc((size_t)n * sizeof(double));
    for (int i = 0; i < n; i++) x[i] = it[i].x;
    double base = schedule_value(it, n, x);
    int bad = 0, trials = 4000;

    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < n; i++) y[i] = x[i];
        int i = rand() % n, j = rand() % n;
        double shrink = pow(rand_range(0, 1), 3.0);
        int op = rand() % 3;
        if (op == 0 && i != j) {                       /* move mass j -> i  */
            double amt = fmin(y[j], it[i].w - y[i]) * shrink;
            y[j] -= amt; y[i] += amt;
        } else if (op == 1) {                          /* add mass to i     */
            double amt = fmin(it[i].w - y[i], W - used) * shrink;
            y[i] += amt;
        } else {                                       /* remove mass from j */
            y[j] -= y[j] * shrink;
        }
        if (schedule_value(it, n, y) > base + 1e-7 * (1.0 + fabs(base))) bad++;
    }
    printf("\nValidation: %d random feasible perturbations tried, %d improved the value -> %s\n",
           trials, bad, bad == 0 ? "PASSED (solution is optimal)" : "FAILED");
    free(x);
    free(y);
    return bad == 0;
}

int main(void) {
    static Item items[MAX_N];
    int n;
    double W;
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    printf("=== Q01: Fractional Knapsack with Deterioration Rate ===\n");
    if (choose_input_method() == 1) input_manual(items, &n, &W);
    else input_random(items, &n, &W);

    print_instance(items, n, W);
    double used = solve_knapsack(items, n, W);
    printf("Total weight used : %.4f\n", used);
    print_schedule(items, n);
    validate_solution(items, n, W, used);
    return 0;
}
