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
        string filename = strings[0].substr(1, strings[0].length() - 1);
        //проверка, если есть файл
        fs.fileSystemName = filename;
    } else {
        cout<<"wrong command\n";
        return;
    }
}