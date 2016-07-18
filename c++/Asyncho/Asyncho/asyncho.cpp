#include "asyncho.h"

Asyncho::Asyncho(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(this, SIGNAL(needImages(QString)), this, SLOT(readImages(QString)));
    connect(this, SIGNAL(readCompleted(QString)), this, SLOT(doWork(QString)));
}

Asyncho::~Asyncho()
{

}

void Asyncho::readImages( QString workType )
{
    QString srcFile = "Y:\\RefData\\TDI_mostd\\TDI072_mostd_new\\level1_data\\";
    int xBeg = 6, xEnd = 34;
    time_t ct = time(0);
//#pragma omp parallel for num_threads(2)
    for(int xSerial = xBeg; xSerial <= xEnd; ++xSerial){
        QString imageName = srcFile + QString("z10\\y20\\%1_20_10.tif").arg(xSerial);
        cout<<imageName.toStdString()<<endl;
        TIFF *tif = TIFFOpen(imageName.toStdString().c_str(), "r");
        uint16 imageType;
        uint16 *imageData16 = NULL;
        uchar *imageData8 = NULL;
        uint32 imageWidth, imageHeight, rowsPerStrip, stripByteCounts, stripNum;
        TIFFGetField(tif, TIFFTAG_STRIPBYTECOUNTS, &stripByteCounts);
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &imageWidth);
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imageHeight);
        TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &imageType);
        TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &rowsPerStrip);
        stripNum = imageHeight / rowsPerStrip;
        if(imageType == 16){
            imageData16 = new uint16[imageWidth * imageHeight * 512];
        }else if(imageType == 8){
            imageData8 = new uchar[imageWidth * imageHeight * 512];
        }
        uint32 curDirectory = 0;
        TIFFSetDirectory(tif, curDirectory);
        for(int z = 0; z < 512; ++z){
            for(uint32 i = 0; i < stripNum; ++i){
                if(imageType == 8){
                    TIFFReadEncodedStrip(tif, i, &imageData8[curDirectory * imageWidth * imageHeight + i * stripByteCounts], stripByteCounts);
                }else if(imageType == 16){
                    TIFFReadEncodedStrip(tif, i, &imageData16[curDirectory * imageWidth * imageHeight + i * stripByteCounts], stripByteCounts);
                }    
            }
            TIFFReadDirectory(tif);
        }
        TIFFClose(tif);
    }
    cout<<"Eclipsed Time: "<<time(0) - ct<<endl;
    emit readCompleted(workType);
}

void Asyncho::doWork( QString workType )
{
    cout<<workType.toStdString()<<endl;
}

void Asyncho::emitImageNeed( QString workType )
{
    emit needImages(workType);
}
