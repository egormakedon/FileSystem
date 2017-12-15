#include <boost/algorithm/string/classification.hpp>
#include "commonfunc.h"

vector<string> takeArgs(string message) {
    vector<string> strings;
    boost::split(strings, message, boost::is_any_of(" "));
    return strings;
}

bool isFileExist(string filename, struct filesystem fs) {
    ////
}

bool isFreeBlockExist(struct filesystem fs) {
    ////
}

