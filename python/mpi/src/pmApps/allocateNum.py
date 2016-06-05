def alloNum(s,usedArray):
        alloedArray=[]
        l = len(usedArray)
        drawerN = l/s
        lastBall = l%s
        longList = [drawerN]*s
        if lastBall == 0:
            pass
        else:
            for i in range(lastBall):
                longList[i] = longList[i] + 1
        index = 0
        for i in range(s):
            l = longList[i]
            tA = usedArray[index:l+index]
            alloedArray.append(tA)
            index = l + index
        
        return alloedArray
                           

def alloNum4pro(s,usedArray,n):
        alloedArray=[]
        l = len(usedArray)
        workN = l / n
        lastWork = l % n
        drawerN = workN / s
        lastBall = workN % s
        longList = [drawerN*n]*s
        if lastBall == 0:
            pass
        else:
            for i in range(lastBall):
                longList[i] = longList[i] + n
        if lastWork != 0:
            longList[s-1] = longList[s-1] + lastWork
        index = 0
        for i in range(s):
            l = longList[i]
            tA = usedArray[index:l+index]
            alloedArray.append(tA)
            index = l + index
         
        return alloedArray    
        