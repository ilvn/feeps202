#!/usr/bin/env python
#
#   Slice a text file into (tweetable) pieces
#
from sys import argv

piece_sz = 140

for filename in argv[1:]:
	buf = ""
	try:
		with open(filename, "r") as f:
			buf = f.read().strip()
			f.close()
	except:
		print "Error reading from", filename
	sz = len(buf)
	for i in range(0, sz, piece_sz):
		with open("%s.p_%d" %(filename,i/piece_sz), "w") as f:
			f.write(buf[i:i+piece_sz])
			f.close()


