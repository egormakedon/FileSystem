#include "commandvalidator/commandvalidator.h"
#include "structheader/structHeader.h"

int main() {
    struct filesystem filesystem;
    while(true) {
        string command;
        cin >> command;
        if (validate(command)) {
            /////
        } else {
            cout<<"wrong command\n";
            continue;
        }
    }
}