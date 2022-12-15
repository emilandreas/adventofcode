f = open("Des10/input.txt", "r")
lines = f.readlines()
c = 0
x = 1


sum1 = 0
drawing = ""
def incrementCycleTask1():
    global c
    global sum1
    c += 1
    if(c == 20 or (c-20)%40 == 0):
        sum1 += c*x
    return c

def incrementCycleTask2():
    global c
    global x
    global drawing
    c += 1
    if((c-1)%40 >= x-1 and (c-1)%40 <= x+1):
        drawing += "#"
    else: drawing += "."


for line in lines:
    incrementCycleTask2()
    op = line.split()
    if(op[0] == "noop"):
        continue
    else:
        incrementCycleTask2()
        x += int(op[1])

def printDrawing():
    i = 40
    while(i < len(drawing)+1):
        print(drawing[i-40:i])
        i += 40


printDrawing()