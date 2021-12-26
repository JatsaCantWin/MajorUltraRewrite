//
// Created by Peter on 2021-12-26.
//

#ifndef MAJORULTRAREWRITE_PLAYLIST_H
#define MAJORULTRAREWRITE_PLAYLIST_H

#include <string>
#include <vector>
#include <random>

class Playlist {
    private:
        std::default_random_engine randomEngine;
        std::vector<std::wstring> songList;
        std::vector<std::wstring>::iterator currentSong;
    public:
        Playlist();
        void addSong(const std::wstring& songPath);
        std::wstring nextSong();
};


#endif //MAJORULTRAREWRITE_PLAYLIST_H
