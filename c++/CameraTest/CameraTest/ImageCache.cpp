#include "stdafx.h"
#include "ImageCache.h"


ImageCache::ImageCache(u_int bitsNumArg):
    imageBits(bitsNumArg)
{
    if(imageBits == 8){
        imageData8 = new u_char[512 * 512 * 512];
        imageData16 = NULL;
    }else if(imageBits == 16){
        imageData16 = new u_short[512 * 512 * 512];
        imageData8 = NULL;
    }else{
        imageData16 = NULL;
        imageData8 = NULL;
    }
    LARGE_INTEGER cTime;
    QueryPerformanceCounter(&cTime);
    buildTime = cTime.QuadPart;
    lastUsedTime = cTime.QuadPart;
}

ImageCache::~ImageCache()
{
    if(imageData8){
        delete []imageData8;
    }
    if(imageData16){
        delete []imageData16;
    }
}

void ImageCache::Modified()
{
    LARGE_INTEGER cTime;
    QueryPerformanceCounter(&cTime);
    lastUsedTime = cTime.QuadPart;
}

ImageCaches::ImageCaches( u_int numArg, u_int bitsArg ):
    cacheMaxNum(numArg),
    imageBits(bitsArg)
{
    
}

ImageCaches::~ImageCaches()
{

}

bool ImageCaches::CachSortFun( const SmartCache &arg1, const SmartCache &arg2 )
{
    return arg1->GetLastUsedTime() > arg2->GetLastUsedTime();
}

bool ImageCaches::isCacheExisting( const string &nameArg )
{
    if(cachePtrs.size() != 0){
        for(vector<SmartCache>::size_type i = 0; i < cachePtrs.size(); ++i){
            SmartCache cachePtrI = cachePtrs.at(i);
            if(nameArg.compare(cachePtrI->GetImageName()) == 0){
                return true;
            }
        }
    }
    return false;
}

void ImageCaches::SortCaches()
{
    sort(cachePtrs.begin(), cachePtrs.end(), CachSortFun);
}

void ImageCaches::DeleteUnusedCache()
{
    cachePtrs.pop_back();
}

void ImageCaches::AddCache( const string &nameArg )
{
    SmartCache tmpCache(new ImageCache(imageBits));
    tmpCache->SetImageName(nameArg);
    if(cachePtrs.size() >= cacheMaxNum && cacheMaxNum >= 2){
        SortCaches();
        DeleteUnusedCache();
    }else if(cacheMaxNum == 1){
        DeleteUnusedCache();
    }
    cachePtrs.push_front(tmpCache);
}

SmartCache & ImageCaches::GetSmartCache( const string &nameArg )
{
    if(cachePtrs.size() != 0){
        for(deque<SmartCache>::size_type i = 0; i < cachePtrs.size(); ++i){
            SmartCache cachePtrI = cachePtrs.at(i);
            if(nameArg.compare(cachePtrI->GetImageName()) == 0){
                cachePtrI->Modified();
                return cachePtrI;
            }
        }
        AddCache(nameArg);
    }else{
        AddCache(nameArg);
    }
    return *cachePtrs.begin();
}

void ImageCaches::TravelCaches()
{
    cout<<"-------------------------------"<<endl;
    for(deque<ImageCache>::size_type i = 0; i < cachePtrs.size(); ++i){
        SmartCache tmpCache = cachePtrs.at(i);
        cout<<i<<endl;
        cout<<tmpCache->GetImageName()<<endl;
        cout<<tmpCache->GetLastUsedTime()<<endl;
    }
    cout<<"##########################"<<endl;
}
