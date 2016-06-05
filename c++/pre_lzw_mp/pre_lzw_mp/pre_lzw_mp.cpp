#include "pre_lzw_mp.h"

pre_lzw_mp::pre_lzw_mp(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(ui.lineEdit, SIGNAL(textChanged(const QString &)), SLOT(enable_button()));
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(do_work()));
}

pre_lzw_mp::~pre_lzw_mp()
{
}

void pre_lzw_mp::enable_button(){
    ui.pushButton->setEnabled(true);

}

void pre_lzw_mp::do_work(){
    thread_num = ui.lineEdit_3->text().toInt();
    src = ui.lineEdit->text();
    dst = ui.lineEdit_2->text();
    int level_num = 0;
    QString level_num_str = "";
    QDir src_dir(src);
    QRegExp reg_05d("(\\d){5}");
    QFileInfoList src_list = src_dir.entryInfoList();
//    qDebug()<<src_list.length();
    QList<QFileInfo>::iterator src_beg = src_list.begin();
    for(QList<QFileInfo>::iterator src_iter = src_beg; src_iter < src_list.end(); ++src_iter){
        if((*src_iter).isDir() && (reg_05d.exactMatch((*src_iter).fileName()))){
               pool<<(*src_iter).fileName();
        } 
    }
    int l = pool.length();
    int i;
#pragma omp parallel for num_threads(6)
    for(i = 0; i < l; ++i){
        qDebug()<<pool.at(i)<<omp_get_thread_num();
        //do_lzw(pool.at(i));
    
    
    }

}

void pre_lzw_mp::do_lzw(QString n){
    QString job = n;
    QString images_src = src + "\\" +n;
    QString write_dst = dst + "\\" + n;
    QString image_name, saved_name;
    int dot_pos;
    QString image_path;
    QDir images_dir(images_src);
    QDir write_dir(dst);
    write_dir.mkdir(job);
    qDebug()<<images_src;
    qDebug()<<write_dst;
    QFileInfoList images_info_list = images_dir.entryInfoList();
    QList<QFileInfo>::iterator image_iter = images_info_list.begin();
    FreeImage_Initialise(true);
    for(; image_iter < images_info_list.end(); ++image_iter){
        if((*image_iter).isDir()){
//            qDebug()<<(*image_iter).fileName();
            continue;
        }
        image_name = (*image_iter).fileName();
        dot_pos = image_name.indexOf(".");
        saved_name = write_dst + "\\" + image_name.left(dot_pos) + "_c.tif";
        image_path = (*image_iter).absoluteFilePath();
        FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(image_path.toStdString().c_str(), 0);
        if(fif == FIF_UNKNOWN){
            fif = FreeImage_GetFIFFromFilename(image_path.toStdString().c_str());
        }
        if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)){
            FIBITMAP *image = FreeImage_Load(fif, image_path.toStdString().c_str());
            FreeImage_Save(FIF_TIFF, image, saved_name.toStdString().c_str(), TIFF_LZW);
            FreeImage_Unload(image);
        }        
    }
    FreeImage_DeInitialise();
}


