import os
import random
import sys
import string

CASE = 1
DEST = os.path.join(os.path.dirname(__file__), 'secret')

def next_file(short_desc=None, long_desc=None):
    global CASE
    basename = os.path.join(DEST, '%02d' % CASE)
    CASE += 1
    if short_desc is not None:
        basename += '.' + short_desc
    if long_desc is not None:
        with open(basename+'.desc', 'w') as desc_out:
            desc_out.write(long_desc)
    return open(basename+'.in', 'w')

def save_case(ARR, S, short_desc=None, long_desc=None):
    sys.stderr.write('save_case sum %d in %s shortdesc %s\n' % (S, ARR, short_desc))
    f = next_file(short_desc, long_desc)
    f.write('%d %d\n' % (len(ARR), S))
    for (NAME, BET) in ARR:
        f.write('%s %d\n' % (NAME, BET))
    f.close()


MAX_N = 10**3
MAX_S = 10**1000 - 1

def random_superincreasing(max_start=10**8, max_jump=10**8, max_n=MAX_N, max_s=MAX_S):
    arr = [ random.randint(1, max_start) ]
    while arr[-1] <= max_s and len(arr) <= max_n:
        arr.append(arr[-1]*2 + random.randint(0, max_jump))
    return arr[:-1]

def random_superincreasing_ratio(max_start=10**8, max_ratio=5, max_n=MAX_N, max_s=MAX_S):
    arr = [ random.randint(1, max_start) ]
    while arr[-1] <= max_s and len(arr) <= max_n:
        arr.append(random.randint(2*arr[-1], max_ratio*arr[-1]))
    return arr[:-1]

def random_subset(arr, nonempty=False):
    subs = random.randint(1 if nonempty else 0, 2**len(arr)-1)
    res = []
    for i in range(len(arr)):
        if (subs & 1) != 0:
            res.append(arr[i])
        subs >>= 1
    return res

def random_name():
    return ''.join( random.choice(string.ascii_lowercase + string.ascii_uppercase) for _ in range(random.randint(10, 20)) )

def shuffled_with_random_names(bets):
    res = [ (random_name(), bet) for bet in bets ]
    random.shuffle(res)
    return res

def gen_random(gen):
    arr = gen()
    sm = sum(arr)
    save_case(shuffled_with_random_names(arr), random.randint(1, sm))

def gen_random_with_solution(gen):
    arr = gen()
    sol = random_subset(arr, nonempty=True)
    save_case(shuffled_with_random_names(arr), sum(sol))

def gen_random_with_full_solution():
    rem = s = MAX_S
    n = MAX_N
    bets = []
    for i in range(n-1):
        lo = 2*bets[-1] if i else 1
        hi = rem / (2**(n-i) - 1)
        bets.append(random.randint(lo, hi))
        rem -= bets[-1]
    assert rem >= 2*bets[-1]
    bets.append(rem)
    save_case(shuffled_with_random_names(bets), s, short_desc='full_solution')

def gen_random_with_singleton_solution():
    s = MAX_S
    n = MAX_N
    bets = []
    lo = 1
    for i in range(n-1):
        hi = s / (2**(n-i)-1)
        bets.append(random.randint(lo, hi))
        lo = 2*hi
    assert s >= 2*bets[-1]
    bets.append(s)
    save_case(shuffled_with_random_names(bets), s, short_desc='singleton_solution')


def main():
    random.seed(1337)

    # Cases that can be solved with complete search
    for i in range(3): gen_random_with_solution(lambda: random_superincreasing(max_n=10))
    for i in range(3): gen_random(lambda: random_superincreasing(max_n=10))

    # Cases that can be solved with meet-in-the-middle
    for i in range(3): gen_random_with_solution(lambda: random_superincreasing(max_n=30))
    for i in range(3): gen_random(lambda: random_superincreasing(max_n=30))

    # Cases that can be solved greedily
    for i in range(5): gen_random_with_solution(random_superincreasing)
    for i in range(5): gen_random_with_solution(random_superincreasing_ratio)
    for i in range(5): gen_random(random_superincreasing)
    for i in range(5): gen_random(random_superincreasing_ratio)

    # Case where solution is all n elements
    gen_random_with_full_solution()

    # Case where solution is a single element
    gen_random_with_singleton_solution()

if __name__=='__main__':
    main()
