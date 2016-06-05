import os


def hasLost(begNum,endNum,srcPath,readPre,readPost):
    for i in range(begNum,endNum+1):
        serialN = "%05d"%(i)
        filename = srcPath + readPre + serialN +readPost
        if os.path.exists(filename):        
            pass
        else:
            return True

    
def printLostFile(begNum,endNum,srcPath,readPre,readPost):
    lostFileN=0
    existFileN=0
    lostFileSA = []
    existFileSA =[]
    sExistSN = None
    eExistSN = None
    sLostSN = None
    eLostSN = None
    for i in range(begNum,endNum+1):
        serialN = "%05d"%(i)
        filename = srcPath + readPre + serialN +readPost
        if os.path.exists(filename):        
            existFileN+=1
            if existFileN == 1:
                sExistSN = i
                eExistSN = i
            else:
                if (i - eExistSN) == 1:
                    eExistSN = i
                else:
                    preExistSA = [sExistSN,eExistSN]
                    sExistSN = i    
                    eExistSN = i
                    existFileSA += preExistSA 
        else:
            lostFileN+=1
            if lostFileN ==1:            
                sLostSN = i
                eLostSN = i
            else:
                if (i - eLostSN) == 1:
                    eLostSN = i
                else:
                    preLostSA = [sLostSN,eLostSN]
                    sLostSN = i
                    eLostSN = i
                    lostFileSA += preLostSA
        if i == endNum:
            if (eLostSN != None) and (eLostSN <= endNum):
                preLostSA = [sLostSN,eLostSN]
                lostFileSA+=preLostSA
            if (eExistSN != None) and (eExistSN <= endNum):
                preExistSA = [sExistSN,eExistSN]
                existFileSA += preExistSA 
    
    if lostFileN == 0:
        print "There is no file lost."
    else:
        print "The files below are missing: "
        for i in range(len(lostFileSA)//2):
            s = lostFileSA[2*i]
            e = lostFileSA[2*i+1]
            for j in range(s,e+1):
                serialN = "%05d"%(j)
                filename = srcPath + readPre + serialN +readPost
                print filename
    
    

    


def getAvailSerial(begNum,endNum,srcPath,readPre,readPost):
    lostFileN=0
    existFileN=0
    lostFileSA = []
    existFileSA =[]
    sExistSN = None
    eExistSN = None
    sLostSN = None
    eLostSN = None
    for i in range(begNum,endNum+1):
        serialN = "%05d"%(i)
        filename = srcPath + readPre + serialN +readPost
        if os.path.exists(filename):   
            print "hhhhhhh"     
            existFileN+=1
            if existFileN == 1:
                sExistSN = i
                eExistSN = i
            else:
                if (i - eExistSN) == 1:
                    eExistSN = i
                else:
                    preExistSA = [sExistSN,eExistSN]
                    sExistSN = i    
                    eExistSN = i
                    existFileSA += preExistSA 
        else:
            lostFileN+=1
            if lostFileN ==1:            
                sLostSN = i
                eLostSN = i
            else:
                if (i - eLostSN) == 1:
                    eLostSN = i
                else:
                    preLostSA = [sLostSN,eLostSN]
                    sLostSN = i
                    eLostSN = i
                    lostFileSA += preLostSA
        if i == endNum:
            if (eLostSN != None) and (eLostSN <= endNum):
                preLostSA = [sLostSN,eLostSN]
                lostFileSA+=preLostSA
            if (eExistSN != None) and (eExistSN <= endNum):
                preExistSA = [sExistSN,eExistSN]
                existFileSA += preExistSA 
    
    
    usedFileSerial = [0]*existFileN
    if existFileN == 0:
        return None
    else:
        index = 0        
        for i in range(len(existFileSA)//2):
            s = existFileSA[2*i]
            e = existFileSA[2*i+1]
            for j in range(s,e+1):
                usedFileSerial[index] = j
                index += 1
        return usedFileSerial