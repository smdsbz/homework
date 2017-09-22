#!/usr/bin/env python3

class FibCache:
    '''
    Acts like heap?
        Make sure you DON'T re-use the instance!
    '''
    
    def __init__(self, k):
        self._max_size = k  # pop size
        self._cursor = 0    # get order
        self._cache = []    # actual cache
        # init self._cache - al zeros
        for _ in range(k):
            self._cache.append(0)
        self._cache[-1] = 1
    
    def append(self, val):
        self._cache[self._cursor % self._max_size] = val
        self._cursor += 1
    
    def _reduce_sum(self):
        return sum(self._cache)

    def run(self, tgt):
        '''
        Run the session, gives you the result
        '''
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

