#include "command.h"

int main() {
    while(true) {
        char command[200];
        cin.clear();
        cin.getline(command, 200);
        startCommand(command);
    }
}