#ifndef FILESYSTEM_FILECOMMAND_H
#define FILESYSTEM_FILECOMMAND_H

#include "structHeader.h"
#include <iostream>
using namespace std;

void create(string message, struct filesystem fs);
void remove();
void copy();
void move();
void write();
void read();
void exit();

#endif