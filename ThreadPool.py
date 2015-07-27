#! /usr/bin/python 
## -*- encoding: utf-8 -*-

from threading import Thread, Lock
import time
from time import sleep
import sys

class ThreadPool:

    def __init__(self, thread_cnt=5):
        self.__threads = []
        self.__resize_lock = Lock()
        self.__task_lock = Lock()
        self.__tasks = []
        self.__is_joining = False
        self.set_thread_cnt(thread_cnt)

    def set_thread_cnt(self, thread_cnt):
        if self.__is_joining:
            return False

        with self.__resize_lock:
            self.__set_thread_cnt_nolock(thread_cnt)

            return True

    def __set_thread_cnt_nolock(self, thread_cnt):
        while thread_cnt > len(self.__threads):
            new_thread = ThreadPoolThread(self)
            self.__threads.append(new_thread)
            new_thread.start()

        while thread_cnt < len(self.__threads):
            self.__threads[0].go_away()
            del self.__threads[0]

    def get_thread_cnt(self):
        with self.__resize_lock:
            return len(self.__threads)

    def queue_task(self, task, args=None, task_callback=None):
        if self.__is_joining:
            return False

        if not callable(task):
            return False

        with self.__task_lock:
            self.__tasks.append((task, args, task_callback))
            return True

    def get_next_task(self):
        with self.__task_lock:
            if len(self.__tasks) == 0:
                return (None, None, None)
            else:
                return self.__tasks.pop(0)

    def join_all(self, wait_for_tasks=True, wait_for_threads=True):
        self.__is_joining = True

        if wait_for_tasks:
            while self.__tasks != []:
                sleep(.1)

        with self.__resize_lock:
            self.__set_thread_cnt_nolock(0)
            self.__is_joining = True
            if wait_for_threads:
                for t in self.__threads:
                    t.join()
                    del t

        self.__is_joining = False

class ThreadPoolThread(Thread):
    thread_sleep_time = 0.1

    def __init__(self, pool):
        Thread.__init__(self)
        self.__pool = pool
        self.__is_dying = False

    def run(self):
        while self.__is_dying == False:
            task, args, task_callback = self.__pool.get_next_task()
            if task == None:
                sleep(ThreadPoolThread.thread_sleep_time)
            elif task_callback == None:
                task(args)
            else:
                task_callback(task(args))

    def go_away(self):
        self.__is_dying = True


def print_task(string):
    s = 'Task: ' + string
    sys.stdout.write(s + '\n');
    return s 

def callback_task(string):
    sys.stdout.write('Callback: ' + string + '\n');

def task(args):
    sleep(1)

def test():
    global task
    tasks = [ (task, None, None) for i in range(10) ]

    # Thread Pool
    thread_pool = ThreadPool(4)
    start_time = time.time()
    for task in tasks:
        thread_pool.queue_task(task[0], task[1], task[2])
    thread_pool.join_all()
    end_time = time.time()
    print "Thread pool: %fs" % (end_time - start_time)

    # Serial
    start_time = time.time()
    for task in tasks:
        task[0](task[1])
    end_time = time.time()
    print "Serial: %fs" % (end_time - start_time)

if __name__ == '__main__':
    test()
