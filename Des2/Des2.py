import pandas as pd

f = open("Des2-input.txt", "r")

df = pd.read_fwf("Des2-input.txt", header=None)

def getHandScore(them, you):
    return ord("X") - ord("A") -(ord(you) - ord(them))

print(df[1])
print(len(df))

# for(i in range(df.col)):
#     for i in range(df)

def getShapeScore(shape):
    return ord(shape)-ord("X") + 1
def isTie(them, you):
    return getHandScore(them, you) == 0
def isWin(them, you):
    return getHandScore(them, you) == -1 or getHandScore(them,you) == 2


def getRoundScore(them, you):
    if(isTie(them, you)):
        return 3 + getShapeScore(you)
    if(isWin(them, you)):
        return 6 + getShapeScore(you)
    else:
        return 0 + getShapeScore(you)

def getYou(them, result):
    if(result == "Y"):
        return chr(ord(them) + ord("X") - ord("A"))
    if(result == "X"):
        if(them == "A"):
            return "Z"
        if(them == "B"):
            return "X"
        if(them == "C"):
            return "Y"
    if(result == "Z"):
        if(them == "A"):
            return "Y"
        if(them == "B"):
            return "Z"
        if(them == "C"):
            return "X"

# totalscore = 0
# for i in range(len(df)):
#     them = df[0][i]
#     you = df[1][i]
#     score = getRoundScore(them, you)
#     print(them, you, score)
#     totalscore += score

# print(totalscore)

totalscore2 = 0
for i in range(len(df)):
    them = df[0][i]
    result = df[1][i]
    you = getYou(them, result)
    score = getRoundScore(them, you)
    print(them, result, you, score)
    totalscore2 += score
print(totalscore2)

