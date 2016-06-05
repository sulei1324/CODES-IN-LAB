def newState(nodeName,n,pType,mType):
    t = pType
    if t == 1:
        appName = "tarApp.py"
    elif t == 2:
        appName = "montageApp.py"
    elif t == 3:
        appName = "projectApp.py"
    elif t == 4:
        appName = "resampleApp.py"
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


#  mpiexec.exe -n 4 -hosts 4 user-PC user-PC user-PC user-PC python mpiTest.py