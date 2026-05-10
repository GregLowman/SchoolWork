#include "array_double.hpp"
#include <sstream>

/**
 * Reads the input file line by line, takes in the
 * query params along with reference of the passengers array
 */
void parseFile(ifstream& input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter) {

    recordIdx = 0;
    string line, airline, location = "";
    location = queryParams[0];
    airline = queryParams[1];
    int lowerLimit = stoi(queryParams[2]);
    int upperLimit = stoi (queryParams[3]);

    
    while(getline(input, line))
    {
        stringstream ss(line);
        AirlinePassenger newPassenger;
        string ageStr = "";

        getline(ss, newPassenger.name, ',');
        getline(ss, newPassenger.airline, ',');
        getline(ss, newPassenger.location, ',');
        getline(ss, ageStr);
        newPassenger.age = stoi(ageStr);

        if(isPassengerQueried(newPassenger, location, airline, lowerLimit, upperLimit))
        {
            addPassenger(passengers,newPassenger, arrCapacity, recordIdx, doublingCounter);
        }
    }

    cout << "Array doubled: " << doublingCounter << endl;
    cout << "Total number of passengers returned after the query: " << recordIdx << endl;
    printQueriedPassengers(passengers, recordIdx);
}

/**
 * Checks if the current passenger has their age in 
 * the queried age range, and their location and 
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge) {


    string location, airline = "";
    int age = 0;

    age = passenger.age;
    airline = passenger.airline;
    location = passenger.location;

    if(location == queryLocation && airline == queryAirline && age >= startAge && age <= endAge)
    {
        return true;
    }

    return false;
}

/**
 * Takes in a reference to an array of structs (passengers) 
 * and the current arrayCapacity. It doubles the size 
 * of the array by making a new array of size the current
 * size and copying the elements of the old one. 
 */
void resizeArr(AirlinePassenger *&passengers, int *arraySize) {
   int newArraySize = *arraySize * 2;
   AirlinePassenger *doubledArray = new AirlinePassenger[newArraySize];

   for(int i = 0; i < *arraySize; i++)
   {
        doubledArray[i] = passengers[i];
   }
   delete[] passengers;
   *arraySize = newArraySize;
   passengers = doubledArray;
}

/**
 * Append the new record to the passengers array. Here we double the 
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter) {
   //TODO

    if (recordIdx == arrCapacity)
    {
        resizeArr(passengers, &arrCapacity);
        doublingCounter++;
    }

    passengers[recordIdx] = airlinePassenger;
    recordIdx++;
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger *passengers, int length) {


    AirlinePassenger hold;

    for(int i = 0; i < length - 1; i++) {
        
        for(int j = 0; j < length - i - 1; j++){

            if(passengers[j].age < passengers[j+1].age ) {
                hold = passengers[j];
                passengers[j] = passengers[j+1];
                passengers[j+1] = hold;
            }
            else if(passengers[j].age == passengers[j+1].age && passengers[j].name > passengers[j+1].name ) {
                hold = passengers[j];
                passengers[j] = passengers[j+1];
                passengers[j+1] = hold;

            }
        }
    }    
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords) {

    sortPassengers(passengers, numOfRecords);

    cout << "Queried Passengers" << endl;
    cout << "---------------------------------------" << endl;

    for (int i = 0; i < numOfRecords; i++){
        cout << passengers[i].name << " " << passengers[i].age<< endl;
    }

}
