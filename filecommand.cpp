#include "filecommand.h"

void create(string message, struct filesystem fs) {
    vector<string> strings = takeArgs(message);

    if (strings.size() != 1) {
        cout<<"wrong command\n";
        return;
    }

    if (regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        string filename = strings[0].substr(1, strings[0].length() - 2);

        if (isFileExist(filename, fs)) {
            cout << filename << " already exist\n";
            return;
        }

        if (isFreeBlockExist(fs)) {
            ////
        } else {
            cout << "filesystem is completed\n";
            return;
        }

    } else {
        cout<<"wrong filename: "<<strings[0]<<endl;
        return;
    }
}

void remove() {

}

void copy() {

}

void move() {

}

void write() {

}

void read() {

}

void exit() {
    exit(0);
}