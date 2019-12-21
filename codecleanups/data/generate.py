import os
import random
import sys

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

def save_case(p, P, short_desc=None, long_desc=None):
    with next_file(short_desc, long_desc) as out:
        out.write('%d\n' % p)
        out.write('%s\n' % " ".join(map(str, sorted(P))))

def main():
    random.seed(11235813)

    save_case(1, [1], 'first_day')
    save_case(1, [365], 'last_day')
    save_case(1, [345], 'day_345')
    save_case(1, [346], 'day_346')
    save_case(2, [19, 38], '19_between')
    save_case(2, [20, 40], '20_between')

    P = range(1, 366)
    for p in sorted([random.choice(P) for _ in range(20)]):
        random.shuffle(P)
        save_case(p, P[:p], 'random_%d' % p)

    save_case(365, P, 'every_day')

if __name__=='__main__':
    main()


