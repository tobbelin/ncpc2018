import sys
import random

random.seed(int(sys.argv[1]))

MAX_EDGES = 10**5

def random_tree(n):
    assert n >= 2
    seq = [ random.randint(0,n-1) for i in range(n-2) ]
    deg = [ 1 ]*n
    
    for u in seq:
        deg[u] += 1

    es = []
    for u in seq:
        for v in range(n):
            if deg[v] == 1:
                es.append((u,v))
                deg[u] -= 1
                deg[v] -= 1
                break

    zs = []
    for v in range(n):
        assert 0 <= deg[v] <= 1
        if deg[v] == 1:
            zs.append(v)
    assert len(zs) == 2
    es.append((zs[0], zs[1]))

    return es

def random_connected_graph(n, sparseness):
    es = set(random_tree(n))
    while len(es) < sparseness*n*(n-1)/2 and len(es) < MAX_EDGES and len(es) < n*(n-1)//2:
        u = random.randint(0,n-1)
        v = random.randint(0,n-1)
        if u != v and (u,v) not in es and (v,u) not in es:
            es.add((u,v))

    return list(es)

def shuffle_edges(es):
    res = []
    for i in range(len(es)):
        if random.randint(0,1) == 1:
            res.append((es[i][1], es[i][0]))
        else:
            res.append((es[i][0], es[i][1]))
    random.shuffle(res)
    return res

n = int(sys.argv[2])
sparseness = float(sys.argv[3])
max_weight = int(sys.argv[4])
qs = int(sys.argv[5])
max_time = int(sys.argv[6])

es = random_connected_graph(n, sparseness)
es = shuffle_edges(es)

sys.stdout.write('%d %d\n' % (n, len(es)))
for (u,v) in es:
    sys.stdout.write('%d %d %d\n' % (u+1, v+1, random.randint(0, max_weight)))

s = set()
while len(s) < qs: s.add(random.randint(0, max_time))
t = set()
while len(t) < qs: t.add(random.randint(0, max_time))

s = sorted(s)
t = sorted(t)

for i in range(qs):
    t[i] = max(t[i], s[i])

# while True:
#     ok = True
#     for i in range(qs-1):
#         if s[i] == s[i+1] or t[i] == t[i+1]:
#             ok = False
#             break
#     for i in range(qs):
#         if s[i] >= t[i]:
#             ok = False
#             break
#     if ok:
#         break

sys.stdout.write('%d\n' % qs)
for q in range(qs):
    sys.stdout.write('%d %d %d\n' % (s[q], random.randint(2,n), t[q]))

