#include "csvwriter.h"

CsvWriter::CsvWriter(string filePath):
    _filePath(filePath)
{
    _csvFile.open (filePath);
}

CsvWriter::~CsvWriter () {
    if(_csvFile.is_open()) {
        _csvFile.close();
    }
}

void CsvWriter::writeString(string stringValue)
{
    if(_csvFile.is_open())
        _csvFile << stringValue << endl;
    else
        cerr << "Error on writing string value: file is not open" << endl;
}
