import re
f = open("Des7/input.txt", "r")

lines = f.readlines()

sizes = {}

def getDirLines(dirName, dirPath):
    print("current search path: ", dirPath)
    currentPath = []
    dirlines = []
    for i in range(len(lines)):
        line = lines[i].strip()
        if(line[:4] == "$ cd"):
            name = line[4:].strip()
            print("compare: ", dirPath, currentPath, dirPath == currentPath, "name: ", dirName, name)
            if(name == dirName and dirPath == currentPath):
                j=0
                while(i+2+j < len(lines) and lines[i+2+j][0] != '$' ):
                    dirlines.append(lines[i+2+j].strip())
                    j += 1
                return dirlines
            if(name == ".."):
                currentPath = currentPath [:-1]
            else:
                currentPath.append(name)
            print("currentPath", currentPath)
    return dirlines

na = []
nb = []

for line in lines:
    if(line[:4] == "$ cd"):
        name = line[4:].strip()
        if(name != ".."):
            na.append(name)

def getDirScore(dirName, dirPath):
    if(dirName == "qsgv"):
        print('a')
    dirlines = getDirLines(dirName, dirPath)
    size = 0
    for line in dirlines:
        if(line[:3].strip() == "dir"):
            n = line[3:].strip()
            relativePath = dirPath + [dirName]
            fullPath = relativePath + [n]
            print("fullpath: ", fullPath, "/".join(fullPath))
            if "/".join(fullPath) in sizes:
                size += sizes["/".join(fullPath)]
            else: size += getDirScore(n, relativePath)
        else: 
            size += int(line.split(" ")[0])
    fullPath = dirPath + [dirName]
    fullPathString = "/".join(fullPath)
    sizes[fullPathString] = size
    nb.append(dirName)
    return size

# for dirName in set(na):
#     getDirScore(dirName)

def getResult1_b():
    score = 0
    for (key, val) in sizes.items():
        if(val <= 100000):
            score += val
    return score

def getResult2():
    maxSize = 70000000
    currSize = sizes["/"]
    freeSizeNeeded = 30000000
    task2Sizes = []
    for (key, val) in sizes.items():
        task2Sizes.append(val)
    task2Sizes.sort()
    for size in task2Sizes:
        if(maxSize - currSize + size > freeSizeNeeded):
            return size



print(getDirScore("/", []))
print(getResult1_b())
print(getResult2())


# print(na)
# print(nb)

# print("na: ", len(na), len(set(na)))
# print("nb: ", len(nb), len(set(nb)))
# opposite = set(na).difference(set(nb))
# oppositeb = set(nb).difference(set(na))
# print(oppositeb)
# for o in opposite:
#     print(o)
# print(sizes)