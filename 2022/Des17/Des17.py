f = open("Des17/input.txt", "r")
lines = f.readlines()

rocks = [
    [[0,3]],
    [[1,1],[0,2],[1,1]],
    [[2,2],[2,2],[0,2]],
    [[0,0],[0,0],[0,0],[0,0]],
    [[0,1],[0,1]]
]
print(lines)

shaft = ['.......' for i in range(7)]
print(shaft)
def printShaft(shaft):
    for i in reversed(range(len(shaft))):
        print(shaft[i])
def simulate():
    return

def findHighestRockHeight(shaft):
    for i in reversed(range(len(shaft))):
        if "#" in shaft[i]:
            return i+1
    return 0

def placeRock(x, y, rock, shaft):
    for i in range(rock):
        rockLayer = rock[i]
        for j in range(rockLayer[0], rockLayer[1]+1):
            shaft[x+i][j] = '@'

def placeStartingRock(rock, shaft):
    bedrockHeight = findHighestRockHeight(shaft) + 3
    rockHeight = len(rock)
    if (len(shaft) < bedrockHeight + 4 + rockHeight):
        shaft.extend(['.......' for i in range(10)])
    placeRock(rockHeight + bedrockHeight + 4, 2, rock, shaft)
    printShaft(shaft)
    

# shaft[0] = "..1111."
# printShaft(shaft)
placeStartingRock()