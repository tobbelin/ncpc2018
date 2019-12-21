#!/usr/bin/python

import random
import os

random.seed(4711)



__location__ = os.path.realpath(
    os.path.join(os.getcwd(), os.path.dirname(__file__)))

def get_file(name):
    return open(os.path.join(__location__, name), "w")

#generate worst case for simulation
f = get_file('a-slow-simulation.in')
f.write("5040 100\n")
for i in range(0, 100):
    f.write("Mower %d,1,1,1,1\n"%(100-i))
f.close()

#generate random cases
for i in range(0, 10):
    f = get_file('random-%d.in'%i)
    f.write('%d 100\n'%(random.randint(1, 100000)))
    for d in range(0,100):
        f.write("Mower %d,%d,%d,%d,%d\n"%(100-d, random.randint(1, 100000), random.randint(1,100), random.randint(1,10080), random.randint(1,10080)))
    f.close()

for i in range(0, 10):
    f = get_file('random-fixed-price-%d.in'%i)
    f.write('%d 100\n'%(random.randint(1, 100000)))
    for d in range(0,100):
        f.write("Mower %d,%d,%d,%d,%d\n"%(100-d, 1000, random.randint(1,100), random.randint(1,10080), random.randint(1,10080)))
    f.close()
