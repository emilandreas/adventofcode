import re
f = open("Des4/input.txt", "r")
lines = list(map(lambda line: list(map(int,re.split(",|-",line.strip()))), f.readlines()))

def encloses(x):
    return  x[0] <= x[2] and x[1] >= x[3] or x[2] <= x[0] and x[3] >= x[1]
def overlaps(x):
    return max(x[0], x[2]) <= min(x[1],x[3])

print(len(list(filter(encloses, lines))))
print(len(list(filter(overlaps, lines))))