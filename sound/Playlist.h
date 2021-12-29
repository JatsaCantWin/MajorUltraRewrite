//
// Created by Peter on 2021-12-26.
//

#ifndef MAJORULTRAREWRITE_PLAYLIST_H
#define MAJORULTRAREWRITE_PLAYLIST_H

#include <string>
#include <list>
#include <random>

class Playlist {
    private:
        std::wstring name;
        std::list<std::wstring> songList;
        std::list<std::wstring>::iterator currentSong;
        std::mt19937 * randomGenerator;
    public:
        explicit Playlist(const std::wstring& name);
        ~Playlist();
        void addSong(const std::wstring& newSong);
        std::wstring nextSong();
        void moveIteratorToStart();
};


#endif //MAJORULTRAREWRITE_PLAYLIST_H
