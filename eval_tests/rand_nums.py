from random import sample
from sys import argv

if len(argv) != 4:
    exit()

start, end, nums = [int(n) for n in argv[1:]]
print(*sample(range(start,end+1), nums), sep=' ', end='')