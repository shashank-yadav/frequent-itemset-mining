import random
import sys

with open('retail.dat') as f:
    lines = f.readlines()

k = int((float(sys.argv[1])/100)*len(lines))
print k

lines_n = random.sample(lines, k)

fout = open('data'+sys.argv[1], 'w')
for x in lines_n:
	fout.write(x)
