import sys
(n, s) = map(int, raw_input().split())
A = []
for (t, b) in sorted(map(lambda (t, b): (t, int(b)), [raw_input().split() for _ in range(n)]), key=lambda x: -x[1]):
    if b <= s:
        s -= b
        A.append(t)
if s: A = []
sys.stdout.write('%d\n%s' % (len(A), '\n'.join(A)))
