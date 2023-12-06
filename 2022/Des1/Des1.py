import pandas as pd
import bisect

# df = pd.read_fwf("Des1/Des1-input.txt", header=None)

file = open("Des1/Des1-input.txt", "r")
lines = file.readlines();
score = 0
maxscore = 0
scores = []
for line in lines:
    print(maxscore, score, line)
    if(line == "\n" or line == "" or line == " " or line != line):
        print("space")
        bisect.insort(scores, score)
        if (score > maxscore):
            maxscore = score
            print("New max score: ", maxscore)
        score = 0
        continue
        
    score += int(line)

if (score > maxscore):
    maxscore = score
    print("New max score: ", maxscore)
    score = 0   

print(maxscore)
print(scores)
print(scores[-1]+ scores[-2]+scores[-3])