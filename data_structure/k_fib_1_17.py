#!/usr/bin/env python3

'''
homework/data_structure/1_17_k_fib.py
    count the $(m)th $(k)-Fibonacci number
    with time complexity of O(n)
'''

class FibCache:
    '''
    Acts like heap?
        Make sure you DON'T re-use the instance!
    '''
    
    def __init__(self, k):
        ''' initialize FibCache instance '''
        self._max_size = k  # pop size
        self._cursor = 0    # get order
        self._cache = []    # actual cache
        # allocate cache space
        for _ in range(k-1):
            self._cache.append(0)
        self._cache.append(1)

    def _reset(self):
        '''
        init _cache to all 0s
            NOTE: FibCache can be reused
        '''
        # reset cache
        for i in range(self._max_size-1):
            self._cache[i] = 0
        self._cache[-1] = 1
        # reset cursor
        self._cursor = 0

    def append(self, val):
        '''
        append to LOGICAL tail of cache
            depricate useless fibonacci value automatically
        '''
        self._cache[self._cursor % self._max_size] = val
        self._cursor += 1
    
    def _reduce_sum(self):
        '''
        a fancier way of saying -
            SUM from fib_k(n-1) to fib_k(n-k)
        '''
        return sum(self._cache)

    def run(self, tgt):
        ''' starts the calculation session, gives you the result '''
        if self._cursor: self._reset() # if not first run -> clean-up
        if tgt < self._max_size-1:
            return 0
        if tgt == self._max_size-1:
            return 1
        for _ in range(self._max_size, tgt):
            self.append(self._reduce_sum())
        return self._reduce_sum()

# the moment of TRUTH!
if __name__ == '__main__':
    k = int(input('k = '))
    m = int(input('m = '))
    print(FibCache(k).run(m))

