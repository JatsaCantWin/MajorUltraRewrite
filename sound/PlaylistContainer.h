//
// Created by Peter on 2022-01-08.
//

#ifndef MAJORULTRAREWRITE_PLAYLISTCONTAINER_H
#define MAJORULTRAREWRITE_PLAYLISTCONTAINER_H

#include <map>
#include "Playlist.h"

class PlaylistContainer {
    private:
        static PlaylistContainer * instance;
        PlaylistContainer();
        std::map<std::wstring, Playlist*> * playlistMap;
    public:
        static PlaylistContainer getInstance();
        void addPlaylist(const std::wstring& playlistName);
        void removePlaylist(const std::wstring& playlistName);
        void addSong(const std::wstring& playlistName, const std::wstring& songPath);
        void removeSong(const std::wstring& playlistName, const std::wstring& songPath);
        Playlist * getPlaylist(const std::wstring& playlistName);
};


#endif //MAJORULTRAREWRITE_PLAYLISTCONTAINER_H
