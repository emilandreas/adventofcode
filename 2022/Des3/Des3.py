f = open("Des3/input.txt", "r")

def getItemValue(item):
    if(ord(item) >= ord('a')):
        return ord(item) - ord('a')+1
    return ord(item) - ord('A')+27

def getScore():
    score = 0
    for line in f.readlines():
        for i in range(len(line)//2):
            if (line[i] in line[len(line)//2:]):
                score += getItemValue(line[i])
                break
    return score
    
def getScore2():
    lines = f.readlines()
    score = 0
    for i in range(len(lines)//3):
        for l in lines[i*3]:
            if (l in lines[i*3 + 1] and l in lines[i*3 + 2]):
                score += getItemValue(l)
                break
    return score

# print(getScore())mmmmmmmmmmiidm
print(getScore2())
