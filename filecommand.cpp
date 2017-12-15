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

void remove(string message, struct filesystem fs) {
    vector<string> strings = takeArgs(message);

    if (strings.size() != 1) {
        cout<<"wrong command\n";
        return;
    }

    if (!regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        cout<<"wrong filename: "<<strings[0]<<endl;
        return;
    }

    string filename = strings[0].substr(1, strings[0].length() - 2);

    if (!isFileExist(filename, fs)) {
        cout << filename << " doesn't exist\n";
        return;
    }

    //// search header
    /////// recursive delete
}

void copy(string message, struct filesystem fs) {

}

void move(string message, struct filesystem fs) {

}

void write(string message, struct filesystem fs) {

}

void read(string message, struct filesystem fs) {

}