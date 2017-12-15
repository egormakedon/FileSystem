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