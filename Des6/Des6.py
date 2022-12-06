f = open("Des6/input.txt", "r")

line = f.readlines()[0]
for i in range(14,len(line)):
    if(len(set(line[i-14:i])) == 14): print(i)
