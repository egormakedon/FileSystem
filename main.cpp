#include "command.h"

int main() {
    while(true) {
        cout<<"> ";
        char command[200];
        cin.clear();
        cin.getline(command, 200);
        startCommand(command);
    }
}