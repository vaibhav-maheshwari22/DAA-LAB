#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

//Data Structures
typedef struct SNode {
    int data;
    struct SNode* nxt;
} SNode;

typedef struct DNode {
    int data;
    struct DNode* prv;
    struct DNode* nxt;
} DNode;


// 1. UNSORTED ARRAY (UA)

// O(n) - Linear scan
int srch_UA(int* a, int sz, int target) {
    for (int i = 0; i < sz; i++) {
        if (a[i] == target) return i;
    }
    return -1;
}
// O(1) - Append at end
void ins_UA(int* a, int* sz, int val) {
    a[(*sz)++] = val;
}
// O(1) - Swap with last element
void del_UA(int* a, int* sz, int id) {
    if (id >= 0 && id < *sz) a[id] = a[--(*sz)];
}
// O(n) - Find max
int max_UA(int* a, int sz) {
    int m = INT_MIN;
    for (int i = 0; i < sz; i++) if (a[i] > m) m = a[i];
    return m;
}
// O(n) - Find min
int min_UA(int* a, int sz) {
    int m = INT_MAX;
    for (int i = 0; i < sz; i++) if (a[i] < m) m = a[i];
    return m;
}
// O(n) - Find max element smaller than target
int pred_UA(int* a, int sz, int id) {
    int m = INT_MIN, idx = -1;
    for (int i = 0; i < sz; i++) {
        if (a[i] < a[id] && a[i] > m) { m = a[i]; idx = i; }
    }
    return idx;
}
// O(n) - Find min element greater than target
int succ_UA(int* a, int sz, int id) {
    int m = INT_MAX, idx = -1;
    for (int i = 0; i < sz; i++) {
        if (a[i] > a[id] && a[i] < m) { m = a[i]; idx = i; }
    }
    return idx;
}


// 2. SORTED ARRAY (SA)

// O(log n) - Binary search
int srch_SA(int* a, int sz, int target) {
    int l = 0, r = sz - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == target) return m;
        a[m] < target ? (l = m + 1) : (r = m - 1);
    }
    return -1;
}
// O(n) - Shift elements to maintain order
void ins_SA(int* a, int* sz, int val) {
    int i = *sz - 1;
    while (i >= 0 && a[i] > val) { a[i + 1] = a[i]; i--; }
    a[i + 1] = val; (*sz)++;
}
// O(n) - Shift left to cover gap
void del_SA(int* a, int* sz, int id) {
    for (int i = id; i < *sz - 1; i++) a[i] = a[i + 1];
    (*sz)--;
}
// O(1) - Access last
int max_SA(int* a, int sz) { return sz == 0 ? INT_MIN : a[sz - 1]; }
// O(1) - Access first
int min_SA(int* a, int sz) { return sz == 0 ? INT_MAX : a[0]; }
// O(1) - Immediate left
int pred_SA(int sz, int id) { return id <= 0 ? -1 : id - 1; }
// O(1) - Immediate right
int succ_SA(int sz, int id) { return id >= sz - 1 ? -1 : id + 1; }


// 3. SINGLY LINKED UNSORTED (SLU)

// O(n) - Sequential search
SNode* srch_SLU(SNode* h, int target) {
    while (h && h->data != target) h = h->nxt;
    return h;
}
// O(1) - Insert at head
void ins_SLU(SNode** h, int val) {
    SNode* n = (SNode*)malloc(sizeof(SNode));
    n->data = val; n->nxt = *h; *h = n;
}
// O(n) - Traverse to find predecessor
void del_SLU(SNode** h, SNode* target) {
    if (!*h || !target) return;
    if (*h == target) { *h = target->nxt; free(target); return; }
    SNode* curr = *h;
    while (curr->nxt && curr->nxt != target) curr = curr->nxt;
    if (curr->nxt == target) { curr->nxt = target->nxt; free(target); }
}
SNode* max_SLU(SNode* h) {
    SNode* m = h;
    while (h) { if (h->data > m->data) m = h; h = h->nxt; }
    return m;
}
SNode* min_SLU(SNode* h) {
    SNode* m = h;
    while (h) { if (h->data < m->data) m = h; h = h->nxt; }
    return m;
}
SNode* pred_SLU(SNode* h, SNode* target) {
    SNode* p = NULL; int m = INT_MIN;
    while (h) {
        if (h->data < target->data && h->data > m) { m = h->data; p = h; }
        h = h->nxt;
    }
    return p;
}
SNode* succ_SLU(SNode* h, SNode* target) {
    SNode* s = NULL; int m = INT_MAX;
    while (h) {
        if (h->data > target->data && h->data < m) { m = h->data; s = h; }
        h = h->nxt;
    }
    return s;
}


// 4. SINGLY LINKED SORTED (SLS)

// O(n) - Stop early if value exceeded
SNode* srch_SLS(SNode* h, int target) {
    while (h && h->data < target) h = h->nxt;
    return (h && h->data == target) ? h : NULL;
}
// O(n) - Find correct position
void ins_SLS(SNode** h, int val) {
    SNode* n = (SNode*)malloc(sizeof(SNode)); n->data = val;
    if (!*h || (*h)->data >= val) { n->nxt = *h; *h = n; return; }
    SNode* curr = *h;
    while (curr->nxt && curr->nxt->data < val) curr = curr->nxt;
    n->nxt = curr->nxt; curr->nxt = n;
}
// O(n) - Traverse to find predecessor
void del_SLS(SNode** h, SNode* target) { del_SLU(h, target); }
// O(n) - Traverse to end
SNode* max_SLS(SNode* h) {
    if (!h) return NULL;
    while (h->nxt) h = h->nxt;
    return h;
}
// O(1) - Minimum is at head
SNode* min_SLS(SNode* h) { return h; }
// O(n) - Traverse to find predecessor node
SNode* pred_SLS(SNode* h, SNode* target) {
    if (!h || h == target) return NULL;
    while (h && h->nxt != target) h = h->nxt;
    return h;
}
// O(1) - Immediate next
SNode* succ_SLS(SNode* target) { return target ? target->nxt : NULL; }


// 5. DOUBLY LINKED UNSORTED (DLU)

// O(n) - Sequential search
DNode* srch_DLU(DNode* h, int target) {
    while (h && h->data != target) h = h->nxt;
    return h;
}
// O(1) - Insert at head
void ins_DLU(DNode** h, int val) {
    DNode* n = (DNode*)malloc(sizeof(DNode));
    n->data = val; n->prv = NULL; n->nxt = *h;
    if (*h) (*h)->prv = n;
    *h = n;
}
// O(1) - Bypass pointers
void del_DLU(DNode** h, DNode* target) {
    if (!*h || !target) return;
    if (*h == target) *h = target->nxt;
    if (target->prv) target->prv->nxt = target->nxt;
    if (target->nxt) target->nxt->prv = target->prv;
    free(target);
}
DNode* max_DLU(DNode* h) {
    DNode* m = h;
    while (h) { if (h->data > m->data) m = h; h = h->nxt; }
    return m;
}
DNode* min_DLU(DNode* h) {
    DNode* m = h;
    while (h) { if (h->data < m->data) m = h; h = h->nxt; }
    return m;
}
DNode* pred_DLU(DNode* h, DNode* target) {
    DNode* p = NULL; int m = INT_MIN;
    while (h) {
        if (h->data < target->data && h->data > m) { m = h->data; p = h; }
        h = h->nxt;
    }
    return p;
}
DNode* succ_DLU(DNode* h, DNode* target) {
    DNode* s = NULL; int m = INT_MAX;
    while (h) {
        if (h->data > target->data && h->data < m) { m = h->data; s = h; }
        h = h->nxt;
    }
    return s;
}


// 6. DOUBLY LINKED SORTED (DLS)

// O(n) - Search with early exit
DNode* srch_DLS(DNode* h, int target) {
    while (h && h->data < target) h = h->nxt;
    return (h && h->data == target) ? h : NULL;
}
// O(n) - Find correct sorted position
void ins_DLS(DNode** h, DNode** tl, int val) {
    DNode* n = (DNode*)malloc(sizeof(DNode)); n->data = val;
    if (!*h) { n->prv = n->nxt = NULL; *h = *tl = n; return; }
    DNode* curr = *h;
    while (curr && curr->data < val) curr = curr->nxt;
    if (curr == *h) { n->nxt = *h; n->prv = NULL; (*h)->prv = n; *h = n; }
    else if (!curr) { n->prv = *tl; n->nxt = NULL; (*tl)->nxt = n; *tl = n; }
    else { n->nxt = curr; n->prv = curr->prv; curr->prv->nxt = n; curr->prv = n; }
}
// O(1) - Bypass pointers
void del_DLS(DNode** h, DNode** tl, DNode* target) {
    if (!*h || !target) return;
    if (*h == target) *h = target->nxt;
    if (*tl == target) *tl = target->prv;
    if (target->prv) target->prv->nxt = target->nxt;
    if (target->nxt) target->nxt->prv = target->prv;
    free(target);
}
// O(1) - Access via tail
DNode* max_DLS(DNode* tl) { return tl; }
// O(1) - Access via head
DNode* min_DLS(DNode* h) { return h; }
// O(1) - Use prev pointer
DNode* pred_DLS(DNode* target) { return target ? target->prv : NULL; }
// O(1) - Use next pointer
DNode* succ_DLS(DNode* target) { return target ? target->nxt : NULL; }

double get_time(clock_t s, clock_t e) {
    return ((double)(e - s)) / CLOCKS_PER_SEC;
}

int main() {
    srand((unsigned)time(NULL));
    int N_arr[] = {1000, 2000, 4000, 8000, 10000};
    
    FILE *f = fopen("q1_benchmark_data.csv", "w");
    if (!f) { printf("Failed to open file.\n"); return 1; }
    
    fprintf(f, "N,Data_Structure,Time_Insert,Time_Search,Time_Max,Time_Min,Time_Pred,Time_Succ,Time_Delete\n");
    printf("Running Benchmarks...\n");
    
    for (int test = 0; test < 5; test++) {
        int N = N_arr[test];
        int* vals = (int*)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) vals[i] = rand() % 500000;
        
        clock_t s, e; 
        double t_ins, t_src, t_max, t_min, t_prd, t_suc, t_del;
        
        // 1. UA
        int* ua = (int*)malloc(N * sizeof(int)); int sz_ua = 0;
        s=clock(); for(int i=0;i<N;i++) ins_UA(ua, &sz_ua, vals[i]); e=clock(); t_ins=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) srch_UA(ua, sz_ua, -1); e=clock(); t_src=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) max_UA(ua, sz_ua); e=clock(); t_max=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) min_UA(ua, sz_ua); e=clock(); t_min=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) pred_UA(ua, sz_ua, i); e=clock(); t_prd=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) succ_UA(ua, sz_ua, i); e=clock(); t_suc=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) del_UA(ua, &sz_ua, 0); e=clock(); t_del=get_time(s,e);
        fprintf(f, "%d,Unsorted_Array,%f,%f,%f,%f,%f,%f,%f\n", N, t_ins, t_src, t_max, t_min, t_prd, t_suc, t_del);
        free(ua);

        // 2. SA
        int* sa = (int*)malloc(N * sizeof(int)); int sz_sa = 0;
        s=clock(); for(int i=0;i<N;i++) ins_SA(sa, &sz_sa, vals[i]); e=clock(); t_ins=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) srch_SA(sa, sz_sa, -1); e=clock(); t_src=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) max_SA(sa, sz_sa); e=clock(); t_max=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) min_SA(sa, sz_sa); e=clock(); t_min=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) pred_SA(sz_sa, i); e=clock(); t_prd=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) succ_SA(sz_sa, i); e=clock(); t_suc=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) del_SA(sa, &sz_sa, 0); e=clock(); t_del=get_time(s,e);
        fprintf(f, "%d,Sorted_Array,%f,%f,%f,%f,%f,%f,%f\n", N, t_ins, t_src, t_max, t_min, t_prd, t_suc, t_del);
        free(sa);

        // 3. SLU
        SNode* slu = NULL; SNode* trk_u[10000];
        s=clock(); for(int i=0;i<N;i++) { ins_SLU(&slu, vals[i]); trk_u[i]=slu; } e=clock(); t_ins=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) srch_SLU(slu, -1); e=clock(); t_src=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) max_SLU(slu); e=clock(); t_max=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) min_SLU(slu); e=clock(); t_min=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) pred_SLU(slu, trk_u[i]); e=clock(); t_prd=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) succ_SLU(slu, trk_u[i]); e=clock(); t_suc=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) del_SLU(&slu, trk_u[i]); e=clock(); t_del=get_time(s,e);
        fprintf(f, "%d,SLL_Unsorted,%f,%f,%f,%f,%f,%f,%f\n", N, t_ins, t_src, t_max, t_min, t_prd, t_suc, t_del);

        // 4. SLS
        SNode* sls = NULL; SNode* trk_s[10000];
        s=clock(); for(int i=0;i<N;i++) ins_SLS(&sls, vals[i]); e=clock(); t_ins=get_time(s,e);
        SNode* c = sls; for(int i=0;i<N;i++) { trk_s[i]=c; c=c->nxt; }
        s=clock(); for(int i=0;i<N;i++) srch_SLS(sls, -1); e=clock(); t_src=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) max_SLS(sls); e=clock(); t_max=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) min_SLS(sls); e=clock(); t_min=get_time(s,e);
        s=clock(); for(int i=1;i<N;i++) pred_SLS(sls, trk_s[i]); e=clock(); t_prd=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) succ_SLS(trk_s[i]); e=clock(); t_suc=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) del_SLS(&sls, trk_s[N-1-i]); e=clock(); t_del=get_time(s,e);
        fprintf(f, "%d,SLL_Sorted,%f,%f,%f,%f,%f,%f,%f\n", N, t_ins, t_src, t_max, t_min, t_prd, t_suc, t_del);

        // 5. DLU
        DNode* dlu = NULL; DNode* dtrk_u[10000];
        s=clock(); for(int i=0;i<N;i++) { ins_DLU(&dlu, vals[i]); dtrk_u[i]=dlu; } e=clock(); t_ins=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) srch_DLU(dlu, -1); e=clock(); t_src=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) max_DLU(dlu); e=clock(); t_max=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) min_DLU(dlu); e=clock(); t_min=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) pred_DLU(dlu, dtrk_u[i]); e=clock(); t_prd=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) succ_DLU(dlu, dtrk_u[i]); e=clock(); t_suc=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) del_DLU(&dlu, dtrk_u[i]); e=clock(); t_del=get_time(s,e);
        fprintf(f, "%d,DLL_Unsorted,%f,%f,%f,%f,%f,%f,%f\n", N, t_ins, t_src, t_max, t_min, t_prd, t_suc, t_del);

        // 6. DLS
        DNode* dls_h = NULL; DNode* dls_t = NULL; DNode* dtrk_s[10000];
        s=clock(); for(int i=0;i<N;i++) ins_DLS(&dls_h, &dls_t, vals[i]); e=clock(); t_ins=get_time(s,e);
        DNode* dc = dls_h; for(int i=0;i<N;i++) { dtrk_s[i]=dc; dc=dc->nxt; }
        s=clock(); for(int i=0;i<N;i++) srch_DLS(dls_h, -1); e=clock(); t_src=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) max_DLS(dls_t); e=clock(); t_max=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) min_DLS(dls_h); e=clock(); t_min=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) pred_DLS(dtrk_s[i]); e=clock(); t_prd=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) succ_DLS(dtrk_s[i]); e=clock(); t_suc=get_time(s,e);
        s=clock(); for(int i=0;i<N;i++) del_DLS(&dls_h, &dls_t, dtrk_s[i]); e=clock(); t_del=get_time(s,e);
        fprintf(f, "%d,DLL_Sorted,%f,%f,%f,%f,%f,%f,%f\n", N, t_ins, t_src, t_max, t_min, t_prd, t_suc, t_del);

        free(vals);
    }
    
    fclose(f);
    printf("Done!\n");
    return 0;
}