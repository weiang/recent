a = 1
def it():
#	global a
#	a = 2
	yield 3
	a += 1
	yield 4

for i in it():
	print("i={};a={}".format(i, a))
