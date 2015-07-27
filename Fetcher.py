#! /usr/bin/python 
## -*- encoding: utf-8 -*-

from threading import Thread, Lock
from Queue import Queue

class Fetcher:

	def __init__(self, threads=5):
		print "Fetcher init"
		print "threads: %d" % (threads)
		self.threads = threads
		self.lock = Lock()
		self.q_req = Queue()
		self.q_ans = Queue()

		for i in range(self.threads):
			t = Thread(target=self.threadget)
			t.setDaemon(True)
			t.start()
		
		self.running = 0

	def __del__(self):
		print "Fetcher delete"
		self.q_req.join()
		self.q_ans.join()

	def threadget(self):
		while True:
			req = self.q_req.get()
			with self.lock:
				self.running += 1
			
			print "R: %s" % (req)
			self.q_ans.put(req)

			with self.lock:
				self.running -= 1

	def push(self, req):
		return self.q_req.put(req)

	def pop(self):
		return self.q_ans.get()

	def taskleft(self):
		return self.q_req.qsize() + self.q_ans.qsize() + self.running

def test():
	f = Fetcher(6)
	reqs = ["%d&&&&" %i for i in range(10)]
	for req in reqs:
		f.push(req)

	while f.taskleft():
		ans = f.pop()
		print "A: %s" % (ans)


if __name__ == '__main__':
		test()
