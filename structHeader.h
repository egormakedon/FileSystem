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

const int MAX_FILENAME_LENGTH = 6;
const int BLOCK_SIZE = 16;

struct filesystem {
    string fileSystemName = "";
};

struct descriptor {
    char filename[MAX_FILENAME_LENGTH];
    int firstBlockIndex;
    bool isFree = true;
};

struct block {
    int blockIndex;
    int nextBlockIndex;
    char value[BLOCK_SIZE];
};

#endif