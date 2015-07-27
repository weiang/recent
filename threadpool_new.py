#! /usr/bin/env python
## -*- coding: utf-8 -*-

import sys
import threading
import Queue
import traceback

class WorkerThread(threading.Thread):
	
	def __init__(self, request_queue, result_queue, poll_timeout=5, **kwds):
		threading.Thread.__init__(self, **kwds)
		self.setDaemon(True)
		self._request_queue = request_queue
		self._result_queue = result_queue
		self._poll_timeout = poll_timeout
		self._dismissed = threading.Event()
		self.start()

	def run(self):
		while True:
			if self._dismissed.isSet():
				break

			try:
				request = self._request_queue.get(True, self._poll_timeout)
			except Queue.Empty:
				continue
			else:
				if self._dismissed.isSet():
					self._request_queue.put(request)
					break
				try:
					result = request.callable(*request.args, **request.kwds)
					self._result_queue.put((request, result))
				except:
					request.exception = True
					self._result_queue.put((request, sys.exc_info()))


	def dismiss(self):
		self._dismissed.set()

		