#ifndef FILESYSTEM_COMMONFUNC_H
#define FILESYSTEM_COMMONFUNC_H

#include <iostream>
#include "structHeader.h"
using namespace std;

vector<string> takeArgs(string message);
bool isFileExist(string filename, struct filesystem fs);
bool isFreeFileExist(struct filesystem fs);
void removeFunc(string filename, struct filesystem fs);
void clearBlockFunc(int firstBlockIndex, struct filesystem fs);

#endif