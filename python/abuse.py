#!/usr/bin/python

from resophonic import kamasu
import sys

n = 10

arr = kamasu.array(n)

for i in range(n):
    print arr[i]

for i in range(n):
    arr[i] = i * 0.5;

for i in range(n):
    print arr[i]

    
arr = kamasu.array(n,n)

for i in range(n):
    for j in range(n):
        arr[i,j] = i*n + j;

for i in range(n):
    for j in range(n):
        assert arr[i,j] == i*n + j

subarr = arr[1:n-1, 1:n-1]

for i in range(n-2):
    for j in range(n-2):
        print i, j, "is", subarr[i,j]
        assert subarr[i,j] == (i+1) * n + j+1

revarr = arr[::-1,::-1]

print revarr[0,0]
print revarr[9,9]
