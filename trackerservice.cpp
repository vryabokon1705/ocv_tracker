#include "trackerservice.h"

TrackerService::TrackerService(string trackerType)
{
    if (trackerType == "BOOSTING")
        _tracker = TrackerBoosting::create();
    else if (trackerType == "MIL")
        _tracker = TrackerMIL::create();
    else if (trackerType == "KCF")
        _tracker = TrackerKCF::create();
    else if (trackerType == "TLD")
        _tracker = TrackerTLD::create();
    else if (trackerType == "MEDIANFLOW")
        _tracker = TrackerMedianFlow::create();
    else if (trackerType == "GOTURN")
        _tracker = TrackerGOTURN::create();
    else if (trackerType == "MOSSE")
        _tracker = TrackerMOSSE::create();
    else return;
}

bool TrackerService::init(Mat frame, const Rect2d &roi) {
    return _tracker->init(frame, roi);
}

bool TrackerService::update(Mat frame, Rect2d &roi) {
    return _tracker->update(frame, roi);
}

bool TrackerService::isTrackerCreated() {
    return !_tracker.empty();
}
