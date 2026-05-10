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

// TestaddMovie_showMovieCollection
// Grade points: 25
TEST_F(test_x, TestaddMovie_showMovieCollection){
    string result;
    string expected;
       
    int len = 0;
    string movie[] = {""};
    string director[] = {""};
    string genre[] = {""};
    
    result = test_add(movie,director, genre, len);
    expected = "[GRADER] Printing movie collection:\nCollection is empty.\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

    int len1 = 1;
    string movie1[] = {"The Dark Knight"};
    string director1[] = {"Christopher Nolan"};
    string genre1[] = {"Action"};
    
    result = test_add(movie1,director1, genre1, len1);
    expected = "[GRADER] Adding:(The Dark Knight, Christopher Nolan, Action)\n[GRADER] Printing movie collection:\nMOVIE: The Dark Knight DIRECTOR: Christopher Nolan GENRE: Action\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    int len2 = 2;
    string movie2[] = {"The Dark Knight","The Shawshank Redemption"};
    string director2[] = {"Christopher Nolan","Frank Darabont"};
    string genre2[] = {"Action","Drama"};
    
    result = test_add(movie2,director2, genre2, len2);
    expected = "[GRADER] Adding:(The Dark Knight, Christopher Nolan, Action)\n[GRADER] Adding:(The Shawshank Redemption, Frank Darabont, Drama)\n[GRADER] Printing movie collection:\nMOVIE: The Dark Knight DIRECTOR: Christopher Nolan GENRE: Action\nMOVIE: The Shawshank Redemption DIRECTOR: Frank Darabont GENRE: Drama\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    int len3 = 3;
    string movie3[] = {"The Dark Knight","The Shawshank Redemption","Schindler's List"};
    string director3[] = {"Christopher Nolan","Frank Darabont","Steven Spielberg"};
    string genre3[] = {"Action","Drama","Biography"};
    
    result = test_add(movie3,director3, genre3, len3);
    expected = "[GRADER] Adding:(The Dark Knight, Christopher Nolan, Action)\n[GRADER] Adding:(The Shawshank Redemption, Frank Darabont, Drama)\n[GRADER] Adding:(Schindler's List, Steven Spielberg, Biography)\n[GRADER] Printing movie collection:\nMOVIE: Schindler's List DIRECTOR: Steven Spielberg GENRE: Biography\nMOVIE: The Dark Knight DIRECTOR: Christopher Nolan GENRE: Action\nMOVIE: The Shawshank Redemption DIRECTOR: Frank Darabont GENRE: Drama\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    


    int len4 = 8;
    string movie4[] = {"The Dark Knight","The Shawshank Redemption","Schindler's List","The Godfather","The Godfather: Part II","Twelve Angry Men","The Lord of the Rings: The Return of the King","Pulp Fiction"};
    string director4[] = {"Christopher Nolan","Frank Darabont","Steven Spielberg","Francis Ford Coppola","Francis Ford Coppola", "Sidney Lumet","Peter Jackson","Quentin Tarantino"};
    string genre4[] = {"Action","Drama","Biography","Crime","Crime", "Crime","Action","Crime"};
    
    result = test_add(movie4,director4, genre4, len4);
	//cout<< result;
    expected = "[GRADER] Adding:(The Dark Knight, Christopher Nolan, Action)\n[GRADER] Adding:(The Shawshank Redemption, Frank Darabont, Drama)\n[GRADER] Adding:(Schindler's List, Steven Spielberg, Biography)\n[GRADER] Adding:(The Godfather, Francis Ford Coppola, Crime)\n[GRADER] Adding:(The Godfather: Part II, Francis Ford Coppola, Crime)\n[GRADER] Adding:(Twelve Angry Men, Sidney Lumet, Crime)\n[GRADER] Adding:(The Lord of the Rings: The Return of the King, Peter Jackson, Action)\n[GRADER] Adding:(Pulp Fiction, Quentin Tarantino, Crime)\n[GRADER] Printing movie collection:\nMOVIE: Pulp Fiction DIRECTOR: Quentin Tarantino GENRE: Crime\nMOVIE: Schindler's List DIRECTOR: Steven Spielberg GENRE: Biography\nMOVIE: The Dark Knight DIRECTOR: Christopher Nolan GENRE: Action\nMOVIE: The Godfather DIRECTOR: Francis Ford Coppola GENRE: Crime\nMOVIE: The Godfather: Part II DIRECTOR: Francis Ford Coppola GENRE: Crime\nMOVIE: The Lord of the Rings: The Return of the King DIRECTOR: Peter Jackson GENRE: Action\nMOVIE: The Shawshank Redemption DIRECTOR: Frank Darabont GENRE: Drama\nMOVIE: Twelve Angry Men DIRECTOR: Sidney Lumet GENRE: Crime\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
}

// TestShowMovie
// Grade Points: 10
TEST_F(test_x, TestShowMovie){
    string movieNames[] = {"The Dark Knight","The Shawshank Redemption","Schindler's List","The Godfather"};
    string directors[] = {"Christopher Nolan","Frank Darabont","Steven Spielberg","Francis Ford Coppola"};
    string genre[] = {"Action","Drama","Biography","Crime"};
	int len = 4;

	string actual = test_show_movie(movieNames, directors, genre, len, "The Dark Knight");
	string expected = "Movie:\n==================\nName :The Dark Knight\nDirector :Christopher Nolan\nGenre :Action\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	actual = test_show_movie(movieNames, directors, genre, len, "Fight Club");
	expected = "Movie not found.\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
}

// TestShowMoviesByDirector (Movies displayed in sorted order)
// Grade Points: 15
TEST_F(test_x, TestShowMoviesByDirector){
	string movieNames[] = {"The Dark Knight","The Shawshank Redemption","Schindler's List","The Godfather"};
    string directors[] = {"Christopher Nolan","Frank Darabont","Steven Spielberg","Francis Ford Coppola"};
    string genre[] = {"Action","Drama","Biography","Crime"};
	int len = 4;

	string actual = test_show_movie_by_director(movieNames, directors, genre, len, "Steven Spielberg");
	string expected = "Movies Directed By: Steven Spielberg\nSchindler's List GENRE: Biography\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string movieNames2[] = {"The Shawshank Redemption","Schindler's List","The Godfather","The Godfather: Part II"};
    string directors2[] = {"Frank Darabont","Steven Spielberg","Francis Ford Coppola","Francis Ford Coppola"};
    string genre2[] = {"Drama","Biography","Crime","Crime"};

	actual = test_show_movie_by_director(movieNames2, directors2, genre2, len, "Francis Ford Coppola");
	expected = "Movies Directed By: Francis Ford Coppola\nThe Godfather: Part II GENRE: Crime\nThe Godfather GENRE: Crime\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	

	actual = test_show_movie_by_director(movieNames2, directors2, genre2, len, "Peter Jackson");
	expected = "Movies Directed By: Peter Jackson\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
 }

// TestPrintLeaves (Movies displayed in sorted order)
// Grade Points: 15
TEST_F(test_x, TestPrintLeaves){
	string movieNames[] = {"The Dark Knight","The Shawshank Redemption","Schindler's List","The Godfather"};
    string directors[] = {"Christopher Nolan","Frank Darabont","Steven Spielberg","Francis Ford Coppola"};
    string genre[] = {"Action","Drama","Biography","Crime"};
	int len = 4;

	string actual = test_print_leaves(movieNames, directors, genre, len);
	string expected = "[GRADER] Result of movies.printLeaves is:\nMOVIE: Schindler's List DIRECTOR: Steven Spielberg GENRE: Biography\nMOVIE: The Godfather DIRECTOR: Francis Ford Coppola GENRE: Crime\n\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string movieNames2[] = {""};
    string directors2[] = {""};
    string genre2[] = {""};
    len = 0;

	actual = test_print_leaves(movieNames2, directors2, genre2, len);
	expected = "[GRADER] Result of movies.printLeaves is:\n\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

    string movieNames3[] = {"The Dark Knight","Schindler's List","The Lord of the Rings: The Return of the King","Pulp Fiction","Inception","Fight Club","Forrest Gump"};
    string directors3[] = {"Christopher Nolan","Steven Spielberg", "Peter Jackson","Quentin Tarantino","Christopher Nolan","David Fincher","Robert Zemeckis"};
    string genre3[] = {"Action","Biography", "Action","Crime","Action","Drama","Drama"};
	len = 7;

	actual = test_print_leaves(movieNames3, directors3, genre3, len);
	expected = "[GRADER] Result of movies.printLeaves is:\nMOVIE: Forrest Gump DIRECTOR: Robert Zemeckis GENRE: Drama\nMOVIE: The Lord of the Rings: The Return of the King DIRECTOR: Peter Jackson GENRE: Action\n\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
 }

// TestGetHeightOfMovieCollection
// Grade Points: 15
TEST_F(test_x, TestGetHeightOfMovieCollection){

	string movieNames[] = {"The Dark Knight","The Shawshank Redemption","Schindler's List","The Godfather"};
    string directors[] = {"Christopher Nolan","Frank Darabont","Steven Spielberg","Francis Ford Coppola"};
    string genre[] = {"Action","Drama","Biography","Crime"};
	int len = 4;

	string actual = test_get_height_of_movie_collection(movieNames, directors, genre, len);
	string expected = "[GRADER]Height of Movie Collection:2\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string movieNames2[] = {"The Dark Knight"};
    string directors2[] = {"Christopher Nolan"};
    string genre2[] = {"Action"};
	len = 1;

	actual = test_get_height_of_movie_collection(movieNames2, directors2, genre2, len);
	expected = "[GRADER]Height of Movie Collection:0\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string movieNames3[] = {""};
	string directors3[] = {""};
	string genre3[] = {""};
	len = 0;

	actual = test_get_height_of_movie_collection(movieNames3, directors3, genre3, len);
	expected = "[GRADER]Empty Tree!\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
 }

// // TestMain
// // Grade Points: 20
TEST_F(test_x, TestMain)
{
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
