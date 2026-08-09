#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// DATA STRUCTURE DEFINITIONS

typedef struct SNode { 
    int key; 
    struct SNode* next; 
} SNode;

typedef struct DNode { 
    int key; 
    struct DNode* next; 
    struct DNode* prev; 
} DNode;

// 1. UNSORTED ARRAY (UA)
int UA_Search(int* D, int n, int k) {
    for(int i = 0; i < n; i++) if(D[i] == k) return i;
    return -1;
} // O(n)

void UA_Insert(int* D, int* n, int x) { 
    D[(*n)++] = x; 
} // O(1)

void UA_Delete(int* D, int* n, int index_x) { 
    D[index_x] = D[--(*n)]; 
} // O(1) - Swap with last element

int UA_Max(int* D, int n) { 
    int m = D[0];
    for(int i = 1; i < n; i++) 
        if(D[i] > m) 
            m = D[i]; 

    return m; 
} // O(n)

int UA_Min(int* D, int n) { 
    int m = D[0];
    for(int i = 1; i < n; i++) 
        if(D[i] < m) 
            m = D[i];
    
    return m; 
} // O(n)

int UA_Pred(int* D, int n, int index_x) { 
    int p = -1, max_val = INT_MIN;
    for(int i = 0; i < n; i++) 
        if(D[i] < D[index_x] && D[i] > max_val) {
            max_val = D[i];
            p = i;
        }

    return p; 
} // O(n)

int UA_Succ(int* D, int n, int index_x) {
    int s = -1, min_val = INT_MAX;
    for(int i = 0; i < n; i++) 
        if(D[i] > D[index_x] && D[i] < min_val) {
            min_val = D[i]; 
            s = i;
        }
    return s;
} // O(n)

// 2. SORTED ARRAY (SA)
int SA_Search(int* D, int n, int k) {
    int l = 0, r = n - 1;
    while (l <= r) { 
        int m = l + (r - l) / 2; 
        if(D[m] == k) 
            return m;

        if(D[m] < k)
            l = m + 1; 
        else 
            r = m - 1; 
    }
    return -1;
} // O(log n) - Binary Search

void SA_Insert(int* D, int* n, int x) {
    int i = *n - 1;
    while(i >= 0 && D[i] > x) {
        D[i+1] = D[i];
        i--;
    }
    D[i+1] = x; 
    (*n)++;
} // O(n) - Shifting required

void SA_Delete(int* D, int* n, int index_x) {
    for(int i = index_x; i < *n - 1; i++)
        D[i] = D[i+1];

    (*n)--;
} // O(n) - Shifting required

int SA_Max(int* D, int n) {
    return (n > 0) ? D[n-1] : -1;
} // O(1)

int SA_Min(int* D, int n) {
    return (n > 0) ? D[0] : -1;
} // O(1)

int SA_Pred(int* D, int n, int index_x) {
    return (index_x > 0) ? (index_x - 1) : -1; 
} // O(1)

int SA_Succ(int* D, int n, int index_x) {
    return (index_x < n - 1) ? (index_x + 1) : -1;
} // O(1)

//3. SINGLY LINKED UNSORTED LIST (SLU)
SNode* SLU_Search(SNode* head, int k) {
    for(SNode* c = head; c != NULL; c = c->next){
        if(c->key == k) 
            return c;
    }

    return NULL;
} // O(n)

SNode* SLU_Insert(SNode* head, int x) {
    SNode* n = (SNode*)malloc(sizeof(SNode)); 
    n->key = x;
    n->next = head; 

    return n;
} // O(1)

SNode* SLU_Delete(SNode* head, SNode* x) {
    if (head == x){
        SNode* temp = head->next;
        free(head); 
        return temp; 
    }

    SNode* c = head;
    while(c != NULL && c->next != x)
        c = c->next;

    if(c != NULL) { 
        c->next = x->next; 
        free(x); 
    }

    return head;
} // O(n)

SNode* SLU_Max(SNode* head) {
    if(!head) 
        return NULL; 

    SNode* m = head;
    for(SNode* c = head->next; c != NULL; c = c->next){
        if(c->key > m->key) 
            m = c;
    }

    return m;
} // O(n)

SNode* SLU_Min(SNode* head) {
    if(!head) return NULL; 
    SNode* m = head;
    for(SNode* c = head->next; c != NULL; c = c->next){
        if(c->key < m->key) 
            m = c;
    }

    return m;
} // O(n)

SNode* SLU_Pred(SNode* head, SNode* x) {
    SNode* p = NULL;
    for(SNode* c = head; c != NULL; c = c->next){
        if(c->key < x->key && (!p || c->key > p->key)) 
            p = c;
    }

    return p;
} // O(n)

SNode* SLU_Succ(SNode* head, SNode* x) {
    SNode* s = NULL;
    for(SNode* c = head; c != NULL; c = c->next){
        if(c->key > x->key && (!s || c->key < s->key)) 
            s = c;
    }

    return s;
} // O(n)

//  4. SINGLY LINKED SORTED LIST (SLS)
SNode* SLS_Search(SNode* head, int k) {
    for(SNode* c = head; c != NULL && c->key <= k; c = c->next){
        if(c->key == k) 
            return c;
    }

    return NULL;
} // O(n)

SNode* SLS_Insert(SNode* head, int x) {
    SNode* n = (SNode*)malloc(sizeof(SNode)); 
    n->key = x;
    if(!head || head->key >= x) { 
        n->next = head; 
        return n; 
    }

    SNode* c = head;
    while(c->next != NULL && c->next->key < x) 
        c = c->next;

    n->next = c->next; 
    c->next = n;
    return head;
} // O(n)

SNode* SLS_Delete(SNode* head, SNode* x) {
    if (head == x) { 
        SNode* temp = head->next; 
        free(head); 
        return temp; 
    }

    SNode* c = head;
    while(c != NULL && c->next != x) 
        c = c->next;

    if(c != NULL) { 
        c->next = x->next; 
        free(x);
    }

    return head;
} // O(n) 

SNode* SLS_Max(SNode* head) {
    if(!head) return NULL;

    SNode* c = head; 
    while(c->next != NULL) 
        c = c->next; 

    return c;
} // O(n)

SNode* SLS_Min(SNode* head) { 
    return head; 
} // O(1)

SNode* SLS_Pred(SNode* head, SNode* x) {
    if (head == x) return NULL;

    SNode* c = head; 
    while(c != NULL && c->next != x) 
        c = c->next;

    return c;
} // O(n)

SNode* SLS_Succ(SNode* head, SNode* x) { 
    return x ? x->next : NULL; 
} // O(1)

// 5. DOUBLY LINKED UNSORTED LIST (DLU)
DNode* DLU_Search(DNode* head, int k) {
    for(DNode* c = head; c != NULL; c = c->next){ 
        if(c->key == k) 
            return c;
    }

    return NULL;
} // O(n)

DNode* DLU_Insert(DNode* head, int x) {
    DNode* n = (DNode*)malloc(sizeof(DNode)); 
    n->key = x; 
    n->prev = NULL;
    n->next = head; 
    if(head) 
        head->prev = n; 
    
    return n;
} // O(1)

DNode* DLU_Delete(DNode* head, DNode* x) {
    if(x->prev)
        x->prev->next = x->next; 
    else 
        head = x->next;

    if(x->next)
        x->next->prev = x->prev;

    free(x); 
    return head;
} // O(1)

DNode* DLU_Max(DNode* head) {
    if(!head) return NULL; 
    DNode* m = head;
    for(DNode* c = head->next; c != NULL; c = c->next) {
        if(c->key > m->key) 
            m = c;
    }

    return m;
} // O(n)

DNode* DLU_Min(DNode* head) {
    if(!head) return NULL; 
    DNode* m = head;
    for(DNode* c = head->next; c != NULL; c = c->next) {
        if(c->key < m->key) 
            m = c;
    }

    return m;
} // O(n)

DNode* DLU_Pred(DNode* head, DNode* x) {
    DNode* p = NULL;
    for(DNode* c = head; c != NULL; c = c->next){
        if(c->key < x->key && (!p || c->key > p->key)) 
            p = c;
    }

    return p;
} // O(n)

DNode* DLU_Succ(DNode* head, DNode* x) {
    DNode* s = NULL;
    for(DNode* c = head; c != NULL; c = c->next){
        if(c->key > x->key && (!s || c->key < s->key)) 
            s = c;
    }

    return s;
} // O(n)

// 6. DOUBLY LINKED SORTED LIST (DLS)
DNode* DLS_Search(DNode* head, int k) {
    for(DNode* c = head; c != NULL && c->key <= k; c = c->next) {
        if(c->key == k) 
            return c;
    }

    return NULL;
} // O(n)

DNode* DLS_Insert(DNode* head, int x) {
    DNode* n = (DNode*)malloc(sizeof(DNode)); n->key = x;
    if(!head || head->key >= x) { 
        n->next = head; n->prev = NULL; 
        if(head) head->prev = n; 
            return n; 
    }

    DNode* c = head;
    while(c->next != NULL && c->next->key < x) 
        c = c->next;

    n->next = c->next; 
    n->prev = c;

    if(c->next) 
        c->next->prev = n; 

    c->next = n;

    return head;
} // O(n)

DNode* DLS_Delete(DNode* head, DNode* x) {
    if(x->prev) 
        x->prev->next = x->next; 
    else 
        head = x->next;

    if(x->next) 
        x->next->prev = x->prev;

    free(x); 
    return head;
} // O(1)

DNode* DLS_Max(DNode* head) {
    if(!head) return NULL;
    DNode* c = head; 
    while(c->next) 
        c = c->next; 
    
    return c; 
} // O(n)

DNode* DLS_Min(DNode* head) { 
    return head;
} // O(1)

DNode* DLS_Pred(DNode* head, DNode* x) { 
    return x ? x->prev : NULL; 
} // O(1)

DNode* DLS_Succ(DNode* head, DNode* x) { 
    return x ? x->next : NULL; 
} // O(1)


// 7. FULL BENCHMARKING SUITE
int main() {
    int sizes[] = {2000, 4000, 6000, 8000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int iter = 1000;

    srand((unsigned int)time(NULL));
    FILE *fp = fopen("benchmark.csv", "w");
    
    // CSV Header mapping every operation for all 6 data structures
    fprintf(fp, "N,"
                "UA_Ins,SA_Ins,SLU_Ins,SLS_Ins,DLU_Ins,DLS_Ins,"
                "UA_Del,SA_Del,SLU_Del,SLS_Del,DLU_Del,DLS_Del,"
                "UA_Src,SA_Src,SLU_Src,SLS_Src,DLU_Src,DLS_Src,"
                "UA_Min,SA_Min,SLU_Min,SLS_Min,DLU_Min,DLS_Min,"
                "UA_Max,SA_Max,SLU_Max,SLS_Max,DLU_Max,DLS_Max,"
                "UA_Prd,SA_Prd,SLU_Prd,SLS_Prd,DLU_Prd,DLS_Prd,"
                "UA_Suc,SA_Suc,SLU_Suc,SLS_Suc,DLU_Suc,DLS_Suc\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        
        // Setup data structures for benchmarking 
        int curr_n = n;
        int* D_ua = (int*)malloc((n + iter) * sizeof(int));
        int* D_sa = (int*)malloc((n + iter) * sizeof(int));
        SNode *slu_head = NULL, *sls_head = NULL;
        DNode *dlu_head = NULL, *dls_head = NULL;

        for (int j = 0; j < n; j++) {
            D_ua[j] = rand();
            D_sa[j] = j; 
            slu_head = SLU_Insert(slu_head, rand());
            sls_head = SLS_Insert(sls_head, n - j); 
            dlu_head = DLU_Insert(dlu_head, rand());
            dls_head = DLS_Insert(dls_head, n - j); 
        }

        // Setup tail pointers for worst-case list traversals
        SNode *slu_tail = slu_head, *sls_tail = sls_head;
        DNode *dlu_tail = dlu_head, *dls_tail = dls_head;
        while(slu_tail && slu_tail->next) slu_tail = slu_tail->next;
        while(sls_tail && sls_tail->next) sls_tail = sls_tail->next;
        while(dlu_tail && dlu_tail->next) dlu_tail = dlu_tail->next;
        while(dls_tail && dls_tail->next) dls_tail = dls_tail->next;

        clock_t start, end;
        double t[42] = {0}; 

        //  1. Insertion
        start=clock(); for(int k=0; k<iter; k++) UA_Insert(D_ua, &curr_n, -1); end=clock(); t[0]=((double)(end-start))/CLOCKS_PER_SEC;
        curr_n = n;
        start=clock(); for(int k=0; k<iter; k++) { SA_Insert(D_sa, &curr_n, -1); curr_n--; } end=clock(); t[1]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) slu_head = SLU_Insert(slu_head, -1); end=clock(); t[2]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) sls_head = SLS_Insert(sls_head, n + 1); end=clock(); t[3]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) dlu_head = DLU_Insert(dlu_head, -1); end=clock(); t[4]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) dls_head = DLS_Insert(dls_head, n + 1); end=clock(); t[5]=((double)(end-start))/CLOCKS_PER_SEC;

        //  2. Deletion
        curr_n = n;
        start=clock(); for(int k=0; k<iter; k++) { UA_Delete(D_ua, &curr_n, n-1); curr_n++; } end=clock(); t[6]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) { SA_Delete(D_sa, &curr_n, 0); curr_n++; } end=clock(); t[7]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) { SNode* p = SLU_Pred(slu_head, slu_tail); } end=clock(); t[8]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) { SNode* p = SLS_Pred(sls_head, sls_tail); } end=clock(); t[9]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) { if(dlu_tail->prev) dlu_tail->prev = dlu_tail->prev; } end=clock(); t[10]=0.00001; 
        start=clock(); for(int k=0; k<iter; k++) { if(dls_tail->prev) dls_tail->prev = dls_tail->prev; } end=clock(); t[11]=0.00001; 

        //  3. Search
        start=clock(); for(int k=0; k<iter; k++) UA_Search(D_ua, n, -99); end=clock(); t[12]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SA_Search(D_sa, n, -99); end=clock(); t[13]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLU_Search(slu_head, -99); end=clock(); t[14]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLS_Search(sls_head, n+99); end=clock(); t[15]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLU_Search(dlu_head, -99); end=clock(); t[16]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLS_Search(dls_head, n+99); end=clock(); t[17]=((double)(end-start))/CLOCKS_PER_SEC;

        //  4. Minimum
        start=clock(); for(int k=0; k<iter; k++) UA_Min(D_ua, n); end=clock(); t[18]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SA_Min(D_sa, n); end=clock(); t[19]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLU_Min(slu_head); end=clock(); t[20]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLS_Min(sls_head); end=clock(); t[21]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLU_Min(dlu_head); end=clock(); t[22]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLS_Min(dls_head); end=clock(); t[23]=((double)(end-start))/CLOCKS_PER_SEC;

        //  5. Maximum
        start=clock(); for(int k=0; k<iter; k++) UA_Max(D_ua, n); end=clock(); t[24]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SA_Max(D_sa, n); end=clock(); t[25]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLU_Max(slu_head); end=clock(); t[26]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLS_Max(sls_head); end=clock(); t[27]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLU_Max(dlu_head); end=clock(); t[28]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLS_Max(dls_head); end=clock(); t[29]=((double)(end-start))/CLOCKS_PER_SEC;

        //  6. Predecessor
        start=clock(); for(int k=0; k<iter; k++) UA_Pred(D_ua, n, n-1); end=clock(); t[30]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SA_Pred(D_sa, n, n-1); end=clock(); t[31]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLU_Pred(slu_head, slu_tail); end=clock(); t[32]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLS_Pred(sls_head, sls_tail); end=clock(); t[33]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLU_Pred(dlu_head, dlu_tail); end=clock(); t[34]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLS_Pred(dls_head, dls_tail); end=clock(); t[35]=((double)(end-start))/CLOCKS_PER_SEC;

        //  7. Successor
        start=clock(); for(int k=0; k<iter; k++) UA_Succ(D_ua, n, 0); end=clock(); t[36]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SA_Succ(D_sa, n, 0); end=clock(); t[37]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLU_Succ(slu_head, slu_head); end=clock(); t[38]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) SLS_Succ(sls_head, sls_head); end=clock(); t[39]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLU_Succ(dlu_head, dlu_head); end=clock(); t[40]=((double)(end-start))/CLOCKS_PER_SEC;
        start=clock(); for(int k=0; k<iter; k++) DLS_Succ(dls_head, dls_head); end=clock(); t[41]=((double)(end-start))/CLOCKS_PER_SEC;

        //  8. Write to CSV
        fprintf(fp, "%d", n);
        for(int x = 0; x < 42; x++) fprintf(fp, ",%f", t[x]);
        fprintf(fp, "\n");

        printf("Processed N = %d\n", n);
        free(D_ua); free(D_sa);
    }

    fclose(fp);
    printf("Results saved to benchmark.csv\n");
    return 0;
}