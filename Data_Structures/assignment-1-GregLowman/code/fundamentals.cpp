#include "fundamentals.hpp"

void insertStockInfo(stockInfo stocks[], string company_name, double stock_prices_arr[], int index) {
    stockInfo company;
    double average = averagePrices(stock_prices_arr);
    company.company_name = company_name;
    company.average = average;
    for (int i = 0; i < 5; i++)
    {
       company.stock_prices_arr[i] = stock_prices_arr[i];
    }
    stocks[index] = company;
    return;
}

void displaySortedStocks(stockInfo stock, ofstream& file){
    int index = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (stock.stock_prices_arr[j] > stock.stock_prices_arr[j + 1])
            {
                double hold = stock.stock_prices_arr[j];
                stock.stock_prices_arr[j] = stock.stock_prices_arr[j + 1];
                stock.stock_prices_arr[j + 1] = hold;
            }
        }
    }

    cout << stock.company_name << "," << stock.average;
    file << stock.company_name << "," << stock.average;

    for(int i = 0; i < 5; i++)
    {
        cout << "," << stock.stock_prices_arr[i];
        file << "," << stock.stock_prices_arr[i];
    }

    cout << endl;
    file << endl;

    return;
}

double averagePrices(double prices[])
{
    double totalPrice = 0.0;
    double average;
    for (int i = 0; i < 5; i++)
    {
        totalPrice += prices[i];
    }
    average = totalPrice / 5;
    return (average);
}
