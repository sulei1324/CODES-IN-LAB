import getopt,  sys
opts,args = getopt.getopt(sys.argv[1:],"hi:")
for op, value in opts:
	print op," and ", value
print "args",args
