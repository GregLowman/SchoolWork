

#include "../code/MovieCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
traceNode *traceHead = NULL;
bool verbose = false;
int numAllocs = 0;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Show the collection of all movies" << endl; // Show complete movie collection sorted by alphabets
    cout << "2. Add a movie"<< endl; // Add a movie to the collection
    cout << "3. Search the movie by the movie name"<< endl; // Display movie by a given movie name
    cout << "4. Display the movies directed by a Director"<< endl; // Display movies by a given director
    cout << "5. Display the leaf nodes of the movies BST"<< endl; // Display leaf nodes of movies BST.
    cout << "6. Display the height of the movies BST"<< endl; // Show the height of the movies collection (Height of the BST)
    cout << "7. Quit"<< endl; //Quit
    cout << "> ";
    
}

int main(int argc, char** argv) {
	
    if(argc>2) 
     {
         freopen(argv[2],"r",stdin);  
     }
    
    int input;
    MovieCollection* tree = new MovieCollection();

    // PROCESS THE FILE
    ifstream iFile(argv[1]);
    string line;

    string movieName,genre,director;

    while(getline(iFile, line)) {
        stringstream ss(line);
        string field;

        int counter = 0;
        while(getline(ss, field, ',')) {
            if (counter == 0)
                movieName = field;
            else if (counter == 1)
                genre = field;
            else if (counter == 2)
                director = field;
            counter++;
        }
        tree->addMovie(movieName,director,genre);
    }

    // PRESENT MENU
    displayMenu();
    cin >> input;

    while (1) {
        if (input == 1) {
            // Show movie collection (in alphabetically sorted order)
            tree->showMovieCollection();
        }
        else if (input == 2){
            // Add the movie using name,director and genre of the movie
            string movieName,genre,director;
            cout << "Enter the Name of the movie" << endl;
            cin.ignore();
            getline(cin,movieName); 
            cout << "Enter the director of the movie" << endl;
            getline(cin,director);
            cout << "Enter the genre of the movie" << endl;
            getline(cin,genre);
            tree->addMovie(movieName,director,genre);
            cout << "New movie Added!" << endl;
        }
        else if (input == 3){
            // Search the movie by name
            string movieName;
            cout << "Enter name of the movie:" << endl;
            cin.ignore();
            getline(cin, movieName);
            tree->showMovie(movieName);
        }
        else if (input == 4){
            // Display movies by a given director
            string director;
            cout << "Enter the name of the director" << endl;
            cin.ignore();
            getline(cin,director);
            tree->showMoviesByDirector(director);
        }
        else if (input == 5){
            // Display the leaves of the BST
            tree->printLeaves();
        }
        else if(input == 6)
        {
            // Display the height of the BST
            int height;
            height = tree->getHeightOfMovieCollection();
            if (height == EMPTY_TREE_ERROR)
                cout << "Collection is Empty!" << endl;
            else
                cout << "The Height of the movie Collection's BST is " << height << endl;
        }
        else if (input == 7){
            // Quit
            cout << "Goodbye!" << endl;
            break;
        }
        displayMenu();
        cin >> input;
    }
    
    
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
    return 0;
}




/*
#include "../code/MovieCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;
traceNode *traceHead = NULL;
bool verbose = false;
int numAllocs = 0;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Show the collection of all movies" << endl;
    cout << "2. Add a movie"<< endl;
    cout << "3. Search the movie by the movie name"<< endl;
    cout << "4. Display the movies directed by a Director"<< endl;
    cout << "5. Display the leaf nodes of the movies BST"<< endl;
    cout << "6. Display the height of the movies BST"<< endl;
    cout << "7. Quit"<< endl;
    cout << "> ";
}

int main(int argc, char** argv) {

    MovieCollection* tree = new MovieCollection();

    // Optional CSV load (start empty if none provided)
    if (argc > 1) {
        ifstream iFile(argv[1]);
        if (iFile) {
            string line, movieName, genre, director;
            while (getline(iFile, line)) {
                stringstream ss(line);
                string field;
                int counter = 0;
                while (getline(ss, field, ',')) {
                    if (counter == 0) movieName = field;
                    else if (counter == 1) genre = field;
                    else if (counter == 2) director = field;
                    counter++;
                }
                if (counter >= 3) {
                    tree->addMovie(movieName, director, genre);
                }
            }
        }
    }
    // If you *need* stdin redirection for automated tests, re-enable this:
    // if (argc > 2) { freopen(argv[2], "r", stdin); }

    while (true) {
        displayMenu();

        int input;
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (input == 1) {
            tree->showMovieCollection();
        }
        else if (input == 2){
            string movieName, genre, director;
            cout << "Enter the Name of the movie" << endl;
            getline(cin, movieName);
            cout << "Enter the director of the movie" << endl;
            getline(cin, director);
            cout << "Enter the genre of the movie" << endl;
            getline(cin, genre);
            tree->addMovie(movieName, director, genre);
            cout << "New movie Added!" << endl;
        }
        else if (input == 3){
            string movieName;
            cout << "Enter name of the movie:" << endl;
            getline(cin, movieName);
            tree->showMovie(movieName);
        }
        else if (input == 4){
            string director;
            cout << "Enter the name of the director" << endl;
            getline(cin, director);
            tree->showMoviesByDirector(director);
        }
        else if (input == 5){
            tree->printLeaves();
        }
        else if (input == 6){
            int height = tree->getHeightOfMovieCollection();
            if (height == EMPTY_TREE_ERROR)
                cout << "Collection is Empty!" << endl;
            else
                cout << "The Height of the movie Collection's BST is " << height << endl;
        }
        else if (input == 7){
            cout << "Goodbye!" << endl;
            break;
        }
    }

    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
    return 0;
}
*/