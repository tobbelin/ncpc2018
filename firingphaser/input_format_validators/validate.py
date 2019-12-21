#!/usr/bin/env python3
from sys import stdin
import re, sys, itertools


integer = "(0|-?[1-9]\d*)"
n_int = lambda n : re.compile("^" + " ".join(n*[integer]) + "\n$")
two_int = n_int(2)
four_int = n_int(4)

class Point:

    def __init__(self, x, y):
        self.x, self.y = x, y

    def __repr__(self):
        return "(%r, %r)" % (self.x, self.y)

def generate_sides(room):
    X, Y = room[0:4:2], room[1:4:2]
    corners = [Point(x, y) for x, y in itertools.product(X, Y)]

    return ((corners[0], corners[1]),
            (corners[0], corners[2]),
            (corners[1], corners[3]),
            (corners[2], corners[3]))


def intersect(a, b):
    """
    Exploiting that all line segments are axes-parallell, since general line
    segment intersection is somewhat tedious.
    """

    # Parallell lines
    if a[0].y == a[1].y and b[0].y == b[1].y:
        a = (Point(a[0].y, a[0].x), Point(a[1].y, a[1].x))
        b = (Point(b[0].y, b[0].x), Point(b[1].y, b[1].x))

    if a[0].x == a[1].x and b[0].x == b[1].x:
        if a[0].x != b[0].x:
            return False

        return (a[0].y <= b[0].y <= a[1].y or
                a[0].y <= b[1].y <= a[1].y or
                b[0].y <= a[0].y <= b[1].y or
                b[0].y <= a[1].y <= b[1].y)

    # Non-parallell lines
    if b[0].x != b[1].x:
        a, b = b, a

    return a[0].x <= b[0].x <= a[1].x and b[0].y <= a[0].y <= b[1].y


# Check input
line = stdin.readline()
assert two_int.match(line)

R, L = map(int, line.split())
assert 1 <= R <= 15 and 1 <= L <= 10**6

rooms = []
for i in range(R):
    line = stdin.readline()
    assert four_int.match(line)

    xl, yl, xu, yu = map(int, line.split())
    assert 0 <= xl < xu <= 10**6
    assert 0 <= yl < yu <= 10**6

    rooms.append((xl, yl, xu, yu))

assert len(stdin.readline()) == 0

# Check that no two rooms overlap
for i in range(R):
    for k in range(i+1, R):
        si = generate_sides(rooms[i])
        sk = generate_sides(rooms[k])

        for a, b in itertools.product(si, sk):
            if intersect(a, b):
                print("Rooms %r and %r intersects" % (rooms[i], rooms[k]))
            assert not intersect(a, b)

sys.exit(42)
