
#include "my_tar.h"

bool Tar::is_end_of_tar(char *b, streampos p){
//    cout<<p<<endl;
    int n = 512;
    for(int i = 0; i < n; i ++){
        if(b[i] != '\0'){
            return false;
        }
    }
    char buffer[512];
    tar_file.read(buffer, 512);
    for(int i = 0; i < n; i ++){
        if(buffer[i] != '\0'){
            tar_file.seekg(p);
            return false;
        }
    }
    return true;
}

bool Tar::is_tar_file(char *b){
    unsigned int count_sum = 0;
    for(unsigned int i = 0; i < 512; ++i){
        if(i >= 148 && i <= 155){
            count_sum += 32;
        }else{
            count_sum += static_cast<unsigned int>(b[i]);
        }
    }
//    cout<<count_sum<<endl;
    char chksum[8];
    for(unsigned int i = 0; i < 512; ++i){
        if(i >= 148 && i <= 155){
            chksum[i - 148] = b[i];
        }
    }
    unsigned int raw_sum;
    sscanf(chksum, "%o", &raw_sum);
//    cout<<raw_sum<<endl;
    if(raw_sum == count_sum){
        return true;
    }else{
        return false;
    }
}

Tar::Tar(string name1): dst(""), sys_del("\\"){
 //   cout<<name<<endl;
    /*file_names.insert(file_names.begin(), "ssss");*/
    tar_name = name1;
    char buffer[512];
    string::size_type get_bytes_num;
//    cout<<name<<endl;
    tar_file.open(name1.c_str(), ios::in | ios::binary);
    if(tar_file.good()){
        tar_file.read(buffer, 512);
        if(is_tar_file(buffer)){
            can_handle = true;
            while(true){
                get_bytes_num = tar_file.gcount();
//                cout<<get_bytes_num<<endl;
                if(get_bytes_num != 512){
                    cout<<"read error!"<<endl;
                    break;
                }
                if(is_end_of_tar(buffer, tar_file.tellg())){
 //                   cout<<"The End!"<<endl;
                    break;   
                }else{
                    char name[100];
                    char size[12];
                    char chksum[8];
                    char magic[6];
                    char typeflag;
                    for(int i = 0; i < 512; ++i){
                        if(i >= 0 && i <= 99){
                            name[i] = buffer[i];
                        }else if(i >= 124 && i <= 135){
                            size[i - 124] = buffer[i];
                        }else if(i >= 148 && i <= 155){
                            chksum[i - 148] = buffer[i];
                        }else if(i >= 257 && i <=262){
                            magic[i - 257] = buffer[i];
                        }else if(i == 156){
                            typeflag = buffer[i];
                        }
                    }
                    int size_num;
                    sscanf(size, "%o", &size_num);
                    switch(typeflag){
                        case '5':
                            size_num = 0;
                            break;
                        case '0':
                        case '\0':
                            can_handle = true;
                            break;
                        default:
                            can_handle = false;
                            cout<<"Can not handle!"<<endl;
                            break;
                    }
                    if(can_handle == false){
                        break;
                    }
                    if(size_num == 0){
                    }else{
                        string name_string(name);
                        file_names.push_back(name_string);
                        int block_512_num = size_num / 512 + 1;
                        for(int i = 0; i < block_512_num; ++i){
                            tar_file.read(buffer, 512);
                            get_bytes_num = tar_file.gcount();
                            if(get_bytes_num != 512){
                                cout<<"read error!"<<endl;
                                break;
                            }
                        }
                    }
                    tar_file.read(buffer, 512);
                }
            }
//            cout<<file_names.size()<<endl;
/*            for(vector<string>::iterator iter = file_names.begin(); iter != file_names.end(); ++iter){
                cout<<*iter<<endl;
            }   */       
        }else{
            cout<<"This is not a tar file!"<<endl;
        }
    }else{
        cout<<"Bad file."<<endl;
    }
    tar_file.close();
}



void Tar::untar(string ds){
    if(can_handle == false){
        cout<<"Sorry, can not handle!"<<endl;
        return;
    }
    dst = ds;
    char buffer[512];
    string::size_type get_bytes_num;
    tar_file.open(tar_name.c_str(), ios::in | ios::binary);
    string whole_file_name = tar_name.substr(0, tar_name.size() - 4);
    if(_access(dst.c_str(), 0) == -1){
        cout<<"Create Folder"<< " "<<whole_file_name<<endl;
        _mkdir(dst.c_str());
    }    
    if(tar_file.good()){
        tar_file.read(buffer, 512);
        if(is_tar_file(buffer)){
            while(true){
                get_bytes_num = tar_file.gcount();
                if(get_bytes_num != 512){
                    cout<<"read error!"<<endl;
                    break;
                }
                if(is_end_of_tar(buffer, tar_file.tellg())){
                    break;   
                }else{
                    char name[100];
                    char size[12];
                    char chksum[8];
                    char magic[6];
                    char typeflag;
                    for(int i = 0; i < 512; ++i){
                        if(i >= 0 && i <= 99){
                            name[i] = buffer[i];
                        }else if(i >= 124 && i <= 135){
                            size[i - 124] = buffer[i];
                        }else if(i >= 148 && i <= 155){
                            chksum[i - 148] = buffer[i];
                        }else if(i >= 257 && i <=262){
                            magic[i - 257] = buffer[i];
                        }else if(i == 156){
                            typeflag = buffer[i];
                        }
                    }
                    int size_num;
                    sscanf(size, "%o", &size_num);
                    switch(typeflag){
                        case '5':
                            size_num = 0;
                            break;
                        case '0':
                        case '\0':
                            can_handle = true;
                            break;
                        default:
                            can_handle = false;
                            break;
                    }
                    if(size_num == 0){
                        cout<<"Dir: "<<" "<<name<<endl;
                        string this_file_name(name);
                        string this_file_path = dst + sys_del + this_file_name;
                        if(_access(this_file_path.c_str(), 0) == -1){
                            cout<<"Create Folder"<< " "<<this_file_path<<endl;
                            _mkdir(this_file_path.c_str());
                        }
                    }else{
                        string name_string(name);
                        
                        string this_file_path = dst + sys_del + name_string;
//                        cout<<"File: "<<this_file_path<<endl;
                        fstream this_file(this_file_path.c_str(), ios::out | ios::binary);                        
                        int block_512_num = size_num / 512 + 1;
                        int saved_size_num = 0;
                        int should_be_saved_bytes = 512;
                        for(int i = 0; i < block_512_num; ++i){
                            tar_file.read(buffer, 512);
                            get_bytes_num = tar_file.gcount();
                            if(get_bytes_num != 512){
                                cout<<"read error!"<<endl;
                                break;
                            }
                            if(size_num - saved_size_num < 512){
                                should_be_saved_bytes = size_num - saved_size_num;
                            }else{
                                should_be_saved_bytes = 512;
                            }
                            this_file.write(buffer, should_be_saved_bytes);
                            saved_size_num += should_be_saved_bytes;
                        }
                        this_file.close();
                    }
                    tar_file.read(buffer, 512);
                }
            }
        }else{
            cout<<"This is not a tar file!"<<endl;
        }
    }else{
        cout<<"Bad file."<<endl;
    }
    tar_file.close();
}

string Tar::get_file_name(unsigned int i){
    if(i > file_names.size() || i < 0){
        cout<<"Bad Index!"<<endl;
        return " ";
    }else{
       return file_names.at(i);
    }
}

int Tar::get_file_num(){
    if(can_handle){
        return file_names.size();
    }else{
        return -1;
    }

}



Tar::~Tar(){
}





//void main(){
//    Tar a("eeeee.tar");
//    a.untar();
//    cin.ignore();
//}