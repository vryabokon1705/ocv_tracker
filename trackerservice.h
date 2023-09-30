#ifndef TRACKERSERVICE_H
#define TRACKERSERVICE_H
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

using namespace std;
using namespace cv;
class TrackerService
{
    string _trackerType;
    Ptr<Tracker> _tracker;
public:
    TrackerService(string trackerType);
    bool init(Mat frame, const Rect2d &roi);
    bool update(Mat frame, Rect2d &roi);
    bool isTrackerCreated();

};

#endif // TRACKERSERVICE_H
