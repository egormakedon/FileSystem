#include "command.h"

struct filesystem filesystem;

void startCommand(string command) {
    string commandType;
    string message;

    char ch = '@';
    int chIndex = 0;

    for (int index = 0; index < command.length(); index++) {
        if (ch == '@' && command[index] != ' ') {
            chIndex = index;
            ch = command[index];
        }
        if (command[index] == ' ' && index != 0 && command[index - 1] != ' ') {
            commandType = command.substr(chIndex, command.length() - index - 1);
            message = command.substr(index + 1, command.length());
            break;
        }
    }

    int key = -1;

    if (commandType == "init") key = 0;
    if (commandType == "load") key = 1;
    if (commandType == "create") key = 2;
    if (commandType == "remove") key = 3;
    if (commandType == "copy") key = 4;
    if (commandType == "move") key = 5;
    if (commandType == "write") key = 6;
    if (commandType == "read") key = 7;

    commandFactory(key, message);
}

void commandFactory(int key, string message) {
    if (!isFileSystemLoad()) {
        cout<<"file system hasn't loaded\n";
        return;
    }

    switch (key) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            cout<<"wrong command\n";
            break;
    }
}

bool isFileSystemLoad() {
    string s = filesystem.fileSystemName;
    if (!s.compare("") == 0) {
        return true;
    } else {
        return false;
    }
}