#include "command.h"

struct filesystem fs;

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
            commandType = command.substr(chIndex, index - chIndex);
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
    if (command == "exit") key = 8;

    commandFactory(key, message);
}

void commandFactory(int key, string message) {
    if (!isFileSystemLoad() && key != 0 && key != 1 && key != 8) {
        cout<<"file system hasn't loaded\n";
        return;
    }

    switch (key) {
        case 0:
            init(message);
            break;
        case 1:
            load(message, fs);
            break;
        case 2:
            create(message, fs);
            break;
        case 3:
            remove(message, fs);
            break;
        case 4:
            copy(message, fs);
            break;
        case 5:
            move(message, fs);
            break;
        case 6:
            write(message, fs);
            break;
        case 7:
            read(message, fs);
            break;
        case 8:
            exit(0);
        default:
            cout<<"wrong command\n";
            break;
    }
}

bool isFileSystemLoad() {
    string s = fs.fileSystemName;
    if (!s.compare("") == 0) {
        return true;
    } else {
        return false;
    }
}