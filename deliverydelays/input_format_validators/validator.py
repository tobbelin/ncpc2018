import sys
import re

line = sys.stdin.readline()
assert re.match('^[1-9][0-9]* [1-9][0-9]*\n$', line)
n, m = map(int, line.strip().split())
assert 2 <= n <= 1000
assert 1 <= m <= 5000

found = set()
G = { u: [] for u in range(1,n+1) }
for i in range(m):
    line = sys.stdin.readline()
    assert re.match('^[1-9][0-9]* [1-9][0-9]* (0|[1-9][0-9]*)\n$', line)
    u, v, d = map(int, line.strip().split())
    assert 1 <= u <= n
    assert 1 <= v <= n
    assert 0 <= d <= 10**8

    assert u != v
    assert (u,v) not in found and (v,u) not in found
    found.add((u,v))

    G[u].append((v,d))
    G[v].append((u,d))

line = sys.stdin.readline()
assert re.match('^(0|[1-9][0-9]*)\n$', line)
k = int(line.strip())
assert 1 <= k <= 1000

last_s = -1
last_t = -1
for i in range(k):
    line = sys.stdin.readline()
    assert re.match('^(0|[1-9][0-9]*) [1-9][0-9]* (0|[1-9][0-9]*)\n$', line)
    s, u, t = map(int, line.strip().split())
    assert 2 <= u <= n
    assert 0 <= s <= t <= 10**8

    assert last_s < s
    assert last_t < t
    last_s = s
    last_t = t

vis = { i: False for i in range(1,n+1) }
vis[1] = True
S = [1]
while S:
    x = S.pop()
    for (y, d) in G[x]:
        if not vis[y]:
            vis[y] = True
            S.append(y)

for i in range(1,n+1):
    assert vis[i]

assert not sys.stdin.read()
sys.exit(42)

