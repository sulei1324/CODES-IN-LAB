#include <stdio.h>

#include "tiffio.h" // Includes the TIFF APIs Declarations

#pragma comment( lib, "libtiff.lib" )

int main()
{
   TIFF *tif_r,*tif_w; // Tiff file pointers creation
   int count=0;
  uint32 imageWidth, imageLength, TileWidth, TileLength, imageRowsPerStrip,x=1,y=1,x1=1024,y1=768,i,j,s,row;
  uint16 imageCompression, imageSamplePerPixel ;
  uint16 imagePlanarConfig, imagePhotoMetric, ResolutUnit ;
  uint16 bps ;
  tstrip_t strip;
  uint32* raster;

 unsigned char *m_pData;
 
   tdata_t buf,bp;

// Opening output file in append mode will help to append to the previous runs.
   tif_w=TIFFOpen(/*argv[argc-1]*/"22.tif","a");
   if ( tif_w==NULL )
   {
   //   printf("unable to open file %s \n",argv[argc-1]);
      return 0;
   }


  
      tif_r=TIFFOpen(/*argv[i]*/"11.tif","r");
	  
      if ( tif_r != NULL )
      {
         /* 讀取 TIFF 標籤 */ 
          TIFFGetField(tif_r, TIFFTAG_IMAGEWIDTH, &imageWidth);
          TIFFGetField(tif_r, TIFFTAG_IMAGELENGTH, &imageLength);
      
          TIFFGetField(tif_r, TIFFTAG_BITSPERSAMPLE, &bps);
       //  TIFFGetField(tif_r, TIFFTAG_COMPRESSION, &imageCompression);
          TIFFGetField(tif_r, TIFFTAG_PHOTOMETRIC, &imagePhotoMetric);
      
          TIFFGetField(tif_r, TIFFTAG_SAMPLESPERPIXEL, &imageSamplePerPixel);
         TIFFGetField(tif_r, TIFFTAG_ROWSPERSTRIP, &imageRowsPerStrip);

       
          TIFFGetField(tif_r, TIFFTAG_RESOLUTIONUNIT, &ResolutUnit);

          TIFFGetField(tif_r, TIFFTAG_PLANARCONFIG, &imagePlanarConfig);
          
          
          /* 寫入 TIFF 標籤 */ 
          TIFFSetField(tif_w, TIFFTAG_IMAGEWIDTH, imageWidth);
          TIFFSetField(tif_w, TIFFTAG_IMAGELENGTH, imageLength);
          
          TIFFSetField(tif_w, TIFFTAG_BITSPERSAMPLE, bps);
         // TIFFSetField(tif_w, TIFFTAG_COMPRESSION, imageCompression);
          TIFFSetField(tif_w, TIFFTAG_PHOTOMETRIC, imagePhotoMetric);
          
          TIFFSetField(tif_w, TIFFTAG_SAMPLESPERPIXEL, imageSamplePerPixel);
          TIFFSetField(tif_w, TIFFTAG_ROWSPERSTRIP, imageRowsPerStrip);
         // TIFFSetField(tif_w, TIFFTAG_PIXAR_IMAGEFULLWIDTH, x1-x+1);
       //    TIFFSetField(tif_w, TIFFTAG_PIXAR_IMAGEFULLLENGTH, y1-y+1);
          TIFFSetField(tif_w, TIFFTAG_RESOLUTIONUNIT, ResolutUnit);  
	
          
          TIFFSetField(tif_w, TIFFTAG_PLANARCONFIG, imagePlanarConfig);
	  raster = (uint32*) _TIFFmalloc(imageWidth*imageLength * sizeof (uint32)); // 分配适当格式的内存
	  
        if (raster != NULL) {
            if (TIFFReadRGBAImage(tif_r, imageWidth, imageLength, raster, 0)) { // 读入图像数据
             //  	buf = (uint32*) _TIFFmalloc((imageWidth) * sizeof (uint32));
				count=&raster;
				for(i=y1-1;i>=y;i--){
				
							
						for(j=x-1;j<x1;j++)	{
								buf=raster+i*imageWidth+j;
							
								
							}TIFFWriteScanline(tif_w,buf,i,0);
							
				}
			  //TIFFWriteScanline(tif_w,buf,i-y+1,0);_TIFFfree(buf);
				}
            }
       /*
       for ( s=0;s<imageSamplePerPixel;s++ )
         {
            for ( row =0;row<y1-y;row++ )
            {
               //TIFFReadScanline(tif_r,buf,row,s);
               TIFFWriteScanline(tif_w,buf,row,s);
            }
         }
	  
         */
		     _TIFFfree(raster); // 释放内存
        
		}
      else
      {
			
         TIFFClose(tif_r);
         TIFFClose(tif_w);
         return 0;
      }

   
   TIFFClose(tif_w);
  return 1;
}