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

        if (strcmp(d.filename, filename.c_str()) == 0) {
            result = true;
            break;
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