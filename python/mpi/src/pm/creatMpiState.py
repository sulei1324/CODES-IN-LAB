def newState(nodeName,n,pType,mType):
    t = pType
    if t == 1:
        appName = "tar2monApp.py"
    elif t == 2:
        appName = "tar2proApp.py"
    elif t == 3:
        appName = "tar2resApp.py"
    nodeArray = nodeName.split()
    nodeNum = len(nodeArray)
    if mType == 1:
        
        mpiState = "/usr/mpi/gcc/openmpi-1.4.3/bin/mpirun -n "
        s=str(n)
        mpiState = mpiState + s + ' '     
        s = ""
        for i in range(len(nodeArray)):
            s = s + "-host " + nodeArray[i] + " "       
        mpiState = mpiState + s + "python "      

        mpiState = mpiState + appName
    else:
        mpiState = "mpiexec.exe "
        s = str(n)
        mpiState += "-hosts " + s + " " + nodeName + ' python ' + appName
        
    return mpiState


#  mpiexec.exe -hosts 4 user-PC user-PC user-PC user-PC python mpiTest.py
#   "/usr/mpi/gcc/openmpi-1.4.3/bin/mpirun -n 4 -host cu01 -host cu02 python ./mpiTest.py"