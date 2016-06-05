
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <direct.h>

#include <io.h>
using namespace std;


class Tar{
public:
    Tar(string tar_name);
    ~Tar();

    fstream tar_file;
    string dst;
    int file_num;
    bool can_handle;
    vector<string> file_names;
    int get_file_num();
    string tar_name;
    string get_file_name(unsigned int  i);
    bool is_end_of_tar(char *b, streampos p);
    bool is_tar_file(char *b);
    void untar(string ds);
    string sys_del;    
};