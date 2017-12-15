#include <boost/algorithm/string/classification.hpp>
#include "commonfunc.h"

void readFileSystem(struct filesystem fs) {
    string fileSystemName = fs.fileSystemName;

    int fd = open(fileSystemName.c_str(), O_RDWR);
    block result;
    lseek(fd, 0, SEEK_SET);
    read(fd, &result, 28);
    cout<<endl<<"index: "<<result.blockIndex<<endl;

    read(fd, &result, 28);
    cout<<endl<<"index: "<<result.blockIndex<<endl;

//    FILE *file = fopen(fileSystemName.c_str(), "r+b");
//    fseek(file,0,SEEK_END);
//    int length=ftell(file);
//    fclose(file);
//
//    ifstream fin(fileSystemName, ios_base::binary);
//    char buffer[length];
//    fin.read(buffer, sizeof(char));
//    fin.close();
//    cout<<sizeof(buffer);
}

vector<string> takeArgs(string message) {
    vector<string> strings;
    boost::split(strings, message, boost::is_any_of(" "));
    return strings;
}

bool isFileExist(string filename, struct filesystem fs) {
    readFileSystem(fs);
}

bool isFreeFileExist(struct filesystem fs) {
    ////
}

