// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions below to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/MovieCollection.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

string movieNames1[] = {"Hamilton", "Interstellar", "Saving Private Ryan", "The Green Mile"};
string directorNames1[] = {"Thomas Kail", "Christopher Nolan", "Steven Spielberg", "Frank Darabont"};
string genre1[] = {"Biography", "Adventure", "Drama", "Crime"};
int len1 = 4;

string movieNames2[] = {""};
string directorNames2[] = {""};
string genre2[] = {""};
int len2 = 0;

string movieNames3[] = {"The Silence of the Lambs", "Star Wars", "It's a Wonderful Life", "Joker", "Whiplash"};
string directorNames3[] = {"Jonathan Demme", "George Lucas", "Frank Capra", "Todd Phillips", "Damien Chazelle"};
string genre3[] = {"Crime", "Action", "Drama", "Crime", "Drama"};
int len3 = 5;

string movieNames4[] = {"The Prestige", "The Departed", "The Pianist", "Gladiator", "The Usual Suspects"};
string directorNames4[] = {"Christopher Nolan", "Martin Scorsese", "Roman Polanski", "Ridley Scott", "Bryan Singer"};
string genre4[] = {"Drama", "Crime", "Biography", "Action", "Crime"};
int len4 = 5;

string movieNames5[] = {"Hamilton", "Interstellar", "Saving Private Ryan", "The Green Mile", "Joker"};
string directorNames5[] = {"Thomas Kail", "Christopher Nolan", "Steven Spielberg", "Frank Darabont","Todd Phillips"};
string genre5[] = {"Biography", "Adventure", "Drama", "Crime","Crime"};
int len5 = 5;


// Test Remove Movie
// Grade Points: 20
TEST_F(test_x, TestRemoveMovie){
	//Movie found not at root and Deleted
	MovieCollection* rootNode = createMovieCollection(movieNames1, directorNames1, genre1, len1);
	string actual = testRemoveMovie(rootNode, "Hamilton");
	string expected = "MOVIE: Interstellar DIRECTOR: Christopher Nolan GENRE: Adventure\nMOVIE: Saving Private Ryan DIRECTOR: Steven Spielberg GENRE: Drama\nMOVIE: The Green Mile DIRECTOR: Frank Darabont GENRE: Crime\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
	

// 	//Movie found at root and Deleted
	rootNode = createMovieCollection(movieNames1, directorNames1, genre1, len1);
	actual = testRemoveMovie(rootNode, "Interstellar");
	expected = "MOVIE: Hamilton DIRECTOR: Thomas Kail GENRE: Biography\nMOVIE: Saving Private Ryan DIRECTOR: Steven Spielberg GENRE: Drama\nMOVIE: The Green Mile DIRECTOR: Frank Darabont GENRE: Crime\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	//Movie not found
	rootNode = createMovieCollection(movieNames1, directorNames1, genre1, len1);
	actual = testRemoveMovie(rootNode, "The Silence of the Lambs");
	expected = "Movie not found!\nMOVIE: Hamilton DIRECTOR: Thomas Kail GENRE: Biography\nMOVIE: Interstellar DIRECTOR: Christopher Nolan GENRE: Adventure\nMOVIE: Saving Private Ryan DIRECTOR: Steven Spielberg GENRE: Drama\nMOVIE: The Green Mile DIRECTOR: Frank Darabont GENRE: Crime\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

// 	//Empty Collections
	rootNode = createMovieCollection(movieNames2, directorNames2, genre2, len2);
	actual = testRemoveMovie(rootNode, "The Silence of the Lambs");
	expected = "Movie not found!\nCollection is empty.\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
}

//Test Rotate Movie Collection
//Grade Points: 20
TEST_F(test_x, TestRotateCollection){
	
	// Movie found not at root to rotate
	MovieCollection* rootNode = createMovieCollection(movieNames1, directorNames1, genre1, len1);
	string actual = testRotateCollection(rootNode, "The Green Mile");
	string expected = "MOVIE: Hamilton DIRECTOR: Thomas Kail GENRE: Biography\nMOVIE: Interstellar DIRECTOR: Christopher Nolan GENRE: Adventure\nMOVIE: Saving Private Ryan DIRECTOR: Steven Spielberg GENRE: Drama\nMOVIE: The Green Mile DIRECTOR: Frank Darabont GENRE: Crime\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	//Movie not found
	rootNode = createMovieCollection(movieNames1, directorNames1, genre1, len1);
	actual = testRotateCollection(rootNode, "Interstellar");
	expected = "MOVIE: Hamilton DIRECTOR: Thomas Kail GENRE: Biography\nMOVIE: Saving Private Ryan DIRECTOR: Steven Spielberg GENRE: Drama\nMOVIE: Interstellar DIRECTOR: Christopher Nolan GENRE: Adventure\nMOVIE: The Green Mile DIRECTOR: Frank Darabont GENRE: Crime\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
	

	//Movie found at root to rotate 
	rootNode = createMovieCollection(movieNames1, movieNames1, genre1, len1);
	actual = testRotateCollection(rootNode, "Hamilton");
	expected = "MOVIE: Interstellar DIRECTOR: Interstellar GENRE: Adventure\nMOVIE: Hamilton DIRECTOR: Hamilton GENRE: Biography\nMOVIE: Saving Private Ryan DIRECTOR: Saving Private Ryan GENRE: Drama\nMOVIE: The Green Mile DIRECTOR: The Green Mile GENRE: Crime\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	//Empty Collections
	rootNode = createMovieCollection(movieNames2, directorNames2, genre2, len2);
	actual = testRotateCollection(rootNode, "Hamilton");
	expected = "\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
 }

//Test Closest Parent
//Grade Points: 40
TEST_F(test_x, TestClosestParent){

	MovieCollection* rootNode = nullptr;
	string testCaseSuffix = "\n[GRADER] No leaked memory (Good).\n";

	// Empty collection
	rootNode = createMovieCollection(movieNames2, directorNames2, genre2, len2);
	string actual = testClosestParent(rootNode, "No movie 1", "No movie 2");
	string expected = "Movie not found!\nError - wrong movie name" + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Single movie in collection
	rootNode = createMovieCollection(movieNames2, directorNames2, genre2, len2);
	rootNode->addMovie("The Shawshank Redemption", "Frank Darabont", "Drama");
	actual = testClosestParent(rootNode, "The movie that doesnt exist", "The Shawshank Redemption");
	expected = "Movie not found!\nError - wrong movie name" + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Single movie in collection - Both movies to be searched are the same
	rootNode = createMovieCollection(movieNames2, directorNames2, genre2, len2);
	rootNode->addMovie("The Shawshank Redemption", "Frank Darabont", "Drama");
	actual = testClosestParent(rootNode, "The Shawshank Redemption", "The Shawshank Redemption");
	expected = "The Shawshank Redemption"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Multiple movies in collection - Root is the closest parent
	rootNode = createMovieCollection(movieNames1, directorNames1, genre1, len1);
	actual = testClosestParent(rootNode, "Interstellar", "Saving Private Ryan");
	expected = "Interstellar"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(3);

	// Same test case as the previous, but movie names in the input are flipped
	rootNode = createMovieCollection(movieNames1, directorNames1, genre1, len1);
	actual = testClosestParent(rootNode, "Saving Private Ryan", "Interstellar");
	expected = "Interstellar"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(2);

	// Multiple movies in collection - Non Root node is the closest parent
	rootNode = createMovieCollection(movieNames5, directorNames5, genre5, len5);
	actual = testClosestParent(rootNode, "Joker", "The Green Mile");
	expected = "Saving Private Ryan" +  testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Multiple movie in collection - One node to be compared is the root
	rootNode = createMovieCollection(movieNames5, directorNames5, genre5, len5);
	actual = testClosestParent(rootNode, "Joker", "Hamilton");
	expected = "Hamilton"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Multiple movies in collection - One movies is in the subtree of the other
	rootNode = createMovieCollection(movieNames1, directorNames1, genre1, len1);
	actual = testClosestParent(rootNode, "Interstellar", "Saving Private Ryan");
	expected = "Interstellar" + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Multiple movies in collection - One of the movies to be searched doesnt exist
	rootNode = createMovieCollection(movieNames5, directorNames5, genre5, len5);
	actual = testClosestParent(rootNode, "Interstellar", "No Movie like this");
	expected = "Movie not found!\nError - wrong movie name" + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(3);

	// Multiple movies in collection - Both movies to be searched dont exist
	rootNode = createMovieCollection(movieNames5, directorNames5, genre5, len5);
	actual = testClosestParent(rootNode, "No Movie like this", "No Movie like this either");
	expected = "Movie not found!\nError - wrong movie name"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(2);

 }

//Test Overall Functionality
//Grade Points: 20
TEST_F(test_x, TestMain){
	string desired = readFileIntoString("../tests/output/movieOutput1.txt");
	string resp = exec("./run_app ../tests/input/movies1.csv ../tests/input/movieInput1.txt");
	ASSERT_EQ(desired, resp);
	add_points_to_grade(7.5);
	
	desired = readFileIntoString("../tests/output/movieOutput2.txt");
	resp = exec("./run_app ../tests/input/movies2.csv ../tests/input/movieInput2.txt");
	ASSERT_EQ(desired, resp);
	add_points_to_grade(7.5);
	
	desired = readFileIntoString("../tests/output/movieOutput3.txt");
	resp = exec("./run_app ../tests/input/movies3.csv ../tests/input/movieInput2.txt");
	ASSERT_EQ(desired, resp);
	add_points_to_grade(5);
 }
