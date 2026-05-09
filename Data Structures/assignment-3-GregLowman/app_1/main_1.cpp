#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "../code_1/musicPlaylist.hpp"

using namespace std;

void displayMenu();
Song* getNewSong(string input);

/*
* The MAIN function is complete. DO NOT MODIFY!
*/
int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Usage: ./run_app <inputfilename>" << endl;
        return 0;
    } else {
        ifstream input;
        input.open(argv[1]); 

        if(!input.is_open()) {
            cout <<"File does not exist / unable to open. Exiting.";
            return 1;
        } else {

            MusicPlaylist* playlist = new MusicPlaylist();
            string line;
            while(true) {
                displayMenu();
                Song* prevSong = nullptr;
                Song* newSong = nullptr;
                getline(input, line);
                int option = stoi(line);
                cout<<"Option is: "<<option<<endl;
                switch (option) {
                    case 1: //Check if the playlist is empty
                    cout << ((playlist->isEmpty()) ? "Empty!\n" : "Not empty!\n"); break;
                    case 2: //Display the playlist;
                    playlist->displayPlaylist(); break;
                    case 3: //Add new song
                    getline(input, line);
                    cout<<line<<endl;
                    newSong = getNewSong(line);
                    getline(input, line);
                    cout<<line<<endl;
                    prevSong = playlist->searchSongByName(line);
                    playlist->addSong(prevSong, newSong);
                    cout<<"Done!"<<endl ;break; 
                    
                    case 4: // Search song by name
                    getline(input, line);
                    cout<<line<<endl;
                    if (Song* tempSong = playlist->searchSongByName(line)) {
                        tempSong->displaySong();
                    } else {
                        cout <<"No song found";
                    }
                    cout << endl; break;

                    case 5: //like Song
                    getline(input, line);
                    cout<<line<<endl;
                    playlist->likeSong(line);
                    break;
                    case 6: // get playlist by artist
                    getline(input, line);
                    cout<<line<<endl;
                    playlist->displayAllSongsbyArtist(line);
                    break;
                    case 7: cout <<"Quitting!\n"; return 0;
                    case -1: cout<<"Invalid option! Exiting.\n"<<endl; return 1;
                }
            }
            
            
        }
    }
    return 0;
}




/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Is the playlist empty?" << endl;
    cout << " 2. Display the playlist." << endl;
    cout << " 3. Add new song." << endl;
    cout << " 4. Search song by name." << endl;
    cout << " 5. Like a song." << endl;
    cout << " 6. Get playlist by artist." << endl;
    cout << " 7. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

Song* getNewSong(string line) {
    stringstream ss(line);
    string token,artist;
    getline(ss, token, ';');
    Song* newSong = new Song();
    newSong->songName = token;
    getline(ss, token, ';');
    stringstream artists(token);
    newSong->artistNames = token;
    getline(ss, token, ';');
    if (token == "True") {
        newSong->liked = true;
    } else {
        newSong->liked = false;
    }

    newSong->next = nullptr;
    return newSong;
}