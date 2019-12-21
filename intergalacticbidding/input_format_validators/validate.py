import sys
import re

line = sys.stdin.readline()
assert re.match('^[1-9][0-9]* [1-9][0-9]*\n$', line)
n, s = map(int, line.strip().split())

assert 1 <= n <= 10**3
assert 1 <= s <  10**1000

seen = set()
bets = []
for i in range(n):
    line = sys.stdin.readline()
    assert re.match('^[A-Za-z]{1,20} [1-9][0-9]*\n$', line)
    name, b = line.strip().split()
    b = int(b)

    assert 1 <= b < 10**1000
    assert name not in seen

    seen.add(name)
    bets.append(b)

bets = sorted(bets)
for (x,y) in zip(bets, bets[1:]):
    assert 2*x <= y

assert sys.stdin.read() == ''
sys.exit(42)

