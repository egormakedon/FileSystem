#include "init.h"

void init(string message) {
    string NUMBER_REGEXP = "\\d+";

    vector<string> strings = takeArgs(message);

    if (strings.size() != 2) {
        cout<<"wrong command\n";
        return;
    }
    if (!regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        cout<<"wrong filename: "<<strings[0]<<endl;
        return;
    }
    if (regex_match(strings[1], regex(NUMBER_REGEXP))) {
        string filename = "../bin/";
        filename.append(strings[0].substr(1, strings[0].length() - 2));
        ifstream fin(filename);

        if (!fin.is_open()) {
            int fd = open(filename.c_str(), O_RDWR | O_CREAT);

            int number = ceil((double)stoi(strings[1]) / (double)BLOCK_SIZE) * 2;
            int half = number / 2;
            block *b = new block[number];

            for (int index = 0; index < half; index++) {
                descriptor d;
                b[index].freeSpace = 0;
                memcpy(&b[index].value, &d, BLOCK_SIZE);
            }

            for (int index = 0; index < number; index++) {
                b[index].blockIndex = index;
                write(fd, &b[index], sizeof(b[index]));
            }
            close(fd);
        } else {
            fin.close();
            cout << filename << " already exist\n";
            return;
        }
    } else {
        cout<<"wrong parameter: "<<strings[1]<<endl;
        return;
    }
}