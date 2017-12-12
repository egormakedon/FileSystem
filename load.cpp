#include "load.h"

void load(string message, struct filesystem fs) {
    string FILE_NAME_REGEXP = "\".+\"";

    vector<string> strings;
    boost::split(strings, message, boost::is_any_of(" "));

    if (strings.size() != 1) {
        cout<<"wrong command\n";
        return;
    }

    if (regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        string filename = "bin/";
        filename.append(strings[0].substr(1, strings[0].length() - 2));

        ifstream fin(filename);
        if (fin.is_open()) {
            fin.close();
            fs.fileSystemName = filename;
            return;
        } else {
            cout<<filename<<" doesn't exist\n";
            return;
        }
    } else {
        cout<<"wrong filename: "<<strings[0]<<endl;
        return;
    }
}