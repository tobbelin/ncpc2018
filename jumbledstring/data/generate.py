from os import system
from random import randint, seed

counter = 0

def add_test(a,b,c,d,s):
	global counter
	counter += 1
	file_name = "{:03d}".format(counter)
	f = open("secret/" + file_name + ".in", "w")
	f.write("{} {} {} {}\n".format(a,b,c,d))
	f.close()
	f = open("secret/" + file_name + ".ans", "w")
	f.write(s + "\n")
	f.close()
	print("test {} added".format(file_name))

def add_possible(s):
	c00 = c01 = c10 = c11 = 0
	c0 = c1 = 0
	for x in s:
		if x == "0":
			c00 += c0
			c10 += c1
			c0 += 1
		else:
			c01 += c0
			c11 += c1
			c1 += 1
	add_test(c00,c01,c10,c11,s)

def add_impossible(c00,c01,c10,c11):
	add_test(c00,c01,c10,c11,"impossible")

add_possible("0")
add_possible("00")
add_possible("01")
add_possible("10")
add_possible("11")
add_possible("000")
add_possible("001")
add_possible("010")
add_possible("011")
add_possible("100")
add_possible("101")
add_possible("110")
add_possible("111")

add_possible("0"*44720)
add_possible("0"*44721)
add_possible("1"*44720)
add_possible("1"*44721)

seed(1337)
r = 10**9
for p in range(10,100,10):
	s = ""
	c00 = c01 = c10 = c11 = 0
	c0 = c1 = 0
	while True:
		if randint(0,99) < p:
			s += "0"
			c00 += c0
			c10 += c1
			c0 += 1
		else:
			s += "1"
			c01 += c0
			c11 += c1
			c1 += 1
		if max(c00,c01,c10,c11) > r:
			break
		u = s
	add_possible(u)

add_impossible(0,1,1,0)
add_impossible(1,1,1,1)
add_impossible(2,0,0,0)
add_impossible(0,2,0,0)
add_impossible(0,0,2,0)
add_impossible(0,0,0,2)
add_impossible(r,r,r,r)
