#include "MovieCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

MovieCollection::MovieCollection() {
    root = nullptr;
}

void _destructMovieCollection(Movie *movie) {
    if (movie == nullptr) return;
    else {
        _destructMovieCollection(movie->left);
        _destructMovieCollection(movie->right);
        delete movie;
    }
}

MovieCollection::~MovieCollection() {
    _destructMovieCollection(root);
}



void MovieCollection::removeMovie(string movieName) {

    // Base Cases
    if(!root)
    {
        cout << "Movie not found!" << endl;
        return;
    }
    Movie* toDelete = returnMovie(movieName, root);
    Movie* parentOfDelete = returnParent(movieName, root);
    if(!toDelete)
    {
        cout << "Movie not found!" << endl;
        return;
    }


    //Root Nodes
    if(parentOfDelete == nullptr)
    {
        // Root is a leaf
        if (!toDelete->left && !toDelete->right) {
            delete toDelete;
            root = nullptr;
            return;
        }

        // Root has only one child
        else if (toDelete->left && !toDelete->right) {
            root = toDelete->left;
            delete toDelete;
            return;
        } else if (!toDelete->left && toDelete->right) {
            root = toDelete->right;
            delete toDelete;
            return;
        }

        // Root has two children
        else {
            Movie* min = lowestNode(toDelete->right);
            Movie* minParent = returnParent(min->movieName, root);

            if (minParent != toDelete)
            {
                minParent->left = min->right;

                min->right = toDelete->right;
            }
            min->left = toDelete->left;
            root = min;
            delete toDelete;
            return;

        }
    }

    //Leaf Node
    if(!toDelete->left && !toDelete->right)
    {
        if(toDelete->movieName < parentOfDelete->movieName)
        {
            parentOfDelete->left = nullptr;
        }
        else
        {
            parentOfDelete->right = nullptr;
        }
        delete toDelete;
        return;
    }

    //Node having either only one child
    else if(toDelete->left && !toDelete->right)
    {
        if(toDelete->movieName < parentOfDelete->movieName)
        {
            parentOfDelete->left = toDelete->left;
        }
        else
        {
            parentOfDelete->right = toDelete->left;
        }
        delete toDelete;
        return;
    }


    else if(!toDelete->left && toDelete->right)
    {
        if(toDelete->movieName < parentOfDelete->movieName)
        {
            parentOfDelete->left = toDelete->right;
        }
        else
        {
            parentOfDelete->right = toDelete->right;
        }
        delete toDelete;
        return;
    }

    //Node having both children
    else if(toDelete->right && toDelete->left)
    {

        Movie* minimumMovie = lowestNode(toDelete->right);
        Movie* minimumParent = returnParent(minimumMovie->movieName, root);
        if (minimumParent != toDelete)
        {
            minimumParent->left = minimumMovie->right;
            minimumMovie->right = toDelete->right;
        }
        minimumMovie->left = toDelete->left;

        if(parentOfDelete->left == toDelete)
        {
            parentOfDelete->left = minimumMovie;
        }
        else
        {
            parentOfDelete->right = minimumMovie;
        }

        delete toDelete;
        return;

    }

}


void MovieCollection::rotateLeftCollection(string movieName) {

    Movie *current = returnMovie(movieName, root);
    if(current)
    {
        Movie *rotate = current->right;

        if(!rotate)
        {
            return;
        }

        Movie *currentParent = returnParent(movieName, root);


        current->right = rotate->left;
        rotate->left = current;

        if(!currentParent)
        {
            root = rotate;
        }
        else if (currentParent->left == current)
        {
            currentParent->left = rotate;
        }
        else
        {
            currentParent->right = rotate;
        }

    }
    return;

}


string MovieCollection::closestParent(string movie1, string movie2) {
    Movie *current = root;

    if(!returnMovie(movie1, root) || !returnMovie(movie2, root))
    {
        cout << "Movie not found!" << endl;
        return "Error - wrong movie name";
    }

    while(current)
    {
        if(movie1 < current->movieName && movie2 < current->movieName)
        {
            current = current->left;
        }
        else if (movie1 > current->movieName && movie2 > current->movieName)
        {
            current = current->right;
        }
        else
        {
            return current->movieName;
        }
    }
    cout << "Movie not found!" << endl;
    return "Error - wrong movie name";
}


Movie* MovieCollection :: lowestNode(Movie* current)
{
    if(current)
    {
        while(current->left)
        {
            current = current->left;
        }
        return(current);
    }
    return(nullptr);
}


Movie* MovieCollection::returnMovie(string key, Movie* current) {
    while (current) {
        if (key < current->movieName) {
            current = current->left;
        } else if (key > current->movieName) {
            current = current->right;
        } else {
            return current; // found
        }
    }
    return nullptr; // not found
}


Movie* MovieCollection::returnParent(string key, Movie* current) {
    Movie* parent = nullptr;
    while (current) {
        if (key < current->movieName) {
            parent = current;
            current = current->left;
        } else if (key > current->movieName) {
            parent = current;
            current = current->right;
        } else {
            // found the key: parent may be nullptr if key was at root
            return parent;
        }
    }
    return nullptr; // key not in the tree
}
