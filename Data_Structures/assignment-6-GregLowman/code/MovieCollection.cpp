#include "MovieCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

MovieCollection::MovieCollection() {
    root = nullptr;
}


MovieCollection::~MovieCollection() {
    Movie *current = root;
    deleteTree(current);
    root = nullptr;
}


void MovieCollection::addMovie(string movieName, string director, string genre) {
    Movie* newMovie = new Movie(movieName, director, genre);
    addMovieHelper(root, newMovie);
}


void MovieCollection::showMovieCollection() {
    if (root == nullptr)
    {
        cout << "Collection is empty." << endl;
        return;
    }
    printMovieRecursive(root);
}


void MovieCollection::showMovie(string movieName) {
    showMovieHelper(movieName);
}


void MovieCollection::showMoviesByDirector(string director) {
    cout << "Movies Directed By: " << director << endl;
    byDirectorHelper(root, director);
}


void MovieCollection::printLeaves()
{
    leafNodeHelperFunction(root);
}

int MovieCollection::getHeightOfMovieCollection() {
    if(!root)
    {
        return EMPTY_TREE_ERROR;
    }
    return getHeightHelper(root);
}

void MovieCollection::deleteTree(Movie* node)
{
    if(node)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}


void MovieCollection::addMovieHelper(Movie* &node, Movie* newNode)
{
    if(node == nullptr)
    {
        node = newNode;
    }
    else if(newNode->movieName < node->movieName)
    {
        addMovieHelper(node->left, newNode);
    }
    else
    {
        addMovieHelper(node->right, newNode);
    }

}


void MovieCollection::printMovieRecursive(Movie *movie)
{
    if(movie)
    {
        printMovieRecursive(movie->left);
        cout << "MOVIE: " << movie->movieName <<" DIRECTOR: " <<
         movie->director << " GENRE: " << movie->genre << endl;
        printMovieRecursive(movie->right);
    }
    else
    {
        return;
    }

}


void MovieCollection::showMovieHelper(string movieName)
{

    Movie* current = root;

    while(current != nullptr)
    {
        if(movieName == current->movieName)
        {
            cout << "Movie:" << endl;
            cout << "==================" << endl;
            cout << "Name :" << current->movieName << endl;
            cout << "Director :" << current->director << endl;
            cout << "Genre :" << current->genre << endl;
            return;
        }
        else if (movieName < current->movieName)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

    }

    cout << "Movie not found." << endl;

}


void MovieCollection::byDirectorHelper(Movie* current, string director)
{
    if(current != nullptr)
    {
        byDirectorHelper(current->right, director);
        if(current->director == director)
        {
            cout << current->movieName
            << " GENRE: " << current->genre << endl;
        }
        byDirectorHelper(current->left, director);
    }
    return;
}

void MovieCollection::leafNodeHelperFunction(Movie* currNode)
{
    if(currNode!=nullptr)
    {
        if(currNode->left == nullptr && currNode->right == nullptr)
        {
            cout << "MOVIE: " << currNode->movieName
            << " DIRECTOR: " << currNode->director
            << " GENRE: " << currNode->genre << endl;
            return;
        }
        leafNodeHelperFunction(currNode->left);
        leafNodeHelperFunction(currNode->right);
    }
}

int MovieCollection::getHeightHelper(Movie* current)
{
    if(current)
    {
        int leftHeight = getHeightHelper(current->left);
        int rightHeight = getHeightHelper(current->right);

        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
    else
    {
        return -1;
    }
}
