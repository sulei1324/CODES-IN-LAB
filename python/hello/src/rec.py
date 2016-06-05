from _pyio import __metaclass__
x=0

def recursion():
    global x
    x=x+1
    if(x<100):
        recursion()
    print x

recursion()



    