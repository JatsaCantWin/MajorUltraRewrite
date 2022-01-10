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
        const static std::vector<std::string> allowedExtensions;
    public:
        explicit Playlist(const std::wstring& name);
        ~Playlist();
        void addSong(const std::wstring& newSong);
        void removeSong(const std::wstring& songPath);
        std::wstring nextSong();
        std::list<std::wstring> getSongList();
        void moveIteratorToStart();
        static bool isValidSong(const std::wstring& songPath);
        bool checkCurrentSongsValidity();
        bool isEmpty();
};


#endif //MAJORULTRAREWRITE_PLAYLIST_H
