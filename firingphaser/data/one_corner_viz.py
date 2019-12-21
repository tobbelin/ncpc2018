from sys import stdin
import math
import numpy as np
import matplotlib.pyplot as plt


class Point:

    def __init__(self, x, y):
        self.x, self.y = x, y

    def __repr__(self):
        return "Point(%.11f, %.11f)" % (self.x, self.y)

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __div__(self, scalar):
        return Point(self.x/scalar, self.y/scalar)

    def dist(self, other):
        return math.sqrt((self.x-other.x)**2 + (self.y-other.y)**2)


def line_abc_form(a, b):
    A = b.y-a.y
    B = a.x-b.x
    C = A*a.x + B*a.y

    return A, B, C


def find_intersection(beam, wall):
    A1, B1, C1 = line_abc_form(*beam)
    A2, B2, C2 = line_abc_form(*wall)
    det = A1*B2 - A2*B1

    # Parallell
    if abs(det) < 10^-8:
        raise ValueError("Laser is parallell to wall1")

    x = (B2*C1 - B1*C2)/det
    y = (A1*C2 - A2*C1)/det
    return Point(x, y)


R, L = map(int, stdin.readline().split())
rooms = [map(int, stdin.readline().split()) for i in range(R)]

X_range = [x for room in rooms for x in room[0:4:2]]
Y_range = [y for room in rooms for y in room[1:4:2]]

plt.xlim([min(X_range)-1, max(X_range)+1])
plt.ylim([min(Y_range)-1, max(Y_range)+1])

for room in rooms:
    plt.plot([room[0], room[2], room[2], room[0], room[0]],
             [room[1], room[1], room[3], room[3], room[1]])

# Plot shortest laser
wall0 = (Point(rooms[0][2], rooms[0][1]), Point(rooms[0][2], rooms[0][3]))
wall1 = (Point(rooms[1][0], rooms[1][3]), Point(rooms[1][2], rooms[1][3]))
corner = Point(rooms[2][0], rooms[2][1])

start = Point(wall0[0].x, corner.y)
end = wall0[1]
while start.dist(end) > 0.00001:
    step = (end-start)/3.
    mid1 = start+step
    mid2 = mid1+step

    p1 = find_intersection((mid1, corner), wall1)
    d1 = p1.dist(mid1)

    p2 = find_intersection((mid2, corner), wall1)
    d2 = p2.dist(mid2)

    if d1 > d2:
        start = mid1
    else:
        end = mid2

q = (start+end)/2
p = find_intersection((q, corner), wall1)

laser_len = math.ceil(p.dist(q))
print("Laser length: %d" % laser_len)
plt.plot([p.x, q.x], [p.y, q.y], 'r-')

for start, end in [(Point(wall0[0].x, corner.y), q), (wall0[1], q)]:
    while start.dist(end) > 0.000001:
        mid = (start+end)/2
        p = find_intersection((mid, corner), wall1)
        d = p.dist(mid)

        if d <= laser_len:
            end = mid
        else:
            start = mid

    q = (start+end)/2
    p = find_intersection((q, corner), wall1)
    plt.plot([p.x, q.x], [p.y, q.y], 'r-')

plt.show()
