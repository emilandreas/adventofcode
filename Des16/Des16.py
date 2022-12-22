import re
import sys
import copy
import networkx as nx
import matplotlib.pyplot as plt
   
  
# Defining a Class
class GraphVisualization:
   
    def __init__(self):
          
        # visual is a list which stores all 
        # the set of edges that constitutes a
        # graph
        self.visual = []
          
    # addEdge function inputs the vertices of an
    # edge and appends it to the visual list
    def addEdge(self, a, b):
        temp = [a, b]
        self.visual.append(temp)
          
    # In visualize function G is an object of
    # class Graph given by networkx G.add_edges_from(visual)
    # creates a graph with a given list
    # nx.draw_networkx(G) - plots the graph
    # plt.show() - displays the graph
    def visualize(self):
        G = nx.Graph()
        G.add_edges_from(self.visual)
        nx.draw_networkx(G)
        plt.show()
  
# Driver code
G = GraphVisualization()
# G.addEdge(0, 2)
# G.addEdge(1, 2)
# G.addEdge(1, 3)
# G.addEdge(5, 3)
# G.addEdge(3, 4)
# G.addEdge(1, 0)
# G.visualize()


f = open("Des16/input.txt", "r")
lines = f.readlines()

tunnels={}
graph={}


for line in lines:
    m = re.match(r"Valve (\w+) has flow rate=(\d+); tunnels? leads? to valves? ((?:[A-Z][A-Z], )*[A-Z][A-Z])", line)
    if(m):
        valve, rate, t = m.groups()
        tunnels[valve] = [int(rate), t.split(', '), False]
        graph[valve] = [int(rate), t.split(', '), 99999999]

for key, value in tunnels.items():
    for node in value[1]:
        G.addEdge(key, node)
# G.visualize()
maxReleased = 0
count = 0

# def getLengthToWorkingValves():
#     valve = 'AA'

# def searchDF(valve, dist):
#     v = graph[valve]
#     v[2] = dist
#     for newV in v[1]:
#         if(graph[newV][2] > dist+1):
#             searchDF(newV, dist+1)

# searchDF('AA', 0)
# print(graph)

mem = {}
newMax = 0
def runMinute(valve, flow, sum, minute, isopen):
    global maxReleased
    if(minute == 30):
        # maxReleased = max(maxReleased, sum)
        if(sum > maxReleased):
            maxReleased = sum
            print("new max: ", maxReleased)
        return newMax
    sum += flow

    #open valve
    t = tunnels[valve]
    if(t[0] > 0 and not valve in isopen):
        t[2] = True
        isopen.append(valve)
        flow += t[0]
        return runMinute(valve, flow, sum, minute + 1, isopen.copy())
    
    #move
    else:
        
        for newV in t[1]:
            return runMinute(newV, flow, sum, minute + 1, isopen.copy())
        
    
# runMinute("AA", 0, 0, 0, [])

print(maxReleased, count)
