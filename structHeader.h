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
#include <sys/io.h>
#include <stdio.h>
#include <fcntl.h>
#include "commonfunc.h"
using namespace std;

const int MAX_FILENAME_LENGTH = 6;
const int BLOCK_SIZE = 16;
const string FILE_NAME_REGEXP = "\".{1,10}\"";
const string DATA_MESSAGE_REGEXP = "\".+\"";

#define EMPTY_FILE -2
#define LAST_BLOCK -1
#define FREE_BLOCK BLOCK_SIZE

struct filesystem {
    string fileSystemName = "";
};

struct descriptor {
    char filename[MAX_FILENAME_LENGTH];
    int firstBlockIndex = EMPTY_FILE;
    bool isFree = true;
};

struct block {
    int blockIndex;
    int nextBlockIndex = LAST_BLOCK;
    char value[BLOCK_SIZE];
    int freeSpace = FREE_BLOCK;
};

#endif