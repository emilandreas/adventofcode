f = open("Des7/input.txt", "r")
lines = f.readlines()

sizes = {}
def getDirContent(dirName, dirPath):
    currentPath = []
    dirlines = []
    for i in range(len(lines)):
        line = lines[i].strip()
        if(line[:4] == "$ cd"):
            name = line[4:].strip()
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
    return dirlines

def getDirScore(dirName, dirPath):
    dirlines = getDirContent(dirName, dirPath)
    size = 0
    for line in dirlines:
        if(line[:3].strip() == "dir"):
            n = line[3:].strip()
            relativePath = dirPath + [dirName]
            fullPathString = "/".join(relativePath + [n])
            if fullPathString in sizes:
                size += sizes[fullPathString]
            else: size += getDirScore(n, relativePath)
        else: 
            size += int(line.split(" ")[0])
    fullPathString = "/".join(dirPath + [dirName])
    sizes[fullPathString] = size
    return size


def getResult1_b():
    score = 0
    for (key, val) in sizes.items():
        if(val <= 100000):
            score += val
    return score

def getResult2():
    allSizes = list(map(lambda x: x[1], sizes.items()))
    allSizes.sort()
    for size in allSizes:
        if(70000000 - sizes["/"] + size > 30000000):
            return size



getDirScore("/", [])
print(getResult1_b())
print(getResult2())
