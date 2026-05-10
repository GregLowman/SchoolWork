#pragma once
#ifndef MovieCollection_H__
#define MovieCollection_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

#include "../library/MovieCollectionBase.hpp"

using namespace std;

class MovieCollection : public MovieCollectionBase {

    public:
        MovieCollection();
        ~MovieCollection();

        Movie* returnMovie(string key, Movie* current);
        Movie* lowestNode(Movie* current);
        Movie* returnParent(string key, Movie* current);
        void removeMovie(string movieName);
        void rotateLeftCollection(string movieName);
        string closestParent(string movie1, string movie2);
        Movie* getRoot(){
            return root;
        }
};

#endif
