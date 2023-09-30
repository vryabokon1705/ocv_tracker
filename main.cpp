#include <iostream>

#include "player.h"

using namespace std;

void printUsage() {
    cout << "usage: ocv_tracker <inputFile> <trackertType> <roiPercentage> <logFile> <outputFile>" << endl;
}


int main(int argc, char *argv[])
{

    if(argc < 6) {
        printUsage();
        return 0;
    }

    shared_ptr<Player> player = make_shared<Player>(argv[1], argv[2], stoi(argv[3]), argv[4], argv[5]);
    player->readFile();
    return 0;
}
