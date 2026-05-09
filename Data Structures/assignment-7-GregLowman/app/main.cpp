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
    cout << "1. Show movie collection" << endl; // Show complete movie collection
    cout << "2. Add a movie"<< endl; // Add a movie to the collection
    cout << "3. Search a movie"<< endl; // Show movie by searching for given movie name
    cout << "4. Remove a movie"<< endl; // Removes the given movie
    cout << "5. Rotate the tree at given movie node" << endl; // Left rotate the tree at a give node
    cout << "6. Find the closest parent of two movies"<< endl; // Shows the closest parent node
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

    string movieName, director, genre;
    
    while(getline(iFile, line)) {
        stringstream ss(line);
        string field;

        int counter = 0;
        
        while(getline(ss, field, ',')) {
            if (counter == 0)
                movieName = field;
            else if (counter == 1)
                director = field;
            else if (counter == 2)
                genre = field;
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
            // Add a movie
            string movieName, director,genre;
            cout << "Enter the Name of the movie" << endl;
            cin.ignore();
            getline(cin,movieName); 
            cout << "Enter the director of the movie" << endl;
            getline(cin,director);
            cout << "Enter the genre of the movie" << endl;
            getline(cin,genre);
            tree->addMovie(movieName,director,genre);
            cout << "New Movie Added!" << endl;
        }
        else if (input == 3){
            // Search a movie
            string movie;
            cout << "Enter name of the movie:" << endl;
            cin.ignore();
            getline(cin, movie);
            tree->showMovie(movie);
        }
        else if (input == 4){
            // Remove the given movie
            string movieName;
            cout << "Enter the name of the movie:" << endl;
            cin.ignore();
            getline(cin,movieName);
            tree->removeMovie(movieName);
        }
        else if (input == 5){
            // Left rotates the tree at a given node
            string movieName;
            cout << "Enter the name of the movie:" << endl;
            cin.ignore();
            getline(cin,movieName);
            tree->rotateLeftCollection(movieName);
        }
        else if(input == 6)
        {
            // Find the closest parent for both the movies
            string movie1, movie2, parentMovie;
            cout << "Enter the name of the first movie (Movie1):" << endl;
            cin.ignore();
            getline(cin,movie1);
            cout << "Enter the name of the second movie (Movie2):" << endl;
            //cin.ignore();
            getline(cin,movie2);
            parentMovie = tree->closestParent(movie1, movie2);
            cout << "The closest parent to both the movies is: " << parentMovie << endl;
        }
        else if (input == 7){
            // Quit
            cout << "Goodbye!"<<endl;
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
