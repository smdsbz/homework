#include <stdio.h>
#include <stdlib.h>

/*  homework/data_structrue/k_fib_1_17.c
 *      C implementation of ./k_fib_1_17.py
 */

    /**** set FibCache data structure ****/
typedef struct _FibCache {
    unsigned    _max_size;  // i.e. k
    unsigned    _cursor;    // waiting to be over-writen
    unsigned long *_cache;  // actual cache
} FibCache;

    /**** FibCache functions ****/

FibCache *FibCache_init(unsigned k);
/*  constructor of FibCache
 *  @param:     unsigned    k - the order of Fibonacci Seq.
 *  @return:    FibCache   *h - pointer to the instance created
 */

void FibCache_reset(FibCache *self);
/*  resets the FibCache inst.
 *  @param:     FibCache   *self  - object pointer
 *  @return:    ---
 */

void FibCache_append(FibCache *self, unsigned long val);
/*  append new Fib. number to the LOGICAL end of the cache
 *  @param:     FibCache       *self  - object pointer
 *              unsigned long   val   - Fib. num
 */

unsigned long FibCache_reduce_sum(FibCache *self);
/*  sum up everything in cache
 *  @param:     FibCache       *self  - object pointer
 *  @return:    unsigned long   rst   - next Fib. num
 */

unsigned long FibCache_run(FibCache *self, unsigned m);
/*  starts the session, gives the result
 *  @param:     FibCache       *self  - cache object pointer
 *              unsigned        m     - index of target Fib. num
 *  @return:    unsigned long   rst   - target Fib. num
 */

    /**** function realizations ****/
FibCache *FibCache_init(unsigned k) {
    // alloc for result
    FibCache *h = (FibCache *)malloc(sizeof(FibCache));
    if (!h) { return NULL; }
    h->_max_size = k;    // set k
    h->_cursor = 0;      // initialization
    h->_cache = (unsigned long *)malloc(k*sizeof(unsigned long));
    if (!h->_cache) { return NULL; }
    // init _cache to all 0s
    unsigned k_bak = 0;
    for (; k_bak < k-1; k_bak++) {
        h->_cache[k_bak] = 0;
    }
    h->_cache[k_bak] = 1;
    return h;
}

void FibCache_reset(FibCache *self) {
    unsigned k_bak = self->_max_size - 1;
    self->_cache[k_bak--] = 1;
    for (; k_bak; k_bak--) {
        self->_cache[k_bak] = 0;
    }
    *(self->_cache) = 0;
    self->_cursor = 0;
    return;
}

void FibCache_append(FibCache *self, unsigned long val) {
    self->_cache[(self->_cursor++) % self->_max_size] = val;
    return;
}

unsigned long FibCache_reduce_sum(FibCache *self) {
    unsigned long rst = 0;
    unsigned k_bak = 0;
    for (; k_bak < self->_max_size; k_bak++) {
        rst = rst + self->_cache[k_bak];
    }
    return rst;
}

unsigned long FibCache_run(FibCache *self, unsigned m) {
    if (self->_cursor) { FibCache_reset(self); }
    if (m < self->_max_size-1) { return 0; }
    if (m == self->_max_size-1) { return 1; }
    unsigned m_bak = self->_max_size;
    for (; m_bak < m; m_bak++) {
        FibCache_append(self, FibCache_reduce_sum(self));
    }
    return FibCache_reduce_sum(self);
}

void main(void) {
    unsigned k, m;
    printf("k="); scanf("%u", &k);
    printf("m="); scanf("%u", &m);
    FibCache *h = FibCache_init(k);
    printf("%lu\n", FibCache_run(h, m));
    return;
}
