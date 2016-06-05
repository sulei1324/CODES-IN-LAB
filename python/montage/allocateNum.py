def alloNum(s,usedArray):
        alloedArray=[]
        l = len(usedArray)
        drawerN = l/s
        lastBall = l%s
        longList = [drawerN]*s
        for i in range(lastBall):
            longList[i] = longList[i] + 1
        index = 0
        for i in range(s):
            l = longList[i]
            tA = usedArray[index:l+index]
            alloedArray.append(tA)
            index = l + index
        
        return alloedArray
                           
        