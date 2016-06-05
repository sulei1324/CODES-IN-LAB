#include "pre_lzw.h"
#include <FreeImage.h>



pre_lzw::pre_lzw(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(ui.lineEdit, SIGNAL(textChanged(const QString &)),  SLOT(enable_button()));
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(do_work()));
    /*connect(ui.lineEdit_2, SIGNAL(textChanged(const QString &)), SLOT());*/
}

pre_lzw::~pre_lzw()
{

}

void pre_lzw::enable_button(){
    ui.pushButton->setEnabled(true);

}

void pre_lzw::do_work(){
    QString src = ui.lineEdit->text();
    
    QDir src_dir(src);
    QDir handled_dir = "";
    QString label_str = "";
    QFileInfoList src_list = src_dir.entryInfoList();
    QList<QFileInfo>::iterator src_b = src_list.begin();
    QRegExp  reg_05d("(\\d){5}");
    for(; src_b < src_list.end(); ++src_b){
        if(reg_05d.exactMatch((*src_b).fileName())){
            label_str += (*src_b).path() + "/" + (*src_b).fileName() + QString("\n");
            handled_dir = QDir((*src_b).path() + "/" + (*src_b).fileName());
            do_lzw(handled_dir);
        }    
    }
    


}

void pre_lzw::do_lzw(const QDir & d){
    FreeImage_Initialise(true);
    QString label_out = "";
    QString dst = ui.lineEdit_2->text();
    QString d_src = d.path();
    QString serial_str = d_src.right(5);
    QDir dst_dir(dst);
    dst_dir.mkdir(serial_str);
    QString image_name = "", image_name_path(""), saved_name("");
    int dot_pos = 0;
    QFileInfoList handled_images = d.entryInfoList();
    QList<QFileInfo>::iterator images_iter = handled_images.begin();
    
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    for(; images_iter < handled_images.end(); ++images_iter){
        image_name_path = (*images_iter).absoluteFilePath();
        if((*images_iter).isDir()){
            continue;
        }
        FIBITMAP *handled_image = 0;
        image_name = (*images_iter).fileName();
        dot_pos = image_name.indexOf(".");
        saved_name = dst + "\\" + serial_str + "\\" + image_name.left(dot_pos) + "_c.tif";
        label_out += saved_name + "\n";
        fif = FreeImage_GetFileType(image_name_path.toStdString().c_str());
        handled_image = FreeImage_Load(fif, image_name_path.toStdString().c_str());
        FreeImage_Save(FIF_TIFF, handled_image, saved_name.toStdString().c_str(), TIFF_LZW);
        FreeImage_Unload(handled_image);
    }
//    ui.label->setText(label_out);
    FreeImage_DeInitialise();

}


// 十六位的，6层数据， 原来18.6G， 压缩后6.3G， 用时34.12s