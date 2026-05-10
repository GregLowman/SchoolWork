#include <iostream>
#include <vector>
#include "../code/LinkedInNetwork.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    LinkedInNetwork newNetwork;
    newNetwork.addProfessional("Bob");
    newNetwork.addProfessional("Jeff");
    newNetwork.addProfessional("Paul");
    newNetwork.addProfessional("Bob");
    newNetwork.addProfessional("Mandy");

    cout << "hello" << endl;
    
    return 0;
}
