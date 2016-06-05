#include "pre_map.h"

pre_map::pre_map(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags), args_checked(false)
{
    ui.setupUi(this);
    timer1 = new QTimer(this);
    timer1->setInterval(1000);
    timer2 = new QTimer(this);
    timer2->setInterval(100);    
    time = new QTime();
    msg_index = 0;
    msg_list = new vector<QString>();
    ct = new CheckThread();
    wt = new WorkThread();
    connect(timer1, SIGNAL(timeout()), this, SLOT(display_time()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(display_msg()));
    //connect(this, SIGNAL(msg_list_changed()), this, SLOT(on_msg_list_changed()));
}

pre_map::~pre_map()
{
    //omp_destroy_lock(lock1);
    //delete lock1;
    delete timer1;
    delete timer2;
    delete time;
    delete msg_list;
    delete ct;
    delete wt;
}

void pre_map::display_msg(){
    int msg_num = msg_list->size();
    if(msg_index < msg_num){
        QString showed_msg = msg_list->at(msg_index);
        ui.textEdit->append(showed_msg);
        ++msg_index;  
    }
}

void pre_map::on_actionSrc_triggered(){
    QFileDialog *src_dialog;
    src_dir = src_dialog->getExistingDirectory(this, tr("Open Directory"), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + "\\";
    ui.textEdit->append("Image Src: " + src_dir);
}

void pre_map::on_actionDst_triggered(){
    QFileDialog *dst_dialog;
    dst_dir = dst_dialog->getExistingDirectory(this, tr("Open Directory"), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + "\\";
    ui.textEdit->append("Image Dst: "+dst_dir);
}

void pre_map::display_time(){
    ui.lcdNumber->display(time->elapsed()/1000);
}

void pre_map::on_pushButton_clicked(){
    if(args_checked){
        ui.pushButton->setDisabled(true);
        ui.textEdit->append("Yes");
        time->start();
        timer1->start();
        timer2->start();
        go2Work(); 
        //args_checked = false;
        //ui.pushButton->setEnabled(true);
        //ui.pushButton->setText("Check Files");
    }else{
        ui.textEdit->clear();
        args_checked = true;
        image_pre = ui.lineEdit->text();
        image_suf = ui.lineEdit_2->text();
        if(src_dir.isEmpty()){
            ui.textEdit->append(tr("Please Choose Raw Image File!"));
            args_checked = false;
        }
        if(dst_dir.isEmpty()){
            ui.textEdit->append(tr("Please Choose Dst Image File!"));
            args_checked = false;
        }
        if(image_pre.isEmpty()){
            ui.textEdit->append(tr("Please Set Image Pre-name!"));
            args_checked = false;
        }
        if(image_suf.isEmpty()){
            ui.textEdit->append(tr("Please Set Image Suf-name!"));
            args_checked = false;
        }
        bool ok;
        start_serial = ui.lineEdit_3->text().toUInt(&ok);
        if(ok != true){
            ui.textEdit->append(tr("Start Serial Not Correct!"));
            args_checked = false;
        }
        end_serial = ui.lineEdit_4->text().toUInt(&ok);
        if(ok != true){
            ui.textEdit->append(tr("End Serial Not Correct!"));
            args_checked = false;
        }        
        pro_thick = ui.lineEdit_5->text().toUInt(&ok);
        if(ok != true){
            ui.textEdit->append(tr("Project Thickness Not Correct!"));
            args_checked = false;
        }          
        thread_num = ui.lineEdit_6->text().toUInt(&ok);
        if(ok != true){
            ui.textEdit->append(tr("Thread Number Not Correct!"));
            args_checked = false;
        }             
        ball_radius = ui.lineEdit_7->text().toUInt(&ok);
        if(ok != true){
            ui.textEdit->append(tr("Ball Radius Not Correct!"));
            args_checked = false;
        } 
        resize_ratio = ui.lineEdit_8->text().toFloat(&ok);
        if(ok != true){
            ui.textEdit->append(tr("Resize Ratio Not Correct!"));
            args_checked = false;
        }
        high_brightness = ui.lineEdit_9->text().toUInt(&ok);
        if(ok != true){
            ui.textEdit->append(tr("Brightness Not Correct!"));
            args_checked = false;
        }        
        if(args_checked == true){
            ui.textEdit->clear();
            if(start_serial > end_serial){
                ui.textEdit->append(tr("Start Serial Beyond End Serial!"));
                args_checked = false;
            }
            if(resize_ratio > 1.0 || resize_ratio < 0){
                ui.textEdit->append(tr("Resize Ratio Out Of Range!"));
                args_checked = false;
            }
            if(ball_radius < 0){
                ui.textEdit->append(tr("Ball Radius should be larger than 0!"));
                args_checked = false;
            }
            vector<QString> lostImages;
            checkImageNames(lostImages);
            if(!lostImages.empty()){
                ui.textEdit->append(tr("--------------Images Do Not Exist!-----------------"));
                for(vector<QString>::size_type i = 0; i < lostImages.size(); ++i){
                    ui.textEdit->append(lostImages[i]);
                }
                ui.textEdit->append(tr("--------------Images Do Not Exist!-----------------"));
                args_checked = false;
            }
        }
        if(args_checked == true){
            ui.textEdit->clear();
            ui.textEdit->append("Already To Work!");
            ui.pushButton->setText("Work");
        }             
    }
    
}

void pre_map::checkImageNames(vector<QString> &lostImageNames){
    ct->setArgs(src_dir, start_serial, end_serial, &lostImageNames, image_pre, image_suf);
    ct->start();
    ct->wait();
}

void CheckThread::setArgs(QString src, uint s_serial, uint e_serial, std::vector<QString> *lost_list, QString pre, QString suf){
    src_dir = src;
    start_serial = s_serial;
    end_serial = e_serial;
    lostImageNames = lost_list;
    img_pre = pre;
    img_suf = suf;
}


void CheckThread::run(){
    QDir src_qdir(src_dir);
    int base = 10;
    QChar filledChar('0');
    omp_lock_t lock1;
    omp_init_lock(&lock1);
#pragma omp parallel for num_threads(6)
    for(int serial_i = static_cast<int>(start_serial); serial_i <= static_cast<int>(end_serial); ++ serial_i){
        QString image_i_name = QString("%1%2%3").arg(img_pre).arg(serial_i, 5, base, filledChar).arg(img_suf);
        omp_set_lock(&lock1);
        qDebug()<<image_i_name;
        if(!src_qdir.exists(image_i_name)){
            lostImageNames->push_back(image_i_name);
        }
        omp_unset_lock(&lock1);
    }
    omp_destroy_lock(&lock1);
}

void WorkThread::setArgs(QString arg1, QString arg2, QString arg3, QString arg4, uint arg5, uint arg6, uint arg7, uint arg8, float arg9, vector<QString> *arg10, uint arg11, uint arg12){
    image_pre = arg1;
    image_suf = arg2;
    src_dir = arg3;
    dst_dir = arg4;
    start_serial = arg5;
    end_serial = arg6;
    pro_thick = arg7;
    thread_num = arg8;
    resize_ratio = arg9;
    msg_list = arg10;
    ball_radius = arg11;
    high_brightness = arg12;
}


void WorkThread::run(){
    vector<vector<QString>> work_pool(thread_num);
    uint image_num = end_serial - start_serial + 1;
    uint worker = 0;
    uint thick_index = 1;
    int base = 10;
    QChar filled('0');
    int width = 5;
    omp_lock_t lock1;
    omp_init_lock(&lock1);
    for(int i = 0; i < static_cast<int>(image_num); ++i){
        if(thick_index > pro_thick){
            thick_index = 1;
            ++worker;
            if(worker > thread_num - 1){
                worker = 0;
            }
        }
        QString image_name = QString("%1%2%3").arg(image_pre).arg(start_serial + i, width, base, filled).arg(image_suf);
        work_pool[worker].push_back(image_name);
        ++thick_index;
    }
#pragma omp parallel for num_threads(thread_num)
//    for(int i = 0; i < 100; ++i){
//        QTest::qSleep(1000);
//        omp_set_lock(&lock1);
//        msg_list->push_back("ssssss");
//        //myWidget->appendMsgList();
//        omp_unset_lock(&lock1); 
//    }
    for(int i = 0; i < static_cast<int>(thread_num); ++i){
        uint thick_index = 1;
        cv::Mat out_image;
        for(int k = 0; k < work_pool[i].size(); ++k){
            QString name_k = src_dir + work_pool[i][k];
            QString name_iamge = work_pool[i][k];
            int tn = omp_get_thread_num();
            cv::Mat in_image = cv::imread(name_k.toStdString(), CV_LOAD_IMAGE_UNCHANGED);
            if(in_image.data){
                omp_set_lock(&lock1);
                QString tmp_msg1 = QString("Projecting: ") + name_iamge + QString(" in thread_%1").arg(tn);
                msg_list->push_back(tmp_msg1);
                omp_unset_lock(&lock1);
                if(k == 0){
                    out_image = cv::Mat::zeros(in_image.rows, in_image.cols, in_image.type());
                }
                cv::max(in_image, out_image, out_image);
                if(thick_index == pro_thick || k == work_pool[i].size() - 1){
                    int out_image_serial = i + (k / pro_thick) * thread_num;   
                    QString out_image_name = QString("%1test_%2_sub.tif").arg(dst_dir).arg(out_image_serial, width, base, filled);
                    omp_set_lock(&lock1);
                    msg_list->push_back(QString("Outing: test_%1_sub.tif in thread_%2").arg(out_image_serial, width, base, filled).arg(tn));
                    omp_unset_lock(&lock1);
                    if(ball_radius != 0){
                        Subbor tmp_sub(out_image, ball_radius);
                    }
                    if(high_brightness != 0){
                        int high_out;
                        if(in_image.type() == CV_8U){
                            high_out = 255;
                        }else if(in_image.type() == CV_16U){
                            high_out = 4095;
                        }
                        if(high_brightness < high_out){
                            TestImAdjust(out_image, 0, high_brightness, 0, high_out);
                        }
                    }
                    cv::Mat tmp_image;
                    cv::resize(out_image, tmp_image, cv::Size(), resize_ratio, resize_ratio, cv::INTER_AREA);
                    cv::imwrite(out_image_name.toStdString(), tmp_image);
                    out_image = cv::Mat::zeros(in_image.rows, in_image.cols, in_image.type());
                    thick_index = 1;
                }else{
                    ++thick_index;
                }
            }else{
                    omp_set_lock(&lock1);
                    msg_list->push_back(QString("Error in reading ") + name_iamge);
                    omp_unset_lock(&lock1);
            }
        }
    }
    omp_set_lock(&lock1);
    msg_list->push_back(QString("------------Done-------------"));
    omp_unset_lock(&lock1);    
    omp_destroy_lock(&lock1);
}

void pre_map::go2Work(){
    ui.textEdit->clear();
    wt->setArgs(image_pre, image_suf, src_dir, dst_dir, start_serial, end_serial, pro_thick, thread_num, resize_ratio, msg_list, ball_radius, high_brightness);
    wt->start();
}


//    vector<vector<QString>> work_pool(thread_num);
//    uint image_num = end_serial - start_serial + 1;
//    uint worker = 0;
//    uint thick_index = 1;
//    int base = 10;
//    QChar filled('0');
//    int width = 5;
//    omp_lock_t lock1;
//    omp_init_lock(&lock1);
//    for(int i = 0; i < static_cast<int>(image_num); ++i){
//        if(thick_index > pro_thick){
//            thick_index = 1;
//            ++worker;
//            if(worker > thread_num - 1){
//                worker = 0;
//            }
//        }
//        QString image_name = QString("%1%2%3").arg(image_pre).arg(start_serial + i, width, base, filled).arg(image_suf);
//        work_pool[worker].push_back(image_name);
//        ++thick_index;
//    }
//#pragma omp parallel for num_threads(thread_num)
//    for(int i = 0; i < static_cast<int>(thread_num); ++i){
//        uint thick_index = 1;
//        cv::Mat out_image;
//        for(int k = 0; k < work_pool[i].size(); ++k){
//            QString name_k = src_dir + work_pool[i][k];   
//            cv::Mat in_image = cv::imread(name_k.toStdString(), CV_LOAD_IMAGE_UNCHANGED);
//            if(in_image.data){
//                omp_set_lock(&lock1);
//                ui.textEdit->append(QString("Projecting: ") + work_pool[i][k] + QString(" in thread %1, thick index is %2.").arg(omp_get_thread_num()).arg(thick_index));
//                omp_unset_lock(&lock1);
//                if(k == 0){
//                    out_image = cv::Mat::zeros(in_image.rows, in_image.cols, in_image.type());
//                }
//                cv::max(in_image, out_image, out_image);
//                if(thick_index == pro_thick || k == work_pool[i].size() - 1){
//                    int out_image_serial = i + (k / pro_thick) * thread_num;   
//                    QString out_image_name = QString("%1test_%2_sub.tif").arg(dst_dir).arg(out_image_serial, width, base, filled);
//                    //omp_set_lock(&lock1);
//                    //ui.textEdit->append(QString("Outing: ") + out_image_name + " " + work_pool[i][k] + QString(" in thread %1, thick index is %2.").arg(omp_get_thread_num()).arg(thick_index));
//                    //omp_unset_lock(&lock1);
//                    if(ball_radius != 0){
//                        Subbor tmp_sub(out_image, ball_radius);
//                    }
//                    cv::Mat tmp_image;
//                    cv::resize(out_image, tmp_image, cv::Size(), resize_ratio, resize_ratio, cv::INTER_AREA);
//                    cv::imwrite(out_image_name.toStdString(), tmp_image);
//                    out_image = cv::Mat::zeros(in_image.rows, in_image.cols, in_image.type());
//                    thick_index = 1;
//                }else{
//                    ++thick_index;
//                }
//            }else{
//                    omp_set_lock(&lock1);
//                    ui.textEdit->append(QString("Error in reading ") + name_k);
//                    omp_unset_lock(&lock1);
//            }
//        }
//    }
//    omp_destroy_lock(&lock1);