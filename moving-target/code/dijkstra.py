#!/usr/bin/env python
import IPython
from parser1000 import parser1000
from PriorityQueue import PriorityQueue

def cost(C,state):
	(x,y) = state
	return C[x][y]
def checkBounds(state):
	(x,y) = state
	return 0<=x<N and 0<=y<N
def getSuccessors(state):
	(x,y) = state
	successors = [(x+1,y),(x,y-1),(x-1,y),(x,y+1)]
	successors = filter(checkBounds,successors)
	return successors
def dijkstra(start,C):
	openSet = PriorityQueue()
	openCheck = {}
	closedSet = {}
	g = {}
	for i in range(len(start)):
		g[start[i]] = 0
	for i in range(len(start)):
		openSet.put(start[i],0)
		openCheck[start[i]] = 1
	while not openSet.empty():
		currentState = openSet.get()
		closedSet[currentState] = 1
		for nextState in getSuccessors(currentState):
			if nextState in closedSet:
				continue

			newCost = g[currentState] + cost(C,nextState)
			if nextState not in openCheck:
				g[nextState] = newCost
				openSet.put(nextState,g[nextState])
				openCheck[nextState] = 1
			elif newCost >= g[nextState]:
				continue
			else:
				g[nextState] = newCost
				openSet.update(nextState,g[nextState])
				openCheck[nextState] = 1

	hmap = open('heuristic.txt','w')
	temp=''
	for i in range(N):
		temp=''
		for j in range(N):
			if j==0:
				temp +=str(g[(i,j)])			
			else:
				temp +=','+str(g[(i,j)]) 
		if i==0:
			hmap.write(temp)
		else:
			hmap.write('\n'+temp)	
	hmap.close()
	return False

def main():
	start = []
	global N
	N,R,pos,C = parser1000()
	for i in range(len(pos)):
		start.append(tuple(pos[i]))
	dijkstra(start,C)

if __name__ == "__main__": 
	main()
