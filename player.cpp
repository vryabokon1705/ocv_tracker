#include <iostream>
#include <sstream>

#include "player.h"

Player::Player(string trackerType, string videouSource, string outputFile, string logFile, int roiPercentage):
    _videouSource(videouSource), _trackerType(trackerType), _roiPercentage(roiPercentage), _outputFile(outputFile)
{
    _roi = Rect2d(0, 0, 0, 0);
    _csvWriter = new CsvWriter(logFile);
}

Player::~Player() {
}

Mat Player::getFrame() {
    return _frame;
}


void Player::readFile() {
    cout << "Opening file " << _videouSource << endl;
    VideoCapture cap(_videouSource);
    if (!cap.isOpened())
    {
        cout  << "Could not open the input video: " << _videouSource << endl;
        return;
    }

    Size size = Size((int) cap.get(CAP_PROP_FRAME_WIDTH),
                     (int) cap.get(CAP_PROP_FRAME_HEIGHT));

    _outputWriter.open(_outputFile, VideoWriter::fourcc('m', 'p', '4', 'v'), cap.get(CAP_PROP_FPS), size, true);

    if (!_outputWriter.isOpened())
    {
            cerr  << "Could not open the output video for write" << endl;
            return;
    }

    cv::namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    cap >> _frame;
    imshow( WINDOW_NAME, _frame );
    setMouseCallback(WINDOW_NAME, selectObject, this);

    while(1){

        cap >> _frame;
        if(_tracking) {
            bool trackingOk = _trackerService->update(_frame, _roi);
            if(!trackingOk) {
                cout << "Tracking failed" << endl;
                _roi = Rect2d(0, 0, 0, 0);
                _tracking = false;
            }
        }

        if ((_frame).empty())
            break;

        if(isDrawRoi()) {
            rectangle(_frame, _roi, _borderColor, _borderWidth, 1);
            if(_tracking) {
                string roiStringValue = rectToString(_roi);
                cout << roiStringValue << endl;
                _csvWriter->writeString(roiStringValue);

                showCoordinates();
            }

        }
//Write to output vide file
        _outputWriter << _frame;

        imshow(WINDOW_NAME, _frame );

        char c=(char)waitKey(25);
        if(c==27)
            break;
    }


    destroyAllWindows();
}

void Player::selectObject(int event, int x, int y, int flags, void *userdata)
{
    Player* player = reinterpret_cast<Player*>(userdata);
    player->selectObject(event, x, y, flags);
}

void Player::selectObject(int event, int x, int y, int flags) {
    if( event == EVENT_MOUSEMOVE && !_tracking)
    {
        if(!(flags & EVENT_FLAG_LBUTTON)) {
            _borderWidth = BORDER_WIDTH_MOUSE_HOVER;
            _borderColor = BORDER_COLOR_MOUSE_HOVER;
        }
        Point center = Point(x,y);
        calculateRoi(x, y);
    }
    else if( event == EVENT_LBUTTONDOWN)
    {
        _tracking = false;
        Point center = Point(x,y);
        _borderWidth = BORDER_WIDTH_SELECTION;
        _borderColor = BORDER_COLOR_SELECTION;
        calculateRoi(x, y);
    }
    else if( event == EVENT_LBUTTONUP)
    {
        Point center = Point(x,y);

        calculateRoi(x, y);
        _trackerService = new TrackerService(_trackerType);
        if(_trackerService->isTrackerCreated()) {
            _borderWidth = BORDER_WIDTH_TRACKING;
            _borderColor = BORDER_COLOR_TRACKING;
            _tracking = true;
            _trackerService->init(_frame, _roi);
            cout << "Starting tracking with " <<_trackerType << endl;
            cout << rectToString(_roi) << endl;
        }
        else {
            _borderWidth = BORDER_WIDTH_MOUSE_HOVER;
            _borderColor = BORDER_COLOR_MOUSE_HOVER;
            _tracking = false;
            cerr << "Cannot create tracker of type" << _trackerType << endl;
        }
    }

}

void Player::calculateRoi(int x, int y) {
    Point center = Point(x,y);

    auto roiWidth = _frame.cols / 100 * _roiPercentage;
    auto roiHeight = _frame.rows / 100 * _roiPercentage;
    auto left = center.x - roiWidth / 2;
    auto top = center.y - roiHeight / 2;
    if(center.x - roiWidth < 0) {
        left = 0;
    }
    else if(left + roiWidth > _frame.cols) {
        left = _frame.cols - roiWidth;
    }

    if(center.y - roiHeight < 0) {
        top = 0;
    }
    else if(top + roiHeight > _frame.rows) {
        top = _frame.rows - roiHeight;
    }
    _roi = Rect2d(left, top, roiWidth, roiHeight);
}

bool Player::isDrawRoi() {
    return _roi.area() > 0;
}

void Player::showCoordinates() {
    if(isDrawRoi()) {
        string roiText = rectToString(_roi) + "," + _trackerType;
        int baseline = 0;
        Size textSize = getTextSize(roiText, FONT_HERSHEY_SIMPLEX, TEXT_SCALE, TEXT_THICKNESS, &baseline);
        putText(_frame, roiText, Point(TEXT_MARGIN,textSize.height + TEXT_MARGIN), FONT_HERSHEY_SIMPLEX, TEXT_SCALE, _borderColor, TEXT_THICKNESS);
    }
}

string Player::rectToString(Rect2d rect) {
    stringstream buffer;
    buffer << rect.x << "," << rect.y << "," << rect.width << "," << rect.height;
    return buffer.str();
}
