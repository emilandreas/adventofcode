import re

f = open("Des15/input.txt", "r")
lines = f.readlines()

points = []
beacons = []
from collections import namedtuple
Point= namedtuple("Point", "x y dist")

def getDist(x1, y1, x2, y2):
    diffx = abs(x1 - x2)
    diffy = abs(y1 - y2)
    return diffx + diffy

for line in lines:
    nums = re.findall(r'\d+', line)
    dist = getDist(int(nums[0]), int(nums[1]), int(nums[2]), int(nums[3]))
    points.append(Point(int(nums[0]), int(nums[1]), dist))
    beacons.append(Point(int(nums[2]),int(nums[3]), 0))

def isPossiblyBeacon(x, y):
    for p in points:
        if(getDist(x, y, p.x, p.y) <= p.dist): 
            return False
    return True

count = 0
for p in points:
    print("p: ", p)
    for i in range(-p.dist -1, p.dist + 1 + 1):
        j = p.dist + 1 - abs(i)
        x = p.x + i
        y = p.y + j
        if(0 <= x <= 4000000 and 0 <= y <= 4000000):
            if(isPossiblyBeacon(x, y)):
                print("freq: ", x*4000000 + y)
    for i in range(-p.dist -1, p.dist + 1 + 1):
        j = p.dist + 1 - abs(i)
        x = p.x + i
        y = p.y - j
        if(0 <= x <= 4000000 and 0 <= y <= 4000000):
            if(isPossiblyBeacon(x, y)):
                print("x, y:", x, y)
                print("freq: ", x*4000000 + y)
            
        



#Del 1
# if(getDist(x, y, p.x, p.y) <= p.dist): 
#                 isBeacon = False
#                 for b in beacons:
#                     if(x == b.x and y == b.y):
#                         isBeacon = True
#                         break
#                 if(not isBeacon):
#                     count += 1 
#                     break


# 4303923  

