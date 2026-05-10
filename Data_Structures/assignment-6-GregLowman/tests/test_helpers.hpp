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
std::string test_add(string* movieName, string* director, string* genre, int length);
string test_show_movie(string* movieNames, string* directors, string* genres, int len, string movieName);
string test_show_movie_by_director(string* movieNames, string* directors, string* genre, int len, string director);
string test_print_leaves(string* movieNames,string* directors, string* genre, int len);
string test_get_height_of_movie_collection(string* movieNames, string* directors, string* genre, int len);
#endif // TEST_H__