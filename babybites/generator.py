#!/usr/bin/env python3
import sys, argparse, random


parser = argparse.ArgumentParser(description="Generator for babybites.")
parser.add_argument('-o', metavar='O', type=str, default="random",
                    help='Options for generation (random, zeroindex, )')
parser.add_argument('-n', metavar='N', type=int, required=True,
                    help='size of graph - integer >=2 (required)')
parser.add_argument('-m', metavar='M', type=int, default=0,
                    help='number of mumbles')
parser.add_argument('-f', metavar='F', type=int, default=0,
                    help='number of flips')
parser.add_argument('-s', metavar='S', type=int, default=None,
                    help='seed for generation (optional)')
args = parser.parse_args()
random.seed(args.s)

n, mumbles, flips = args.n, args.m, args.f

if flips < 0 or mumbles < 0 or n < 1:
    raise Exception("Illegal arguments")
if (flips + mumbles > n):
    raise Exception("Can't have more errors and mumbles than bites")


### Print n
print(n)


### Generate numbers
nums = [i + (1 if args.o != "zeroindex" else 0) for i in range(n)]

### Determine positions to manipulate
manipos = random.sample(range(n), mumbles + flips)


for count, i in enumerate(manipos):
    if count < mumbles:
        nums[i] = "mumble"
    else:
        err = random.choice([1, -1])
        nums[i] += err
        
print(" ".join([str(x) for x in nums]))