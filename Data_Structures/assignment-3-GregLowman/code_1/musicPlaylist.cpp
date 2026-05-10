#include "musicPlaylist.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

MusicPlaylist::MusicPlaylist() {
    head = nullptr;
}

MusicPlaylist::MusicPlaylist(Song* song) {
    head = song;
}

Song* MusicPlaylist::getFirstSong(){
    return this->head;
}

/**
 * Prints the song in [ name, artists, <3/<3 ] format.
 */
void Song::displaySong(){
    if (this->liked)
    {
        cout << "[ " << this->songName << ", " << this->artistNames << ", <3 ]";
    }
    else
    {
        cout << "[ " << this->songName << ", " << this->artistNames << ", </3 ]";
    }
}

/**
 * Returns true if the playlist has no songs.
 */
bool MusicPlaylist::isEmpty(){
    if(head == nullptr) {
        return true;
    }
    return false;
}

/**
 * Prints every song in the playlist separated by " -> ", ending with "NULL".
 */
void MusicPlaylist::displayPlaylist(){
    Song *current;
    current = head;
    cout << "Displaying songs\n";
    cout << "==================\n";
    while(current != nullptr) {
        if (current->liked)
        {
            cout << "[ " << current->songName << ", " << current->artistNames << ", <3 ] -> ";
        }
        else
        {
            cout << "[ " << current->songName << ", " << current->artistNames << ", </3 ] -> ";
        }
        current = current->next;
    }
    cout << "NULL\n";
    cout << "==================\n";
    return;
}

/**
 * Inserts newSong after previousSong. If previousSong is nullptr, inserts at head.
 *
 * @param previousSong Node after which to insert; nullptr to insert at head.
 * @param newSong Node to insert.
 */
void MusicPlaylist::addSong(Song* previousSong, Song* newSong){
    if(previousSong == nullptr)
    {
        newSong->next = head;
        head = newSong;
        return;
    }
    newSong->next = previousSong->next;
    previousSong->next = newSong;
    return;
}

/**
 * Returns the first Song whose songName matches name, or nullptr if not found.
 *
 * @param name Song name to search for.
 */
Song* MusicPlaylist::searchSongByName(std::string name){
    Song *current;
    current = head;
    while (current != nullptr)
    {
        if (current->songName == name)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

/**
 * Toggles the liked flag on the song matching name and prints confirmation.
 * Prints "Song not found." if no match exists.
 *
 * @param name Song name to like/unlike.
 */
void MusicPlaylist::likeSong(std::string name){
    Song *current;
    current = searchSongByName(name);
    if (current != nullptr)
    {
        current -> liked = true;
        cout << "Song: " << current->songName << " liked!" << endl;
    }
    else
    {
        cout << "Song not found." << endl;
    }
    return;
}

/**
 * Prints all songs whose artistNames matches name.
 * Prints "No songs found." if there are no matches.
 *
 * @param name Artist name to search for.
 */
void MusicPlaylist::displayAllSongsbyArtist(std::string name){
    Song *current;
    current = head;
    bool found = false;
    while (current != nullptr)
    {
        if (current->artistNames == name)
        {
            current->displaySong();
            cout << endl;
            found = true;
        }
        current = current->next;
    }
    if(!found)
    {
        cout << "No songs found." << endl;
    }
    return;
}
