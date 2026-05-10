// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/MusicPlaylist.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

class test : public ::testing::Test 
{
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		srand(time(0)); //Set the random seed
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


/**
 * Takes a music playlist and adds songs to the queue. Random number of songs between 3-9.
 * Default Setup:Palm Trees->Void->Thug Waffle->44 Bars->Kaancepts->Tortured Genius->Smells like teen spirit
 * @param playlist The playlist to be modified
 * @return Number of songs in the playlist
 */
int buildMusicPlaylist(MusicPlaylist*& playlist, bool random = false){
	Song * palmTrees = new Song({"Palm Trees", "Flatbush Zombies", false, NULL});
	Song * void_ = new Song({"Void", "Pouya", false, NULL});
	Song * thugWaffle = new Song({"Thug Waffle", "Flatbush Zombies", false, NULL});
	Song * bars_44 = new Song({"44 Bars", "Logic", false, NULL});
	Song * kaan = new Song({"KAANCEPTS 2", "K.A.A.N.", false, NULL});
	Song * torturedGenius = new Song({"Tortured Genius", "Eazy Mac", false, NULL});
	Song * smells = new Song({"Smells Like Teen Spirit", "Nirvana", false, NULL});
	Song * livin = new Song({"Livin' on a Prayer", "K.A.A.N.", false, NULL});
	Song * strawberry = new Song({"Strawberry Fields Forever", "The Beatles", false, NULL});

	//Default playlist is 7
	int numberSongs = 7;

	//Builds a playlist of the following
	playlist->addSong(NULL, palmTrees);
	playlist->addSong(palmTrees, void_);
	playlist->addSong(void_, thugWaffle);
	
	if(random){
		numberSongs = rand() % 7 + 3;

		//Randomizes the songs being built into the playlist for length and values
		switch (numberSongs)
		{
			case 4:
				playlist->addSong(thugWaffle, bars_44);
				break;
			case 5:
				playlist->addSong(thugWaffle, bars_44);
				playlist->addSong(bars_44, kaan);
				break;
			case 6:
				playlist->addSong(thugWaffle, bars_44);
				playlist->addSong(bars_44, torturedGenius);
				playlist->addSong(torturedGenius, kaan);
				break;
			case 7:
				playlist->addSong(thugWaffle, bars_44);
				playlist->addSong(bars_44, kaan);
				playlist->addSong(kaan, torturedGenius);
				playlist->addSong(torturedGenius, smells);
				break;
			case 8:
				playlist->addSong(thugWaffle, bars_44);
				playlist->addSong(bars_44, torturedGenius);
				playlist->addSong(torturedGenius, smells);
				playlist->addSong(smells, kaan);
				playlist->addSong(kaan, livin);
				break;
			case 9:
				playlist->addSong(thugWaffle, bars_44);
				playlist->addSong(bars_44, kaan);
				playlist->addSong(kaan, torturedGenius);
				playlist->addSong(torturedGenius, smells);
				playlist->addSong(smells, livin);
				playlist->addSong(livin, strawberry);
				break;
			default:
				break;
		}
	}else{
		playlist->addSong(thugWaffle, bars_44);
		playlist->addSong(bars_44, kaan);
		playlist->addSong(kaan, torturedGenius);
		playlist->addSong(torturedGenius, smells);
		//Palm Trees->Void->Thug Waffle->44 Bars-> Kaancepts -> Tortured Genius -> Smells like teen spirit
	}
	return numberSongs;
}

/**
 * Modifies the playlist songs to create a loop in the playlist. If a valid song is passed, creates a loop at that song 
 * @param playlist The playlist to be modified
 * @param SongToLoop Defaults to nullptr. Creates a loop at the corresponding song
 * @return The total number of songs stuck in the loop
 */
int createLoopInPlaylist(MusicPlaylist *& playlist, Song* SongToLoop = nullptr){
	Song* current = playlist->getFirstSong();
	Song* prev = nullptr;
	int counter = 0;
	if(!SongToLoop){
		while(current){
			prev = current;
			current = current->next;
			counter++;
		}
		
		//Find the midway point of the song LL and point the end node to it
		current = playlist->getFirstSong();
		for(int x = 1; x < counter/2; x++){
			current = current->next;
		}
		prev->next = current;
		//Returns either 1/2 counter + 1 or 2 based on even odd
		return counter/2+(counter%2==0 ? 1 : 2);
	}else{
		Song* target = nullptr;
		
		while(current){
			//If the songToLoop matches the current song, set our target to ti
			if(SongToLoop == current){
				target = SongToLoop;
			}
			//If the target song is found, start the counter to get the loop size
			if(target != nullptr){
				counter++;
			}
			prev = current;
			current = current->next;
		}
		//Set the end node's next to the target song
		prev->next = target;
		return target ? counter : -1;
	}

}


/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

/**
 * Test the findLoopInPlaylist [30 POINTS]
 * Using srand() on line 22, we can set the seed of our number generator to get the same number every time.
 * Test is built using randomization to create better checks for the loop.
 */ 
TEST_F(test, TestFindLoopInPlaylist) {
	MusicPlaylist* musicPlaylist = new MusicPlaylist;

	// check answer for empty list
	const int expectedEmptyLength = -1;
	int receivedLength = musicPlaylist->findLoopInPlaylist();
	ASSERT_EQ(receivedLength, expectedEmptyLength);
	add_points_to_grade(10);

	// Create a normal linked list without a loop
	buildMusicPlaylist(musicPlaylist, true);
	const int expectedNoLoopLength = -1;
	receivedLength = musicPlaylist->findLoopInPlaylist();
	ASSERT_EQ(receivedLength, expectedNoLoopLength);
	add_points_to_grade(10);

	// Builds 1 random lists to check against. Checks against a predefined loop of length 4
	const int expectedLoopLength = createLoopInPlaylist(musicPlaylist, musicPlaylist->searchSongByName("Void"));
	receivedLength = musicPlaylist->findLoopInPlaylist();
	ASSERT_EQ(receivedLength, expectedLoopLength);
	add_points_to_grade(5);
	
	MusicPlaylist* playlist2 = new MusicPlaylist;
	buildMusicPlaylist(playlist2, true);
	const int expectedLoopLength2 = createLoopInPlaylist(playlist2);
	int receivedLength2 = playlist2->findLoopInPlaylist();
	ASSERT_EQ(receivedLength2, expectedLoopLength2);
	add_points_to_grade(5);
}

// Test the removeSongs function [35 POINTS]
TEST_F(test, TestRemoveSongs) {
	MusicPlaylist* musicPlaylist = new MusicPlaylist;

	testing::internal::CaptureStdout();
	// Check for empty list
	musicPlaylist->removeSongs(10, 20);
	string receivedOut = testing::internal::GetCapturedStdout();
	string expectedOut = "Playlist is Empty\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(1);

	testing::internal::CaptureStdout();
	musicPlaylist->removeSongs(0,0);
	string check = testing::internal::GetCapturedStdout(); //Ignore. 

	//Returns 7
	const int playlistLength = buildMusicPlaylist(musicPlaylist);

	// After Building but with bad start and end
	testing::internal::CaptureStdout();
	musicPlaylist->removeSongs(0, 6);
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Invalid start or end values\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(2);

	// After building but start > end
	testing::internal::CaptureStdout();
	musicPlaylist->removeSongs(4, 2);
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Invalid start or end values\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(2);

	// After building, delete just one node
	testing::internal::CaptureStdout();
	// Removes Tortured Genius
	musicPlaylist->removeSongs(playlistLength-1, playlistLength-1);
	musicPlaylist->displayPlaylist();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Displaying songs\n==================\n[ Palm Trees, Flatbush Zombies, </3 ] -> [ Void, Pouya, </3 ] -> [ Thug Waffle, Flatbush Zombies, </3 ] -> [ 44 Bars, Logic, </3 ] -> [ KAANCEPTS 2, K.A.A.N., </3 ] -> [ Smells Like Teen Spirit, Nirvana, </3 ] -> NULL\n==================\n";
	//Palm Trees->Void->Thug Waffle->44 Bars-> Kaancepts -> Smells like teen spirit
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);

	// After building, delete list except head and tail
	testing::internal::CaptureStdout();
	musicPlaylist->removeSongs(2, 5);
	musicPlaylist->displayPlaylist();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Displaying songs\n==================\n[ Palm Trees, Flatbush Zombies, </3 ] -> [ Smells Like Teen Spirit, Nirvana, </3 ] -> NULL\n==================\n";
	//Palm Trees->Smells like teen spirit
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);

	// After building with good start and end deleting whole list
	testing::internal::CaptureStdout();
	musicPlaylist->removeSongs(1, 2);
	musicPlaylist->displayPlaylist();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Displaying songs\n==================\nNULL\n==================\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);

	// making another for a few more tests
	MusicPlaylist* musicPlaylist2 = new MusicPlaylist;
	testing::internal::CaptureStdout();
	buildMusicPlaylist(musicPlaylist2);
	check = testing::internal::GetCapturedStdout(); //Ignore. 

	// after building, delete just the head
	testing::internal::CaptureStdout();
	musicPlaylist2->removeSongs(1, 1);
	musicPlaylist2->displayPlaylist();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Displaying songs\n==================\n[ Void, Pouya, </3 ] -> [ Thug Waffle, Flatbush Zombies, </3 ] -> [ 44 Bars, Logic, </3 ] -> [ KAANCEPTS 2, K.A.A.N., </3 ] -> [ Tortured Genius, Eazy Mac, </3 ] -> [ Smells Like Teen Spirit, Nirvana, </3 ] -> NULL\n==================\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);

	// after building, delete just the tail
	testing::internal::CaptureStdout();
	musicPlaylist2->removeSongs(6, 6);
	musicPlaylist2->displayPlaylist();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Displaying songs\n==================\n[ Void, Pouya, </3 ] -> [ Thug Waffle, Flatbush Zombies, </3 ] -> [ 44 Bars, Logic, </3 ] -> [ KAANCEPTS 2, K.A.A.N., </3 ] -> [ Tortured Genius, Eazy Mac, </3 ] -> NULL\n==================\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);
}

// Test the mergeTwoHistories function [35 POINTS]
// TODO: Modifications still need to be done
TEST_F(test, TestMergeTwoPlaylists) {
	MusicPlaylist* musicPlaylist1 = new MusicPlaylist;
	MusicPlaylist* musicPlaylist2 = new MusicPlaylist;
	MusicPlaylist* musicPlaylistsMerged = new MusicPlaylist;
	
	// Check for merging 2 empty lists 
	testing::internal::CaptureStdout();
	//Returns null songs, resulting in empty merged playlist 
	musicPlaylistsMerged->mergeTwoPlaylists(musicPlaylist1->searchSongByName("empty"), musicPlaylist2->searchSongByName("empty"));
	musicPlaylistsMerged->displayPlaylist();
	string receivedOut = testing::internal::GetCapturedStdout();
	string expectedOut = "Displaying songs\n==================\nNULL\n==================\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(1);

	// check for merging 1 built and one empty list
	testing::internal::CaptureStdout();
	buildMusicPlaylist(musicPlaylist1);
	string check = testing::internal::GetCapturedStdout(); //Ignore. 
	testing::internal::CaptureStdout();
	// 10 is the ID of the colorado page which is the head
	musicPlaylistsMerged->mergeTwoPlaylists(musicPlaylist1->getFirstSong(), musicPlaylist2->searchSongByName("empty"));
	musicPlaylistsMerged->displayPlaylist();
	receivedOut = testing::internal::GetCapturedStdout();
	testing::internal::CaptureStdout();
	musicPlaylist1->displayPlaylist();
	expectedOut = testing::internal::GetCapturedStdout();
	ASSERT_EQ(receivedOut, expectedOut);
	Song *mergedHead = musicPlaylistsMerged->getFirstSong();
	Song *oneHead = musicPlaylist1->getFirstSong();
	// Has to be the same node, not just having the same contents
	ASSERT_EQ(mergedHead, oneHead);
	add_points_to_grade(11);

	// check for merging 2 built lists
	testing::internal::CaptureStdout();
	buildMusicPlaylist(musicPlaylist2);
	check = testing::internal::GetCapturedStdout(); //Ignore. 
	testing::internal::CaptureStdout();

	
	musicPlaylistsMerged->mergeTwoPlaylists(musicPlaylist1->getFirstSong(), musicPlaylist2->getFirstSong());
	musicPlaylistsMerged->displayPlaylist();
	receivedOut = testing::internal::GetCapturedStdout();
	//2 Playlists with the same songs (different nodes) merged so it will look "duplicated"
	expectedOut = "Displaying songs\n==================\n[ Palm Trees, Flatbush Zombies, </3 ] -> [ Palm Trees, Flatbush Zombies, </3 ] -> [ Void, Pouya, </3 ] -> [ Void, Pouya, </3 ] -> [ Thug Waffle, Flatbush Zombies, </3 ] -> [ Thug Waffle, Flatbush Zombies, </3 ] -> [ 44 Bars, Logic, </3 ] -> [ 44 Bars, Logic, </3 ] -> [ KAANCEPTS 2, K.A.A.N., </3 ] -> [ KAANCEPTS 2, K.A.A.N., </3 ] -> [ Tortured Genius, Eazy Mac, </3 ] -> [ Tortured Genius, Eazy Mac, </3 ] -> [ Smells Like Teen Spirit, Nirvana, </3 ] -> [ Smells Like Teen Spirit, Nirvana, </3 ] -> NULL\n==================\n";
	ASSERT_EQ(receivedOut, expectedOut);
	mergedHead = musicPlaylistsMerged->getFirstSong();
	oneHead = musicPlaylist1->getFirstSong();
	Song * twoHead = musicPlaylist2->getFirstSong();

	ASSERT_EQ(mergedHead, oneHead);
	add_points_to_grade(5);
	ASSERT_EQ(mergedHead->next, twoHead);
	add_points_to_grade(5);

	// check for merging 2 built lists of unequal length
	MusicPlaylist* musicPlaylist3 = new MusicPlaylist;
	MusicPlaylist* musicPlaylist4 = new MusicPlaylist;
	testing::internal::CaptureStdout();
	buildMusicPlaylist(musicPlaylist3);
	Song * unique = new Song {"Uniquely", "You", false, NULL};
    Song * totally = new Song {"Totally Ridiculous", "Ridiculous Totally", true, nullptr};
    Song * vibin = new Song {"Vibin", "The vibe guys", false, NULL};
	musicPlaylist4->addSong(nullptr, unique);
    musicPlaylist4->addSong(unique, totally);
    musicPlaylist4->addSong(totally, vibin);
	check = testing::internal::GetCapturedStdout(); //Ignore. 
	testing::internal::CaptureStdout();
	musicPlaylistsMerged->mergeTwoPlaylists(musicPlaylist3->getFirstSong(), musicPlaylist4->getFirstSong());
	musicPlaylistsMerged->displayPlaylist();
	receivedOut = testing::internal::GetCapturedStdout();
	// Palm Trees->Uniquely->Void->Totally Ridiculous->Thug Waffle->Vibin->44 bars->KAANCEPTS 2->Tortured Genius->Smells Like Teen Spirit->NULL
	expectedOut = "Displaying songs\n==================\n[ Palm Trees, Flatbush Zombies, </3 ] -> [ Uniquely, You, </3 ] -> [ Void, Pouya, </3 ] -> [ Totally Ridiculous, Ridiculous Totally, <3 ] -> [ Thug Waffle, Flatbush Zombies, </3 ] -> [ Vibin, The vibe guys, </3 ] -> [ 44 Bars, Logic, </3 ] -> [ KAANCEPTS 2, K.A.A.N., </3 ] -> [ Tortured Genius, Eazy Mac, </3 ] -> [ Smells Like Teen Spirit, Nirvana, </3 ] -> NULL\n==================\n";
	ASSERT_EQ(receivedOut, expectedOut);
	Song *mergedSecondNode = musicPlaylistsMerged->getFirstSong();
	Song *threeHead = musicPlaylist3->getFirstSong();
	Song *fourHead = musicPlaylist4->getFirstSong();
	// Has to be the same node, not just having the same contents
	ASSERT_EQ(mergedSecondNode, threeHead);
	add_points_to_grade(6);
	ASSERT_EQ(mergedSecondNode->next, fourHead);
	add_points_to_grade(7);
}