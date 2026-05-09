#ifndef MUSIC_PLAYLIST_HPP__
#define MUSIC_PLAYLIST_HPP__
#include <iostream>

using namespace std;

struct Song {
    std::string songName;
    string artistNames;
    bool liked;
    Song* next;

    void displaySong();
};

class MusicPlaylist {
    private:
        Song* head;
    public:
        MusicPlaylist();
        MusicPlaylist(Song* song);

        Song* getFirstSong();
        bool isEmpty();
        void displayPlaylist();
        void addSong(Song* previousSong, Song* newSong);
        Song* searchSongByName(std::string name);
        void likeSong(std::string name);
        void displayAllSongsbyArtist(string name);
};
#endif
