#include <boost/algorithm/string/classification.hpp>
#include "commonfunc.h"

vector<string> takeArgs(string message) {
    vector<string> strings;
    boost::split(strings, message, boost::is_any_of(" "));
    return strings;
}

bool isFileExist(string filename, struct filesystem fs) {
    bool result = false;
    string fileSystemName = fs.fileSystemName;
    int fd = open(fileSystemName.c_str(), O_RDWR);
    int len = lseek(fd, 0, SEEK_END);

    int index = 0;
    while (index < len / 2) {
        block b;
        lseek(fd, index, SEEK_SET);
        read(fd, &b, sizeof(b));

        descriptor d;
        memcpy(&d, &b.value, BLOCK_SIZE);

        if (d.isFree == false) {
            if (strcmp(d.filename, filename.c_str()) == 0) {
                result = true;
                break;
            }
        }

        index += sizeof(b);
    }

    close(fd);
    return result;
}

bool isFreeFileExist(struct filesystem fs) {
    bool result = false;
    string fileSystemName = fs.fileSystemName;
    int fd = open(fileSystemName.c_str(), O_RDWR);
    int len = lseek(fd, 0, SEEK_END);

    int index = 0;
    while (index < len / 2) {
        block b;
        lseek(fd, index, SEEK_SET);
        read(fd, &b, sizeof(b));

        descriptor d;
        memcpy(&d, &b.value, BLOCK_SIZE);

        if (d.isFree == true) {
            result = true;
            break;
        }

        index += sizeof(b);
    }

    close(fd);
    return result;
}

void removeFunc(string filename, struct filesystem fs) {
    string fileSystemName = fs.fileSystemName;
    int fd = open(fileSystemName.c_str(), O_RDWR);
    int len = lseek(fd, 0, SEEK_END);

    int index = 0;
    descriptor findDesc;
    block findBlock;
    while (index < len / 2) {
        block b;
        lseek(fd, index, SEEK_SET);
        read(fd, &b, sizeof(b));

        descriptor d;
        memcpy(&d, &b.value, BLOCK_SIZE);

        if (d.isFree == false) {
            if (strcmp(d.filename, filename.c_str()) == 0) {
                findDesc = d;
                findBlock = b;
                break;
            }
        }

        index += sizeof(b);
    }

    findDesc.isFree = true;
    if (findDesc.firstBlockIndex == EMPTY_FILE) {
        memcpy(&findBlock.value, &findDesc, BLOCK_SIZE);
        lseek(fd, index, SEEK_SET);
        write(fd, &findBlock, sizeof(findBlock));
        close(fd);
        return;
    } else {
        int firstBlockIndex = findDesc.firstBlockIndex;
        findDesc.firstBlockIndex = EMPTY_FILE;
        memcpy(&findBlock.value, &findDesc, BLOCK_SIZE);
        lseek(fd, index, SEEK_SET);
        write(fd, &findBlock, sizeof(findBlock));
        close(fd);
        clearBlockFunc(firstBlockIndex, fs);
        return;
    }
}

void clearBlockFunc(int firstBlockIndex, struct filesystem fs) {
    string fileSystemName = fs.fileSystemName;
    int fd = open(fileSystemName.c_str(), O_RDWR);
    int len = lseek(fd, 0, SEEK_END);

    int index = len / 2;
    while (index < len) {
        block b;
        lseek(fd, index, SEEK_SET);
        read(fd, &b, sizeof(b));

        if (b.blockIndex == firstBlockIndex) {
            b.freeSpace = FREE_BLOCK;
            if (b.nextBlockIndex == LAST_BLOCK) {
                lseek(fd, index, SEEK_SET);
                write(fd, &b, sizeof(b));
                close(fd);
                return;
            } else {
                firstBlockIndex = b.nextBlockIndex;
                b.nextBlockIndex = LAST_BLOCK;
                lseek(fd, index, SEEK_SET);
                write(fd, &b, sizeof(b));
                index = len / 2;
                continue;
            }
        }

        index += sizeof(b);
    }
    close(fd);
}

void writeFunc(string filename, string message, struct filesystem fs) {
    string fileSystemName = fs.fileSystemName;
    int fd = open(fileSystemName.c_str(), O_RDWR);
    int len = lseek(fd, 0, SEEK_END);

    int index = 0;
    int firstBlockIndex;
    block b;
    descriptor d;

    while (index < len / 2) {
        lseek(fd, index, SEEK_SET);
        read(fd, &b, sizeof(b));
        memcpy(&d, &b.value, BLOCK_SIZE);
        if (d.isFree == false) {
            if (strcmp(d.filename, filename.c_str()) == 0) {
                firstBlockIndex = d.firstBlockIndex;
                break;
            }
        }
        index += sizeof(b);
    }
    close(fd);

    if (firstBlockIndex == EMPTY_FILE) {
        int offset = findFreeBlock(fs);
        if (offset == -1) {
            cout << "filesystem is completed\n";
            return;
        } else {
            fd = open(fileSystemName.c_str(), O_RDWR);
            block firstBlock;
            lseek(fd, offset, SEEK_SET);
            read(fd, &firstBlock, sizeof(firstBlock));
            firstBlockIndex = firstBlock.blockIndex;
            d.firstBlockIndex = firstBlockIndex;
            memcpy(&b.value, &d, BLOCK_SIZE);
            lseek(fd, index, SEEK_SET);
            write(fd, &b, sizeof(b));
            close(fd);
        }
    }

    write(message, message.length(), message.length(), firstBlockIndex, fs);



////
////
////
////
////
////
////    /////////////////////
////
////    block prevBlock;
////    if (firstBlockIndex == LAST_BLOCK) {
////        int offset = findFreeBlock(fs);
////        if (offset == -1) {
////            cout << "filesystem is completed\n";
////            return;
////        } else {
////            fd = open(fileSystemName.c_str(), O_RDWR);
////            block firstBlock;
////            lseek(fd, offset, SEEK_SET);
////            read(fd, &firstBlock, sizeof(firstBlock));
////
////            firstBlockIndex = firstBlock.blockIndex;
////            d.firstBlockIndex = firstBlockIndex;
////            memcpy(&b.value, &d, BLOCK_SIZE);
////            lseek(fd, index, SEEK_SET);
////            write(fd, &b, sizeof(b));
////            close(fd);
////            prevBlock = firstBlock;
////        }
////    } else {
////        fd = open(fileSystemName.c_str(), O_RDWR);
////        index = len / 2;
////        while (index < len) {
////            lseek(fd, index, SEEK_SET);
////            read(fd, &prevBlock, sizeof(prevBlock));
////            if (prevBlock.blockIndex == firstBlockIndex) {
////                break;
////            }
////            index += sizeof(prevBlock);
////        }
////        close(fd);
//    }
//
//    int messageLength = message.length();
//    int remainBytes = message.length();
//    while (remainBytes != 0) {
//        char ch = message.c_str()[messageLength - remainBytes];
//
//
//    }
}

int findFreeBlock(struct filesystem fs) {
    string fileSystemName = fs.fileSystemName;
    int fd = open(fileSystemName.c_str(), O_RDWR);
    int len = lseek(fd, 0, SEEK_END);

    int index = len / 2;
    while (index < len) {
        block b;
        lseek(fd, index, SEEK_SET);
        read(fd, &b, sizeof(b));
        if (b.freeSpace == FREE_BLOCK) {
            close(fd);
            return index;
        }
        index += sizeof(b);
    }
    close(fd);
    return -1;
}

void write(string message, int mesLen, int remainLen, int blocIndex, struct filesystem fs) {
    string fileSystemName = fs.fileSystemName;
    int fd = open(fileSystemName.c_str(), O_RDWR);
    int len = lseek(fd, 0, SEEK_END);

    int index = len / 2;
    block b;
    while (index < len) {
        lseek(fd, index, SEEK_SET);
        read(fd, &b, sizeof(b));
        if (b.blockIndex == blocIndex) {
            break;
        }
        index += sizeof(b);
    }

    while (b.freeSpace > 0 || remainLen != 0) {
        string s;
        s.append(b.value);
        s += message.c_str()[mesLen - remainLen];
        remainLen--;
        b.freeSpace--;
        memcpy(&b.value, s.c_str(), sizeof(s.c_str()));
        lseek(fd, index, SEEK_SET);
        write(fd, &b, sizeof(b));
    }

    if (remainLen == 0) {
        cout<<"written successful\n";
        return;
    }
    close(fd);

    if (b.nextBlockIndex != LAST_BLOCK) {
        write(message, mesLen, remainLen, b.nextBlockIndex, fs);
    } else {
        int offset = findFreeBlock(fs);
        if (offset == -1) {
            cout << "filesystem is completed: was written\copied not all data\n";
            return;
        } else {
            fd = open(fileSystemName.c_str(), O_RDWR);
            block nextBlock;
            lseek(fd, offset, SEEK_SET);
            read(fd, &nextBlock, sizeof(nextBlock));
            b.nextBlockIndex = nextBlock.blockIndex;
            lseek(fd, index, SEEK_SET);
            write(fd, &b, sizeof(b));
            close(fd);
            write(message, mesLen, remainLen, nextBlock.blockIndex, fs);
        }
    }
}