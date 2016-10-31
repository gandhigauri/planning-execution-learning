import heapq
import IPython

class PriorityQueue:
	def __init__(self):
		self.elements=[]
	def empty(self):
		return len(self.elements)==0
	def put(self, state, priority):
		pair = (priority,state)
		heapq.heappush(self.elements,pair)
	def get(self):
		temp = heapq.heappop(self.elements)
		return temp[1], temp[0]
	def exists(self, state):
		return state in (x[1] for x in self.elements)

