# Test project to show tracking possibilities of different OpenCV tracking methods
## Prerequirements
- OS: Linux
- OpenCV 4.x (maximum 4.5.0) with ffmpeg support and tracking support properly installed
- git, cmake, make,pkg-config, gcc with c++11 support

## Installation
```
mkdir install
cd install
git clone https://github.com/vryabokon1705/ocv_tracker.git
cd ocv_tracker
mkdir build && cd build
cmake ..
make
sudo make install
```

## Usage
```
ocv_tracker <inputFile> <trackertType> <roiPercentage> <logFile> <outputFile>
```
where: 
 - inputFile: complete path to video file to process
 - trackertType: OpenCV tracker, one of BOOSTING, MIL, KCF, TLD, MEDIANFLOW, GOTURN, MOSSE
 - roiPercentage: size of selection to track for as percentage of input video frame size
 - logFile: complete path to file, used to collect tracking data (roi position)
 - outputFile: complete path to output file, where processed video frames witll be stored
