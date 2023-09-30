#ifndef CSVWRITER_H
#define CSVWRITER_H
#include <string>
#include <iostream>
#include <fstream>


using namespace std;
class CsvWriter
{
 string _filePath;
 ofstream _csvFile;
public:
    CsvWriter(string filePath);
    ~CsvWriter();

    void writeString(string stringValue);
};


#endif // CSVWRITER_H
