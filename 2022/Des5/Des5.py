import re
f = open("Des5/input.txt", "r")

lines = f.readlines()
s = [[],[],[],[],[],[],[],[],[]]

lines1 = lines[:8]
lines2 = lines[10:]

# Build stacks
for line in lines1:
    for i in range(9):
        if(line[1+i*4]!=" "):
            s[i].append(line[1+i*4])
print(s)

def moveCrate(f, t):
    crate = s[f-1].pop(0)
    s[t-1].insert(0,crate)

def moveCrates1(f,t, num):
    for i in range(num):
        moveCrate(f,t)

def moveCrates2(f,t,num):
    crates = s[f-1][:num]
    s[f-1] = s[f-1][num:]
    s[t-1] = crates + s[t-1]

def getSolution():
    result = ""
    for stack in s:
        if(len(stack) >0):
            result = result + stack[0]
    return result
# Move stacks
for line in lines2:
    num, sFrom, sTo = map(int,re.match(r"move (\d+) from (\d+) to (\d+)", line).groups())
    moveCrates2(sFrom, sTo, num)

print("solution: ", getSolution())
