#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code/MovieCollection.hpp"


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}


traceNode *traceHead = NULL;
bool verbose = false;
int numAllocs = 0;


string test_add(string* movieName, string* director, string* genre, int len)
{
    MovieCollection* movie = new MovieCollection();
    testing::internal::CaptureStdout();
    
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:(" <<movieName[i]<<", "<<director[i]<<", "<<genre[i] <<")"<< endl;
        movie->addMovie(movieName[i],director[i],genre[i]);
    }
    cout<<"[GRADER] Printing movie collection:"<<endl;
    movie->showMovieCollection();
    
     // MEMCHECK!
    delete movie;
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
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_show_movie(string* movieNames, string* directors, string* genre, int len, string movieName){
    MovieCollection* tree = new MovieCollection();
    testing::internal::CaptureStdout();

    for(int i = 0; i < len; i++){
        tree->addMovie(movieNames[i], directors[i], genre[i]);
    }

    tree->showMovie(movieName);
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
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_show_movie_by_director(string* movieNames, string* directors, string* genre, int len, string director){
    MovieCollection* tree = new MovieCollection();
    testing::internal::CaptureStdout();

    for(int i = 0; i < len; i++){
        tree->addMovie(movieNames[i], directors[i], genre[i]);
    }

    tree->showMoviesByDirector(director);
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
     
    string output = testing::internal::GetCapturedStdout();
    return output;

}

string test_print_leaves(string* movieNames,string* directors, string* genre, int len)
{
    MovieCollection* tree = new MovieCollection();
    testing::internal::CaptureStdout();
    
    for(int i=0;i<len;i++)
    {
         tree->addMovie(movieNames[i], directors[i], genre[i]);
    }
    
    cout << "[GRADER] Result of movies.printLeaves is:" << endl;
    tree->printLeaves();
    cout << endl;
        
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
    
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_get_height_of_movie_collection(string* movieNames, string* directors, string* genre, int len){
    MovieCollection* tree = new MovieCollection();
    testing::internal::CaptureStdout();

    for(int i = 0; i < len; i++){
        tree->addMovie(movieNames[i], directors[i], genre[i]);
    }

    int height = tree->getHeightOfMovieCollection();

    if (height == EMPTY_TREE_ERROR)
        cout << "[GRADER]Empty Tree!" << endl;
    else
        cout << "[GRADER]Height of Movie Collection:" << height << endl;

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
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}
