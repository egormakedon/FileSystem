#include "init.h"

void init(string message) {
    string FILE_NAME_REGEXP = "\".+\"";
    string NUMBER_REGEXP = "\\d+";

    vector<string> strings;
    boost::split(strings, message, boost::is_any_of(" "));

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
            FILE *file = fopen(filename.c_str(), "w+b");
            int number = ceil((double)stoi(strings[1]) / (double)BLOCK_SIZE) * 2;

            for (int index = 0; index < number; index++) {
                struct block b;
                fwrite(&b, sizeof(struct block), 1, file);
            }
            fclose(file);
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