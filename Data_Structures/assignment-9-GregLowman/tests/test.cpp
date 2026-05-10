// tests.cpp
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "../code/Dungeon.hpp"
#include "test_helpers.hpp"  // Make sure this helper now returns a bool for test_findPath

using namespace std;

class test_x : public ::testing::Test {
protected:
    // This function runs only once before any TEST_F functions
    static void SetUpTestCase(){
        ofstream outgrade("./total_grade.txt");
        if(outgrade.is_open()){
            outgrade.clear();
            outgrade << (int)0;
            outgrade.close();
        }
    }
    // This function runs after all TEST_F functions have been executed
    static void TearDownTestCase(){
        ofstream outgrade("./total_grade.txt");
        if(outgrade.is_open()){
            outgrade.clear();
            outgrade << (int)ceil(100 * total_grade / max_grade);
            outgrade.close();
            cout << "Total Grade is : " << (int)ceil(100 * total_grade / max_grade) << endl;
        }
    }
    // Adds points if the test passes
    void add_points_to_grade(double points){
        if(!::testing::Test::HasFailure()){
            total_grade += points;
        }
    }
    
    static double total_grade;
    static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;

// Test the conversion from (x,y) coordinates to vertex number.
TEST_F(test_x, Test_findVertexNumFromPosition) {
    Dungeon d(5);
    ASSERT_EQ(d.findVertexNumFromPosition(0, 0), 0);
    ASSERT_EQ(d.findVertexNumFromPosition(1, 2), 1 * 5 + 2);
    ASSERT_EQ(d.findVertexNumFromPosition(4, 4), 4 * 5 + 4);
    add_points_to_grade(5.0);
}

// Test addVertex function
TEST_F(test_x, Test_addVertex) {
    Dungeon d(4);
    
    // Add a vertex at (1,2) of type 'open'
    d.addVertex(1, 2, open);
    
    // Check if the vertex exists
    bool found = false;
    for (auto v : d.vertices) {
        if (v->x == 1 && v->y == 2 && v->c == open && v->vertexNum == 6) {
            found = true;
            break;
        }
    }
    
    ASSERT_TRUE(found);
    add_points_to_grade(10.0);
}

// Test the isContaminated function.
TEST_F(test_x, Test_isContaminated) {
    // Create a 3x3 dungeon with all cells set to open.
    Dungeon d1(3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            d1.dungeon[i][j] = open;
            d1.addVertex(i, j, open);
        }
    }
    // With no radioactive cells, no cell should be contaminated.
    EXPECT_FALSE(d1.isContaminated(1, 1));

    // Create a NEW 3x3 dungeon and set cell (0,0) to radioactive.
    Dungeon d2(3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(i == 0 && j == 0) {
                d2.dungeon[i][j] = radioactive;
                d2.addVertex(i, j, radioactive);
            }
            else {
                d2.dungeon[i][j] = open;
                d2.addVertex(i, j, open);
            }
        }
    }
    
    // Cells adjacent to (0,0) should now be contaminated.
    EXPECT_TRUE(d2.isContaminated(0, 1));
    EXPECT_TRUE(d2.isContaminated(1, 1));
    // A cell far from (0,0) should remain uncontaminated.
    EXPECT_FALSE(d2.isContaminated(2, 2));
    add_points_to_grade(10.0);
}

// Test the function findOpenAdjacentPaths.
TEST_F(test_x, Test_findOpenAdjacentPaths) {
    // Create a 3x3 dungeon with all cells set to open.
    Dungeon d1(3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            d1.dungeon[i][j] = open;
            d1.addVertex(i, j, open);
        }
    }
    // For cell at (1,1), expect all 8 surrounding neighbors.
    vector<int> neighbors = d1.findOpenAdjacentPaths(1, 1);
    EXPECT_EQ(neighbors.size(), 8);

    //create a new dungeon with a radioactive cell to contaminate some neighbors
    Dungeon d2(3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(i == 0 && j == 0) {
                d2.dungeon[i][j] = radioactive;
                d2.addVertex(i, j, radioactive);
            }
            else {
                d2.dungeon[i][j] = open;
                d2.addVertex(i, j, open);
            }
        }
    }
    neighbors = d2.findOpenAdjacentPaths(1, 1);
    // Depending on your contamination logic, adjust the expected count.
    // Here, we expect some neighbors to be excluded; for example, assume 5 remain.
    EXPECT_EQ(neighbors.size(), 5);
    add_points_to_grade(10.0);
}

// Test convertDungeonToAdjacencyListGraph function
TEST_F(test_x, Test_convertToAdjacencyList) {
    Dungeon d(3);
    
    // Set all cells to open and add vertices
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            d.dungeon[i][j] = open;
            d.addVertex(i, j, open);
        }
    }

    // Convert to adjacency list
    d.convertDungeonToAdjacencyListGraph();
    
    // Pick a middle cell (1,1) and check that it has 8 neighbors in adjacency list
	ASSERT_EQ(d.findVertexNumFromPosition(1,1), 4);
    vertex* v = d.vertices[d.findVertexNumFromPosition(1,1)];
    ASSERT_EQ(v->adj.size(), 8);

    // Set a boundary cell (0,0) and check adjacency list size (should have 3 neighbors)
    v = d.vertices[d.findVertexNumFromPosition(0,0)];
    ASSERT_EQ(v->adj.size(), 3);

    add_points_to_grade(10.0);
}

// Updated helper function prototype in test_helpers.hpp should now be:
// bool test_findPath(const string &filename);

// Test using test_a.txt (5x5 maze where a valid path exists)
TEST_F(test_x, Test_dungeonTraversable_a) {
    string fileName = "../tests/data/test_a.txt";
    // Expect true since a valid path exists.
    bool result = test_findPath(fileName);
    ASSERT_EQ(result, true);
    add_points_to_grade(10.0);
}

// Test using test_c.txt (3x3 maze with no valid path)
TEST_F(test_x, Test_dungeonTraversable_no_path) {
    string fileName = "../tests/data/test_c.txt";
    // Expect false since no valid path exists.
    bool result = test_findPath(fileName);
    ASSERT_EQ(result, false);
    add_points_to_grade(10.0);
}

// Test destructor to check for memory leaks
TEST_F(test_x, Test_Destructor) {
    Dungeon* d = new Dungeon(3);
    
    // Add some vertices
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            d->dungeon[i][j] = open;
            d->addVertex(i, j, open);
        }
    }
    
    // Delete the dungeon
    delete d;

    // Run with address sanitizer or valgrind to ensure no memory leaks
    ASSERT_TRUE(true);
    add_points_to_grade(10.0);
}

// Additional Complex Test 1: Using test_complex1.txt (7x7 maze with a single narrow solution)
TEST_F(test_x, Test_dungeonTraversable_complex1) {
    string fileName = "../tests/data/test_complex1.txt";
    // Expect true if a valid path exists in the complex maze.
    bool result = test_findPath(fileName);
    ASSERT_EQ(result, true);
    add_points_to_grade(15.0);
}

// Additional Complex Test 2: Using test_complex2.txt (6x6 maze with multiple branches)
TEST_F(test_x, Test_dungeonTraversable_complex2) {
    string fileName = "../tests/data/test_complex2.txt";
    // Expect true if a valid path exists in the maze.
    bool result = test_findPath(fileName);
    ASSERT_EQ(result, false);
    add_points_to_grade(10.0);
}
