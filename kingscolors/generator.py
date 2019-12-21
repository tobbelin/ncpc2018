#!/usr/bin/env python3
import sys, argparse, random


parser = argparse.ArgumentParser(description="Generator for landoftrees.")
parser.add_argument('-o', metavar='O', type=str, default="random",
                    help='Options for generation (random, balanced, onepath, twopaths)')
parser.add_argument('-n', metavar='N', type=int, required=True,
                    help='size of graph - integer >=2 (required)')
parser.add_argument('-k', metavar='N', type=int, default=0,
                    help='number of children (<= n)')
parser.add_argument('-s', metavar='S', type=int, default=None,
                    help='seed for generation (optional)')
args = parser.parse_args()
random.seed(args.s)

options = args.o
n, k = args.n, args.k
if (n < 2):
    raise Exception("Can't have n < 2")
if (k < 2):
    k = random.randint(2, n)
if (k > n):
    raise Exception("Can't have k > n")

# Print main information
print(n, k)

# Various options
if (options == "random"):
    for i in range(n-1):
        print(random.randint(0, i))
        
elif (options == "balanced"):
    for i in range(1, n):
        print(i//2)

elif (options == "onepath"):
    for i in range(n-1):
        print(i)
        
elif (options == "twopaths"):
    print(0)
    print(0)
    for i in range(3, n):
        print(i-2)
        
else:
    raise Exception("Illegal option: '{}'".format(option))
