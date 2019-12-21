# This solution just simulates one cut and doens't take into account the week after
import sys
import math

size, n = map(lambda x:int(x), sys.stdin.readline().split(' '))
cheapest = 1e9
candidates = []
for i in range(n):
    line = sys.stdin.readline().split(',')
    (price,capacity,cutting_time,recharge_time) = map(lambda x:int(x), line[1:])

    left = size
    minutes = 0
    batteries = cutting_time
    while left > 0 and minutes <= 10080:
        if batteries == 0:
            batteries = cutting_time
            minutes += recharge_time
        left -= capacity
        minutes += 1
        batteries -= 1

    if left <= 0 and minutes <= 10080:
        if price < cheapest:
            cheapest = price
            candidates = [line[0]]
        elif price == cheapest:
            candidates.append(line[0])

for c in candidates:
    print(c)
if len(candidates) == 0:
    print('no such mower')
