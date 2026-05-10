#include <iostream>
#include <fstream>
#include "../code/fundamentals.hpp"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    string inputPath = argv[1];
    string outputPath = argv[2];

    stockInfo dataArray [6];
    double priceArray[5];
    string line;
    string name;

    int i = 0;
    int index = 0;

    ifstream fileChoice;
    fileChoice.open(inputPath);

    if (fileChoice.is_open())
    {
        while(getline(fileChoice, line))
        {
            stringstream ss(line);
            getline(ss, name, ',');

            while (i < 5)
            {
                double truePrice;
                string price;
                getline(ss, price, ',');
                truePrice = stod(price);
                priceArray[i] = truePrice;
                i++;
            }
            i = 0;
            insertStockInfo(dataArray, name, priceArray, index);
            index++;
        }

        ofstream outputFile(outputPath);

        for (int i = 0; i < index; i++)
        {
            displaySortedStocks(dataArray[i], outputFile);
        }
    }
    return 0;
}
