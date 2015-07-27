#! /usr/bin/python 
## -*- encoding: utf-8 -*-

from threading import Thread, Lock
from Queue import Queue
from urllib2 import urlopen

class Fetcher:

	def __init__(self, threads=5):
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
			
			try:
				content = urlopen(req).read()
			except:
				content = ''
			finally:
				self.q_ans.put((req, content))

			with self.lock:
				self.running -= 1

	def push(self, req):
		return self.q_req.put(req)

	def pop(self):
		return self.q_ans.get()

	def taskleft(self):
		return self.q_req.qsize() + self.q_ans.qsize() + self.running

def test():
	f = Fetcher(2)
	reqs = ["http://www.baidu.com", "http://www.sina.com", "http://www.bing.com"]#, "http://weibo.com/u/2806519004/home?wvr=5&lf=reg"]
	for req in reqs:
		f.push(req)

	while f.taskleft():
		ans = f.pop()
		print "Url: %s" % (ans[0])
		print "Content: %s" % (ans[1])

if __name__ == '__main__':
		test()
