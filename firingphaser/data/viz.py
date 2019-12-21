from sys import stdin
import numpy as np
import matplotlib.pyplot as plt

R, L = map(int, stdin.readline().split())
rooms = [map(int, stdin.readline().split()) for i in range(R)]

X_range = [x for room in rooms for x in room[0:4:2]]
Y_range = [y for room in rooms for y in room[1:4:2]]

plt.xlim([min(X_range)-1, max(X_range)+1])
plt.ylim([min(Y_range)-1, max(Y_range)+1])

for room in rooms:
    plt.plot([room[0], room[2], room[2], room[0], room[0]],
             [room[1], room[1], room[3], room[3], room[1]])

plt.show()
