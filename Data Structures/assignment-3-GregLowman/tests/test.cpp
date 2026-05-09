// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/musicPlaylist.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <iomanip>

using namespace std;

class test : public ::testing::Test {
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

double test::total_grade = 0;
double test::max_grade = 100;


/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

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

std::string readFileInto(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

void buildMusicPlaylist(MusicPlaylist* mp) {
	
    Song* Shape = new Song {"Shape of You", "Ed Sheeran", 1, nullptr};
	Song* Closer = new Song {"Closer", "Chainsmokers", 0, nullptr};
	Song* Perfect = new Song {"Perfect", "Ed Sheeran", 0, nullptr};
	Song* Hello = new Song {"Hello", "Adele", 0, nullptr};
    Song* Despacito = new Song {"Despacito", "Luis Fonsi, Daddy Yankee", 1, nullptr};

    mp->addSong(nullptr, Shape);
    mp->addSong(Shape, Closer);
    mp->addSong(Closer, Perfect);
    mp->addSong(Perfect, Hello);
    mp->addSong(Hello, Despacito);
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

/*
The displaySong and displayPlaylist functions are checked as part of other tests.
*/

// Test the isEmpty() function [10 POINTS]
TEST_F(test, TestIsEmpty) {
	MusicPlaylist* musicPlaylist = new MusicPlaylist();
	// When the playlist is not empty
	bool isEmptyValue = musicPlaylist->isEmpty();
	ASSERT_EQ(isEmptyValue, true);
	add_points_to_grade(5);

	// When the playlist is populated
	Song* newSong = new Song({"Shape of You", "Ed Sheeran", 1, nullptr});
	MusicPlaylist* musicPlaylist2 = new MusicPlaylist(newSong);
	isEmptyValue = musicPlaylist2->isEmpty();
	ASSERT_EQ(isEmptyValue, false);
	add_points_to_grade(5);
}

// Test the addSong() function [20 POINTS]
TEST_F(test, TestAddSong) {
    MusicPlaylist* musicPlaylist = new MusicPlaylist();

    Song* Shape = new Song({"Shape of You", "Ed Sheeran", 1, nullptr});
	Song* Closer = new Song({"Closer", "Chainsmokers", 0, nullptr});
	Song* Perfect = new Song({"Perfect", "Ed Sheeran", 1, nullptr});
	Song* Hello = new Song({"Hello", "Adele", 0, nullptr});
	//Redirect output of STD
	testing::internal::CaptureStdout();

	// When previousSong is nullptr
	// When the list is empty
	musicPlaylist->addSong(nullptr, Shape);
	musicPlaylist->displayPlaylist();
	string addSongOut = testing::internal::GetCapturedStdout();
	string expectedAddSongOut = "Displaying songs\n==================\n[ Shape of You, Ed Sheeran, <3 ] -> NULL\n==================\n";
	ASSERT_EQ(expectedAddSongOut, addSongOut);
	add_points_to_grade(5);

	testing::internal::CaptureStdout();
	// When previousSong is null
	// and the list is not empty
	musicPlaylist->addSong(nullptr, Closer);
	musicPlaylist->displayPlaylist();
	addSongOut = testing::internal::GetCapturedStdout();
	expectedAddSongOut = "Displaying songs\n==================\n[ Closer, Chainsmokers, </3 ] -> [ Shape of You, Ed Sheeran, <3 ] -> NULL\n==================\n";
	ASSERT_EQ(expectedAddSongOut, addSongOut);
	add_points_to_grade(5);

	testing::internal::CaptureStdout();
	// Insert somewhere in the middle
	musicPlaylist->addSong(Closer, Perfect);
	musicPlaylist->displayPlaylist();
	addSongOut = testing::internal::GetCapturedStdout();
	expectedAddSongOut = "Displaying songs\n==================\n[ Closer, Chainsmokers, </3 ] -> [ Perfect, Ed Sheeran, <3 ] -> [ Shape of You, Ed Sheeran, <3 ] -> NULL\n==================\n";
	ASSERT_EQ(expectedAddSongOut, addSongOut);
	add_points_to_grade(5);

	testing::internal::CaptureStdout();
	// Insert at the end
	musicPlaylist->addSong(Shape, Hello);
	musicPlaylist->displayPlaylist();
	addSongOut = testing::internal::GetCapturedStdout();
	expectedAddSongOut = "Displaying songs\n==================\n[ Closer, Chainsmokers, </3 ] -> [ Perfect, Ed Sheeran, <3 ] -> [ Shape of You, Ed Sheeran, <3 ] -> [ Hello, Adele, </3 ] -> NULL\n==================\n";
	ASSERT_EQ(expectedAddSongOut, addSongOut);
	add_points_to_grade(5);	
}

// Test the searchSongByName() function [10 POINTS]
TEST_F(test, TestSearchSongByName) {
	MusicPlaylist* musicPlaylist = new MusicPlaylist();
	// Check for empty list
	Song* historyPtr = musicPlaylist->searchSongByName("Perfect");
	ASSERT_EQ(historyPtr, nullptr);
	add_points_to_grade(2);

	testing::internal::CaptureStdout();
	buildMusicPlaylist(musicPlaylist);
	string MusicPlaylistOut = testing::internal::GetCapturedStdout(); // Ignore

	// Hit case
	historyPtr = musicPlaylist->searchSongByName("Perfect");
	ASSERT_NE(historyPtr, nullptr);
	ASSERT_EQ(historyPtr->songName, "Perfect");
	add_points_to_grade(4);

	// Miss case
	historyPtr = musicPlaylist->searchSongByName("Set Fire to the Rain");
	ASSERT_EQ(historyPtr, nullptr);
	add_points_to_grade(4);		
}

// Test the likeSong() function [10 POINTS]
TEST_F(test, TestLikeSong) {
	MusicPlaylist* musicPlaylist = new MusicPlaylist();

	// If the list is empty
	testing::internal::CaptureStdout();
	musicPlaylist->likeSong("Perfect");
	string LikeSongOut = testing::internal::GetCapturedStdout();
	string expectedLikeSongOut = "Song not found.\n";
	ASSERT_EQ(expectedLikeSongOut, LikeSongOut);
	add_points_to_grade(5);

	// Populate the playlist
	testing::internal::CaptureStdout();
	buildMusicPlaylist(musicPlaylist);
	string MusicPlaylistOut = testing::internal::GetCapturedStdout(); // Ignore

	testing::internal::CaptureStdout();
	musicPlaylist->likeSong("Perfect");
	LikeSongOut = testing::internal::GetCapturedStdout();
	expectedLikeSongOut = "Song: Perfect liked!\n";
	ASSERT_EQ(expectedLikeSongOut, LikeSongOut);
	add_points_to_grade(5);
}

// Test the displayAllSongsbyArtist() function [20 POINTS]
TEST_F(test, TestDisplayAllSongbyArtist) {
	MusicPlaylist* checkAllSongs = new MusicPlaylist();
	Song* palm_trees = new Song({"Palm Trees", "Flatbush Zombies", true, nullptr});
	Song* void_ = new Song({"Void", "Pouya", false, nullptr});
	Song* phonk_demon = new Song({"Phonk Demon", "Lil revive", false, nullptr});
	Song* thug_waffle = new Song({"Thug Waffle", "Flatbush Zombies", true, nullptr});
	checkAllSongs->addSong(nullptr, palm_trees);
	checkAllSongs->addSong(palm_trees, void_);
	checkAllSongs->addSong(void_, phonk_demon);
	checkAllSongs->addSong(phonk_demon, thug_waffle);

	testing::internal::CaptureStdout();
	checkAllSongs->displayAllSongsbyArtist("Eminem");
	string noArtist = testing::internal::GetCapturedStdout();
	string expectedOutputEmpty = "No songs found.\n";
	ASSERT_EQ(expectedOutputEmpty, noArtist);
	add_points_to_grade(10);

	testing::internal::CaptureStdout();
	checkAllSongs->displayAllSongsbyArtist("Flatbush Zombies");
	string PlaylistOut = testing::internal::GetCapturedStdout();
	string expectedOutput = "[ Palm Trees, Flatbush Zombies, <3 ]\n[ Thug Waffle, Flatbush Zombies, <3 ]\n";
	ASSERT_EQ(expectedOutput, PlaylistOut);
	add_points_to_grade(10);
}


// Test the entire program [30 POINTS]
TEST_F(test, TestApp_1){
	string desired = readFileIntoString("../tests/expected_1.txt");
	string resp = exec("./run_app ../tests/input_1.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_2.txt");
	resp = exec("./run_app ../tests/input_2.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_3.txt");
	resp = exec("./run_app ../tests/input_3.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);
}
