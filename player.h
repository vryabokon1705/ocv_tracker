#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <opencv2/opencv.hpp>

#include "trackerservice.h"
#include "csvwriter.h"


using namespace std;
using namespace cv;
class Player
{
    const string WINDOW_NAME= "ocv_tracker";
    const int BORDER_WIDTH_MOUSE_HOVER = 1;
    const int BORDER_WIDTH_SELECTION = 2;
    const int BORDER_WIDTH_TRACKING = 2;
    const Scalar BORDER_COLOR_MOUSE_HOVER = Scalar( 255, 0, 0 );
    const Scalar BORDER_COLOR_SELECTION = Scalar( 0, 255, 0 );
    const Scalar BORDER_COLOR_TRACKING = Scalar( 0, 0, 255 );
    const float TEXT_SCALE = 0.75;
    const int TEXT_THICKNESS = 2;
    const int TEXT_MARGIN = 2;

    string _videouSource;
    string _trackerType;
    int _roiPercentage;
    string _outputFile;

    Ptr<TrackerService> _trackerService;
    Ptr<CsvWriter> _csvWriter;
    VideoWriter _outputWriter;

    Mat _frame;
    bool _tracking = false;
    Rect2d _roi;
    int _borderWidth = 1;
    Scalar _borderColor = BORDER_COLOR_MOUSE_HOVER;

public:
    Player(string trackerType, string videouSource, string outputFile, string logFile, int roiPercentage);
    ~Player();
    void readFile();

private:
    void selectObject(int action, int x, int y, int flags);
    static void selectObject(int event, int x, int y, int, void* userdata);
    Mat getFrame();
    void calculateRoi(int x, int y);
    bool isDrawRoi();
    void showCoordinates();
    static string rectToString(Rect2d rect);


};

#endif // PLAYER_H
