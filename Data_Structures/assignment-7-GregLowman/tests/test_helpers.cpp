#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code/MovieCollection.hpp"

bool verbose = false;
int numAllocs = 0;
traceNode *traceHead = NULL;

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

void memLeakCheck(MovieCollection* root){
    delete root;
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
}

void _showPreOrderMovieCollectionHelper(Movie* movie){
    if (movie != nullptr) {
        cout << "MOVIE: " << movie->movieName << " DIRECTOR: " << movie->director << " GENRE: " << movie->genre << endl;
        _showPreOrderMovieCollectionHelper(movie->left);
        _showPreOrderMovieCollectionHelper(movie->right);
    }
}

void getPreOrderedMovieCollection(MovieCollection* collection){
    if (collection == nullptr) {
        cout << "Collection is empty." << endl;
        return;
    }
    _showPreOrderMovieCollectionHelper(collection->getRoot());
}

MovieCollection* createMovieCollection(string* movieNames, string* directors, string* genres, int len){
    MovieCollection* movie = new MovieCollection();
    for(int i=0;i<len;i++)
    {
        movie->addMovie(movieNames[i],directors[i],genres[i]);
    }
    return movie;
}

string testRemoveMovie(MovieCollection* root, string removeMovieName){
    testing::internal::CaptureStdout();
    root->removeMovie(removeMovieName);
    root->showMovieCollection();
    memLeakCheck(root);
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string testRotateCollection(MovieCollection* root, string rotateMovie){
    testing::internal::CaptureStdout();
    root->rotateLeftCollection(rotateMovie);
    getPreOrderedMovieCollection(root);
    memLeakCheck(root);
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string testClosestParent(MovieCollection* root, string movie_1, string movie_2){
    testing::internal::CaptureStdout();
    cout<<root->closestParent(movie_1, movie_2);
    memLeakCheck(root);
    string output = testing::internal::GetCapturedStdout();
    return output;
}