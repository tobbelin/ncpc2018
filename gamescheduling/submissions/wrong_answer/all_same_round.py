import sys

# n participants in every team, m teams
n,m = map(lambda x:int(x), sys.stdin.readline().split(' '))

for t1 in range(m):
    for p1 in range(n):
        for t2 in range(m):
            for p2 in range(n):
                if t2 > t1:
                    sys.stdout.write("%c%d-%c%d " % (chr(t1 + ord('A')), p1 + 1, chr(t2 + ord('A')), p2 + 1))
print
