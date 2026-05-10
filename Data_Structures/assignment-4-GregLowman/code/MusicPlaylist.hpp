//#pragma once
#ifndef MUSIC_PLAYLIST_HPP__
#define MUSIC_PLAYLIST_HPP__
#include "../library/MusicPlaylistBase.hpp"

using namespace std;

// class for storing and manipulating linked-list of songs
class MusicPlaylist : public MusicPlaylistBase {
    private:
    public:
        // Constructors to initialize the playlist
        MusicPlaylist();
        int findLoopInPlaylist();
        void removeSongs(int start, int end);
        void mergeTwoPlaylists(Song* headOne, Song* headTwo);
};
#endif
