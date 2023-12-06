from collections import namedtuple
f = open("Des9/input.txt", "r")
lines = f.readlines()

def moveHead(point, dir):
    if(dir == "U"):
        point = Point(point.x, point.y + 1)
        return point
    if(dir == "D"):
        point = Point(point.x, point.y - 1)
        return point
    if(dir == "L"):
        point = Point(point.x - 1, point.y)
        return point
    if(dir == "R"):
        point = Point(point.x + 1, point.y)
        return point

def moveTail(h, t):
    tx = t.x
    ty = t.y
    if ( abs(h.x -t.x) < 2 and abs(h.y - t.y) < 2 ):
        return t
    
    if ( abs(h.x -t.x) >= 2):
        tx = t.x + (h.x - t.x)/abs(h.x -t.x)
        if ( abs(h.y -t.y) > 0):
            ty = t.y + (h.y - t.y)/abs(h.y -t.y)
    if ( abs(h.y -t.y) >= 2):
        ty = t.y + (h.y - t.y)/abs(h.y -t.y)
        if ( abs(h.x -t.x) > 0):
            tx = t.x + (h.x - t.x)/abs(h.x -t.x)
    
    return Point(tx, ty)

Point= namedtuple("Point", "x y")
def task1():
    s = set()
    T = Point(0,0)
    H = Point(0,0)
    for line in lines:
        input = line.split()
        dir = input[0]
        num = int(input[1])
        for i in range(num):
            H = moveHead(H, dir)
            T = moveTail(H, T)
            print(H, T)
            s.add(T)
    print("task 1: ", len(s))

def task2():
    s = set()
    rope = [Point(0,0) for i in range(10)]
    for line in lines:
        input = line.split()
        dir = input[0]
        num = int(input[1])
        for _ in range(num):
            rope[0] = moveHead(rope[0], dir)
            for i in range(1, len(rope)):
                rope[i] = moveTail(rope[i-1], rope[i])
            s.add(rope[-1])
    print("task 2: ", len(s))
task2()