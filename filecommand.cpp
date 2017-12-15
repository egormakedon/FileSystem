#include "filecommand.h"

void create(string message, struct filesystem fs) {
    vector<string> strings = takeArgs(message);

    if (strings.size() != 1) {
        cout << "wrong command\n";
        return;
    }

    if (!regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        cout << "wrong filename: " << strings[0] << endl;
        return;
    }

    string filename = strings[0].substr(1, strings[0].length() - 2);

    if (isFileExist(filename, fs)) {
        cout << filename << " already exist\n";
        return;
    }

    if (!isFreeFileExist(fs)) {
        cout << "filesystem is completed\n";
        return;
    }

    //////
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

    if (!isFreeFileExist(fs)) {
        cout << "filesystem is completed\n";
        return;
    }

    //// проверка на имя, сначала получить всю инфу с файла, проверит хватает ли места для копирования, копировать
}

void move(string message, struct filesystem fs) {
    vector<string> strings = takeArgs(message);

    if (strings.size() != 2) {
        cout<<"wrong command\n";
        return;
    }

    if (!regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        cout<<"wrong filename: "<<strings[0]<<endl;
        return;
    }

    if (!regex_match(strings[1], regex(FILE_NAME_REGEXP))) {
        cout<<"wrong filename: "<<strings[1]<<endl;
        return;
    }

    string filename = strings[0].substr(1, strings[0].length() - 2);
    string newFileName = strings[1].substr(1, strings[1].length() - 2);

    if (!isFileExist(filename, fs)) {
        cout << filename << " doesn't exist\n";
        return;
    }

    if (isFileExist(newFileName, fs)) {
        cout << filename << " already exist\n";
        return;
    }

    //// изменить имя
}

void write(string message, struct filesystem fs) {
    vector<string> strings = takeArgs(message);

    if (strings.size() != 2) {
        cout<<"wrong command\n";
        return;
    }

    if (!regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        cout << "wrong filename: " << strings[0] << endl;
        return;
    }

    if (!regex_match(strings[1], regex(DATA_MESSAGE_REGEXP))) {
        cout << "wrong input data: " << strings[1] << endl;
        return;
    }

    string filename = strings[0].substr(1, strings[0].length() - 2);

    if (!isFileExist(filename, fs)) {
        cout << filename << " doesn't exist\n";
        return;
    }

    //// kak v copy
}

void read(string message, struct filesystem fs) {
    vector<string> strings = takeArgs(message);

    if (strings.size() != 1) {
        cout<<"wrong command\n";
        return;
    }

    if (!regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        cout << "wrong filename: " << strings[0] << endl;
        return;
    }

    string filename = strings[0].substr(1, strings[0].length() - 2);

    if (!isFileExist(filename, fs)) {
        cout << filename << " doesn't exist\n";
        return;
    }

    ///// read
}