import sys

N, M, L = map(int, sys.argv[1:])

print N*M, L

x = 200
y = 200

for i in range(N):
    for j in range(M):
        print " ".join(map(str, [x+2*i, y+2*j, x+2*i+1, y+2*j+1]))
