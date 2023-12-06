f = open("Des22/input.txt", "r")
lines = f.readlines()
grid = []

from collections import namedtuple
Point= namedtuple("Point", "row col dir")

for line in lines[:-2]:
    l = line.replace('\n', '')
    grid.append(l)


instructions = lines[-1].strip()

startrow = 0
startcol = grid[0].find('.')

def getInstructArr(struct):
    ins = ''
    arr = []
    for i in range(len(struct)):
        if(not struct[i].isdigit()):
            if(len(ins) > 0):
                arr.append(int(ins))
                ins = ""
            arr.append(struct[i])
        else:
            ins = ins + struct[i]
    if(len(ins) > 0):
        arr.append(int(ins))
    return arr

# print(getInstructArr(instructions))

def getNextPos(currpos):
    if(currpos.dir == 0):
        newcol = currpos.col+1
        if(newcol >= len(grid[currpos.row]) or grid[currpos.row][newcol] == " "):
            newcol = 0
            for i in reversed(range(1, currpos.col)):
                if(grid[currpos.row][i-1] == " "):
                    newcol = i
                    break
            # return Point(currpos.row, newcol, currpos.dir)
        if(grid[currpos.row][newcol] == "#"):
            return currpos
        else:
            return Point(currpos.row, newcol, currpos.dir)
    elif(currpos.dir == 2):
        newcol = currpos.col-1
        if( newcol  < 0 or grid[currpos.row][newcol] == " "):
            newcol = len(grid[currpos.row]) - 1
            for i in range(currpos.col, len(grid[currpos.row]) - 1):
                if(grid[currpos.row][i+1] == " "):
                    newcol = i
                    break
        
        if(grid[currpos.row][newcol] == "#"):
            return currpos
        else:
            return Point(currpos.row, newcol, currpos.dir)
    elif(currpos.dir == 1):
        newrow = currpos.row + 1 
        if( newrow  >= len(grid) or currpos.col >= len(grid[newrow]) or grid[newrow][currpos.col] == " "):
            newrow = 0
            for i in reversed(range(1, currpos.row)):
                if(grid[i-1][currpos.col] == " "):
                    newrow = i
                    break
        
        if(grid[newrow][currpos.col] == "#"):
            return currpos
        else:
            return Point(newrow, currpos.col, currpos.dir)
    elif(currpos.dir == 3):
        newrow = currpos.row - 1 
        if( newrow  < 0 or grid[newrow][currpos.col] == " "):
            newrow = len(grid)-1
            for i in range(currpos.row, len(grid)-1):
                if(len(grid[i+1]) <= currpos.col or grid[i+1][currpos.col] == " "):
                    newrow = i
                    break
        
        if(grid[newrow][currpos.col] == "#"):
            return currpos
        else:
            return Point(newrow, currpos.col, currpos.dir)


def needsWrap(row, col):
    return row < 0 or  row  >= len(grid) or col < 0 or col >= len(grid[row]) or grid[row][col] == " "


def getNextPosCube(currpos):
    newcol = currpos.col
    newrow = currpos.row
    newdir = currpos.dir
    if(currpos.dir == 0):
        newcol = currpos.col+1
        if(needsWrap(newrow, newcol)):
            if 0 <= currpos.row < 50:
                newdir = 2
                newrow = 150 - 1 - currpos.row
                newcol = 99
            elif 50 <= currpos.row < 100:
                newdir = 3
                newrow = 49
                newcol = currpos.row + 50
            elif 100 <= currpos.row < 150:
                newdir = 2
                newrow = 49 - (currpos.row - 100)
                newcol = 149
            elif 150 <= currpos.row < 200:
                newdir = 3
                newrow = 149
                newcol = 50 + currpos.row -150

    elif(currpos.dir == 2):
        newcol = currpos.col-1
        if(needsWrap(newrow, newcol)):
            if 0 <= currpos.row < 50:
                newdir = 0
                newrow = 149 - currpos.row
                newcol = 0
            if 50  <= currpos.row < 100:
                newdir = 1
                newrow = 100
                newcol = currpos.row - 50
            if 100 <= currpos.row < 150:
                newdir = 0
                newrow = 149 - currpos.row
                newcol = 50
            if 150 <= currpos.row < 200:
                newdir = 1
                newrow = 0
                newcol = 50 + currpos.row - 150
    elif(currpos.dir == 1):
        newrow = currpos.row + 1 
        if(needsWrap(newrow, newcol)):
            if 0 <= currpos.col < 50:
                newdir = 1
                newrow = 0
                newcol = currpos.col + 100
            if 50  <= currpos.col < 100:
                newdir = 2
                newrow = currpos.col - 50 + 150
                newcol = 49
            if 100 <= currpos.col < 150:
                newdir = 2
                newrow = currpos.col - 100 + 50
                newcol = 99
    elif(currpos.dir == 3):
        newrow = currpos.row - 1 
        if(needsWrap(newrow, newcol)):
            if 0 <= currpos.col < 50:
                newdir = 0
                newrow = 50 + (currpos.col)
                newcol = 50
            elif 50 <= currpos.col < 100:
                newdir = 0
                newrow = currpos.col - 50 + 150
                newcol = 0
            elif 100 <= currpos.col < 150:
                newdir = 3
                newrow = 199
                newcol = currpos.col -100
    if(grid[newrow][newcol] == "#"):
        return currpos
    else:
        return Point(newrow, newcol, newdir)

def rotate(ins, point):
    if(ins == 'R'):
        return Point(point.row, point.col, (point.dir + 1)%4)
    elif(ins == 'L'):
        return Point(point.row, point.col, (point.dir - 1)%4)

def simulate(dir, startrow, startcol):
    pos = Point(startrow, startcol, dir)
    count = 0

    for ins in getInstructArr(instructions):
        # if count == 165:
            # break
        count += 1
        if(ins == 'R' or ins == 'L'):
            pos = rotate(ins, pos)
            # print(pos)
        else: 
            print(pos, ins)

            for i in range(ins):

                nextpos = getNextPosCube(pos)
                prevpos = pos
                pos = nextpos
                # print(prevpos, ins, pos)

                if(pos == prevpos):
                    # print("obstacle")
                    break
            # print(pos)
    print("score: ", (pos.row+1)*1000+(pos.col+1)*4+pos.dir)


simulate(0, startrow, startcol)