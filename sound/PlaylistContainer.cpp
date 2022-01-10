//
// Created by Peter on 2022-01-08.
//

#include "PlaylistContainer.h"

#include <iostream>

using namespace std;

PlaylistContainer * PlaylistContainer::instance = nullptr;

PlaylistContainer::PlaylistContainer() {
    playlistMap = new std::map<std::wstring, Playlist*>;
}

void PlaylistContainer::addPlaylist(const std::wstring& playlistName) {
    playlistMap->insert(pair<wstring, Playlist*>(playlistName, new Playlist(playlistName)));
}

void PlaylistContainer::removePlaylist(const std::wstring& playlistName) {
    delete (*playlistMap)[playlistName];
    (*playlistMap).erase(playlistName);
}

void PlaylistContainer::addSong(const std::wstring& playlistName, const std::wstring& songPath) {
    if (not playlistMap->count(playlistName))
        throw invalid_argument("Playlista nie istnieje. as");
    (*playlistMap)[playlistName]->addSong(songPath);
}

void PlaylistContainer::removeSong(const std::wstring& playlistName, const std::wstring& songPath) {
    if (not playlistMap->count(playlistName))
        throw invalid_argument("Playlista nie istnieje. rs");
    (*playlistMap)[playlistName]->removeSong(songPath);
}

Playlist * PlaylistContainer::getPlaylist(const std::wstring& playlistName) {
    if (not playlistMap->count(playlistName))
        throw invalid_argument("Playlista nie istnieje. gp");
    return (*playlistMap)[playlistName];
}

PlaylistContainer PlaylistContainer::getInstance() {
    if (instance == nullptr)
        instance = new PlaylistContainer();
    return *instance;
}
