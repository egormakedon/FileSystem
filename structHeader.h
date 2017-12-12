#ifndef FILESYSTEM_STRUCTHEADER_H
#define FILESYSTEM_STRUCTHEADER_H

#include <iostream>
#include <cstring>
#include <string>
#include "init.h"
#include "load.h"
#include <regex>
#include <fstream>
#include "filecommand.h"
#include <boost/algorithm/string.hpp>
using namespace std;

struct filesystem {
    string fileSystemName = "";
};

struct header {
    int size;
    int freeSize;
    struct fileDescriptor* descriptors;
};

struct fileDescriptor {
    string filename = "";
    int firstBlock;
};

struct fileblock {
    int blockNum;
    int nextBlockNum = -1;
    int size = 5;
    char info[5];
};

#endif