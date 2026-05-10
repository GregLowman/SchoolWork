#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;


int main(int argc, char* argv[])
{

    if (argc < 6) 
    {
    cout << "Usage: " << argv[0] << " <fileName> <location> <airline> <lowerAge> <upperAge>\n";
    return -1;
    }
    string fileName = argv[1];

    string queryParameters [4];
    for(int i = 0; i < 4; i++)
    {
        int j = i+2;
        queryParameters[i] = argv[j];
    }

    int arraySize = 10;
    int recordId, doubleCount = 0;
    AirlinePassenger *passangerArrayPointer = new AirlinePassenger[arraySize];

  
    ifstream inStream;
    inStream.open(fileName);

    string line;

    if (inStream.is_open())
    {
      parseFile(inStream, queryParameters, passangerArrayPointer, arraySize, recordId, doubleCount);
    }

    inStream.close();
    
    delete[] passangerArrayPointer;
    return 0;
}
