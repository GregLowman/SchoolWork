#include <gtest/gtest.h>
#include "test_helpers.hpp"
#include "../code/Dungeon.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

bool test_findPath(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    int n;
    file >> n; // Read the size of the maze
    Dungeon *d = new Dungeon(n);

    string line;
    getline(file, line); // Move to the next line after reading n

    for (int i = 0; i < n; i++) {
        getline(file, line);
        stringstream ss(line);
        for (int j = 0; j < n; j++) {
            char cell;
            ss >> cell;
            cell_type type;
            switch (cell) {
                case 'S': type = start; break;
                case 'E': type = END; break;
                case '.': type = open; break;
                case 'X': type = wall; break;
                case 'R': type = radioactive; break;
                default: type = wall; break;
            }
            d->dungeon[i][j] = type;
            d->addVertex(i, j, type);
        }
    }
    
    file.close();

    // Convert the grid to an adjacency list representation.
    d->convertDungeonToAdjacencyListGraph();

    // Use the modified DFS method to determine if the dungeon is traversable.
    bool result = d->isDungeonTraversable();

    delete d; // Cleanup memory
    return result;
}

string test_printPath(Dungeon &tmp_sr) {
    testing::internal::CaptureStdout();
    /*
    TODO if needed: implement printing of the path if required.
    */
    string output = testing::internal::GetCapturedStdout();
    return output;
}
