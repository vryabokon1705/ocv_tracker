#include <iostream>

#include "player.h"

using namespace std;

void printUsage() {
    cout << "usage: ocv_tracker <trackertType> <inputFile> <outputFile> <logFile> <roiPercentage>" << endl;
}


int main(int argc, char *argv[])
{

    if(argc < 6) {
        printUsage();
        return 0;
    }

    int roiPercentage = stoi(argv[5]);
    if(roiPercentage <= 0 || roiPercentage >= 100) {
        cerr << "Roi percentage cannot be less than 0 and greater than 100" << endl;
        return 1;
    }

    shared_ptr<Player> player = make_shared<Player>(argv[1], argv[2], argv[3], argv[4], roiPercentage);
    player->readFile();
    return 0;
}
