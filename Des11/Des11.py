f = open("Des11/input2.txt", "r")
lines = f.readlines()

monkies = []
for j in range((len(lines) + 1)//7):
    i = j*7
    monkeyNum = int(lines[i][7])
    items = list(map(int, lines[i+1].split("Starting items:")[1].split(',')))
    operation = lines[i+2].split("Operation: new = old")[1].strip()
    test = int(lines[i+3].split("Test: divisible by")[1].strip())
    true = int(lines[i+4].strip()[-1])
    false = int(lines[i+5].strip()[-1])
    monkies.append([monkeyNum, items, operation,test,true,false])

def doOperation(op, num):
    symbol = op.split()[0]
    multiplier = op.split()[1].strip()
    if(multiplier == "old"):
        multiplier = num
    multiplier = int(multiplier)
    if(symbol == "+"):
        return num + multiplier
    elif(symbol == "*"):
        return num * multiplier

inspect = [0 for i in range(8)]
def playRound():
    for i in range(len(monkies)):
        monkey = monkies[i]
        print("monkey ", i)

        while (len(monkey[1]) > 0):
            item = monkey[1][0]
            inspect[i] += 1
            altItem = doOperation(monkey[2], item)
            # altItem = altItem//3
            monkey[1][0] = altItem
            if(altItem%monkey[3] == 0):
                moveItem(i,monkey[4],altItem)
            else:
                moveItem(i,monkey[5],altItem)


def moveItem(f, t,item):

    mF = monkies[f]
    mT = monkies[t]
    i = mF[1][0]
    mF[1] = mF[1][1:]
    mT[1].append(item)


print(monkies)
for i in range(1000):
    print("round: ",i )
    playRound()
print(inspect)
inspect.sort()
print(inspect[-2]*inspect[-1])
# print(monkies)

