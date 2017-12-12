#include "init.h"

void init(string message, struct filesystem fs) {
    string FILE_NAME_REGEXP = "\".+\"";
    string NUMBER_REGEXP = "\\d+";

    vector<string> strings;
    boost::split(strings, message, boost::is_any_of(" "));

    if (strings.size() != 2) {
        cout<<"wrong command\n";
        return;
    }
    if (!regex_match(strings[0], regex(FILE_NAME_REGEXP))) {
        cout<<"wrong command\n";
        return;
    }
    if (regex_match(strings[1], regex(NUMBER_REGEXP))) {
        int number = stoi(strings[1]);
        if (number >= 5) {
            string filename = strings[0].substr(1, strings[0].length() - 1);
            //////  init filesystem
            ////// proverka na dublirovanie nazvaniya faila
            fs.fileSystemName = filename;
        } else {
            cout<<"wrong command\n";
            return;
        }
    } else {
        cout<<"wrong command\n";
        return;
    }
}