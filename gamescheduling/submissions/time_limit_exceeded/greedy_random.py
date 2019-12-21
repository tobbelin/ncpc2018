import random

def format(i):
    return '%s%d' % (chr(65+i/n), i%n + 1)

def make_schedule(n, m):
    p = n*m
    G = [[] for _ in range(p)]
    for i in range(p):
        for j in range(n*(i/n+1), p):
            G[i].append(j)
            G[j].append(i)
            
    schedule = []
    may_skip = [True]*p
    players = range(p)
    remaining = m*(m-1)/2*n*n

    def make_day():
        day = []
        taken = [False]*p
        deg = [len(G[i]) for i in range(p)]
        for _ in range(p/2):
            a = -1
            random.shuffle(players)
            for i in players:
                if not taken[i] and (a == -1 or (may_skip[i], deg[i]) < (may_skip[a], deg[a])):
                    a = i
            assert a != -1
            b = -1
            random.shuffle(G[a])
            for i in G[a]:
                if not taken[i] and (b == -1 or deg[i] < deg[b]):
                    b = i
            if b == -1:
                if not may_skip[b]: return []
                continue
#            if b == -1: return None
            taken[a] = taken[b] = True
            day.append((a, b))
            for i in G[a]:
                deg[i] -= 1
            for i in G[b]:
                deg[i] -= 1
        return day
    
#    print 'attempt gen'
    for _ in range(n*(m-1)+1):
        day = make_day()
        if not day: return None

        schedule.append(day)
        remaining -= len(day)
        if not remaining: return schedule

        used = set()
        for (a, b) in day:
            used.add(a)
            used.add(b)
            G[a].remove(b)
            G[b].remove(a)
        for i in range(p):
            may_skip[i] &= i in used

(n, m) = map(int, raw_input().split())
iters = 0
while True:
    schedule = make_schedule(n, m)
    iters += 1
    if schedule: break

import sys
sys.stderr.write('%d iters\n' % (iters))

for S in schedule:
    print ' '.join('%s-%s' % (format(a), format(b)) for (a, b) in S)
