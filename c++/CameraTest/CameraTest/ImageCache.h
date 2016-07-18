#ifndef IMAGECACHE_H
#define IMAGECACHE_H
#include "stdafx.h"
#include <time.h>
#include "TestVtkVolume.h"
class ImageCache;
typedef std::tr1::shared_ptr<ImageCache> SmartCache;



class ImageCache{
public:
    ImageCache(u_int bitsNumArg);
    ~ImageCache();
    void Modified();
    void GetImagePtr(u_char* &arg){arg = imageData8;}
    void GetImagePtr(u_short* &arg){arg = imageData16;}
    void SetImageName(const string &arg){imageName = arg;}
    LONGLONG GetLastUsedTime(){return lastUsedTime;}
    string GetImageName(){return imageName;}
    LONGLONG GetBuildTime(){return buildTime;}

private:
    u_int imageBits;
    u_char *imageData8;
    u_short *imageData16;
    LONGLONG lastUsedTime;
    LONGLONG buildTime;
    string imageName;
};


class ImageCaches{
public:
    ImageCaches(u_int numArg, u_int bitsArg);
    ~ImageCaches();
    SmartCache &GetSmartCache(const string &nameArg);
    void TravelCaches();
    bool isCacheExisting(const string &nameArg);  

private:
    static bool CachSortFun(const SmartCache &arg1, const SmartCache &arg2);
    void SortCaches();
    void DeleteUnusedCache();
    void AddCache(const string &nameArg);
    deque<SmartCache> cachePtrs;
    u_int cacheMaxNum;
    u_int imageBits;
};


#endif