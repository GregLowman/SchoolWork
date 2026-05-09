#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include "../code/MovieCollection.hpp"

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
void memLeakCheck(MovieCollection* root);
void getPreOrderedMovieCollection(MovieCollection* root);
MovieCollection* createMovieCollection(string* movieNames, string* directors, string* genre, int len);
string testRemoveMovie(MovieCollection* root, string removeMovie);
string testRotateCollection(MovieCollection* root, string rotateMovie);
string testClosestParent(MovieCollection* root, string movie_1, string movie_2);
#endif // TEST_H__