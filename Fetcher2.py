#!/usr/bin/env python
# -*- encoding=utf-8 -*-

import threading
from threading import Lock
import urllib2
import time
from Queue import Queue

class Fetcher:

    def __init__(self, threads=5):
        self.__thread_cnt = threads
        self.__threads = []
        self.__lock = Lock()
        self.q_req = Queue()
        self.q_resp = Queue()

        self.__running = 0
        for i in range(self.__thread_cnt):
            new_thread = threading.Thread(target=self.__task)
            new_thread.setDaemon(True)
            new_thread.start()
            self.__threads.append(new_thread)

        

    def __task(self):
        while True:
            req = self.q_req.get()
            print "Req: %s" % (req)
            with self.__lock:
                self.__running += 1
            content = urllib2.urlopen(req).read()
            self.q_resp.put((req, content))

            with self.__lock:
                self.__running -= 1

    def push(self, req):
        self.q_req.put(req)

    def pop(self):
       return self.q_resp.get()

    def task_left(self):
        return self.__running + self.q_resp.qsize() + self.q_req.qsize()

def test():
    urls = ["http://www.baidu.com", "http://www.sina.com", "http://www.bing.com"]

    reqs = ["%s" % (urls[i%3]) for i in range(15)]
    f = Fetcher(20)

    s_time = time.time()
    for req in reqs:
        f.push(req)
    while f.task_left():
        resp = f.pop()

    e_time = time.time()
    print "Threads: %fs" % (e_time - s_time)

    s_time = time.time()
    for req in reqs:
        urllib2.urlopen(req).read()
    e_time = time.time()
    print "Serial: %fs" % (e_time - s_time)

if __name__ == '__main__':
    test()
