#ifndef FILESYSTEM_COMMONFUNC_H
#define FILESYSTEM_COMMONFUNC_H

#include <iostream>
#include "structHeader.h"
using namespace std;

vector<string> takeArgs(string message);
bool isFileExist(string filename, struct filesystem fs);
bool isFreeBlockExist(struct filesystem fs);

#endif
