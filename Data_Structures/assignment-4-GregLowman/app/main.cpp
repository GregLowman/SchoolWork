
#include "../code/MusicPlaylist.hpp"
#include "../library/MusicPlaylistBase.hpp"
#include <string>
#include <sstream>

void displayMenu();
void handleUserInput(MusicPlaylist& musicPlaylist);
// NO NEED TO EDIT MAIN FILE FOR HW4
/*
 * Purpose: handle the interaction with the user
 * Note: We give you some of the inputs/ ouputs you had to implment last week.
 *       It is up to you to add code to handle the new menu options.
 * @param MusicPlaylist object for carrying linked list operations
 * @return none
 */

vector<std::tuple<std::string, std::string, bool>> songDetails;

void takePlaylistInput(int numSongs) {
    cin.ignore(); // Clear newline character from previous input

    for (int i = 0; i < numSongs; ++i) {
        string inputLine;
        cout << "Enter song details (songName;artistNames;liked): ";
        getline(cin, inputLine);
        stringstream ss(inputLine);
        string songName, artistNames, likedStr;
        getline(ss, songName, ';');
        getline(ss, artistNames, ';');
        getline(ss, likedStr, ';');
        bool liked = (likedStr == "1");
        cout << songName << ";" << artistNames << ";" << liked << endl;
        songDetails.push_back(make_tuple(songName, artistNames, liked));
    }
}

void handleUserInput(MusicPlaylist& musicPlaylist)
{
    int choice = 0; 
    bool quit = false;

    while (!quit) {
        displayMenu();
        cin >> choice;
        cout << "Option is: " << choice << endl;
        switch (choice) {
            case 1: { // Produce loop and find loop length in the playlist
                //DO NOT use any other case once you use case 3 else you might be stuck in infinite loop
                // So quit = true
                if(musicPlaylist.isEmpty()){
                    int numSongs;
                    cout << "How many songs do you want to enter? ";
                    cin >> numSongs;
                    cout << numSongs << endl;
                    takePlaylistInput(numSongs);
                    musicPlaylist.buildMusicPlaylist(numSongs, songDetails);
                    songDetails.clear();
                }
                musicPlaylist.displayPlaylist();
                int lastIndex;
                cout << "Enter the index of the song node where the last node should point: ";
                cin >> lastIndex;
                cout << lastIndex << endl;
                musicPlaylist.produceLoop(lastIndex);
                cout << "Loop created" << "\n";
                cout << "Executing findLoopInPlaylist() Function..." << endl;
                cout << "Loop length = " << musicPlaylist.findLoopInPlaylist() << endl;
                quit = true;
                break;

            } case 2: { // remove part of music playlist
                if(musicPlaylist.isEmpty()){
                    int numSongs;
                    cout << "How many songs do you want to enter? ";
                    cin >> numSongs;
                    cout << numSongs << endl;
                    takePlaylistInput(numSongs);
                    musicPlaylist.buildMusicPlaylist(numSongs, songDetails);
                    songDetails.clear();
                }
                musicPlaylist.displayPlaylist();
                int start, end;
                cout << "Enter the start node number: ";
                cin >> start;
                cout << start << endl;
                cout << "Enter the end node number: ";
                cin >> end;
                cout << end << endl;
                cout << "Executing removeSong() Function..." << endl;
                musicPlaylist.removeSongs(start, end);
                musicPlaylist.displayPlaylist();
                quit = true;
                break;

            } case 3: { // merge music playlists
                MusicPlaylist musicPlaylist1;
                MusicPlaylist musicPlaylist2;
                int numSongs;
                cout << "====== Building Playlist 1 ======" << endl;
                cout << "How many songs do you want to enter? ";
                std::cin >> numSongs;
                cout << numSongs << endl;
                takePlaylistInput(numSongs);
                musicPlaylist1.buildMusicPlaylist(numSongs, songDetails);
                songDetails.clear();
                musicPlaylist1.displayPlaylist();
                cout << "====== Building Playlist 2 ======" << endl;
                int numsong;
                cout << "How many songs do you want to enter? ";
                cin >> numsong;
                cout << numsong << endl;
                takePlaylistInput(numsong);
                musicPlaylist2.buildMusicPlaylist(numsong, songDetails);
                songDetails.clear();
                musicPlaylist2.displayPlaylist();
                cout << "Executing mergeTwoPlaylists() Function..." << endl;
                musicPlaylist.mergeTwoPlaylists(musicPlaylist1.getFirstSong(), musicPlaylist2.getFirstSong());
                musicPlaylist.displayPlaylist();
                quit = true;
                break;

            } 
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}

void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Produce loop and find loop length in the playlist " << endl;
    cout << " 2. Remove part of music playlist " << endl;
    cout << " 3. Merge music playlists " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

int main(int argc, char* argv[])
{
    // DO NOT MODIFY THIS.
    // This is used to read a simulted input from a file. Used in test cases.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.

    // Create a new object for the music playlist linked list.
    MusicPlaylist musicPlaylist;
    handleUserInput(musicPlaylist);
    //cout << "LOOP : " << musicPlaylist.findLoopInPlaylist() << endl;

    return 0;
}