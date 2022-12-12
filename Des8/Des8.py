f = open("Des8/input.txt", "r")
lines = f.readlines()
grid = []
for line in lines:
    grid.append(line.strip())

def isLower(arr, height):
    for elem in arr:
        if (int(elem) >= int(height)):
            return False
    return True

def isVisible(grid, i, j):
    height = grid[i][j]
    if(i == 0 or j== 0 or i == len(grid) -1 or j == len(grid[i]) -1 ):
        return True
    # if( isLower(grid[:i][j], height) or isLower(grid[i+1:][j], height) or isLower(grid[i][:j], height) or isLower(grid[i][j+1:], height)):
        # return True
    # print(i, j)
    # print(grid[:i][0])
    return isLower(getCol(grid[:i],j), height) or isLower(getCol(grid[i+1:],j), height) or isLower(grid[i][:j], height) or isLower(grid[i][j+1:], height)

def countVisible(arr, height):
    sum = 0
    # print("arr", arr)
    for elem in arr:
        if(int(elem) >= int(height)):
            return sum+1
        sum += 1
    return sum

def findVisible(grid, i, j):
    height = grid[i][j]
    
    # if( isLower(grid[:i][j], height) or isLower(grid[i+1:][j], height) or isLower(grid[i][:j], height) or isLower(grid[i][j+1:], height)):
        # return True
    # print(i, j)
    # print(grid[:i][0])
    up = countVisible(getCol(grid[:i],j)[::-1], height)
    down = countVisible(getCol(grid[i+1:],j), height)
    left = countVisible(grid[i][:j][::-1], height)
    right = countVisible(grid[i][j+1:], height)
    return up * down * left * right  #countVisible(getCol(grid[:i],j)[::-1], height) * countVisible(getCol(grid[i+1:],j), height) * countVisible(grid[i][:j][::-1], height) or countVisible(grid[i][j+1:], height)




def getCol(arr, j):
    ret = []
    for line in arr:
        ret.append(line[j])
    return ret


    # return sum(map(int, filter(lambda x: int(x)>=height, arr)) ) == 0

sum = 0
for i in range(len(grid)):
    for j in range(len(grid[i])):
        height = grid[i][j]
        # print(i, j, len(grid), len(grid[i]))
        if(isVisible(grid, i, j)): sum += 1
maxsum = 0
for i in range(len(grid)):
    for j in range(len(grid[i])):
        height = grid[i][j]
        # print(i, j, len(grid), len(grid[i]))
        newSum = findVisible(grid, i, j)
        if(newSum > maxsum):
            
            maxsum = newSum
        



print("sum: ", sum)        
print("maxsum: ", maxsum)        


arr = ['1', 2, '3']
print(arr[:1], arr[1:])
print(isLower(arr, 3))
print(isLower(arr, 4))