//
// Created by Peter on 2021-12-26.
//

#include <filesystem>
#include <iostream>
#include "Playlist.h"
#include "../input/Terminal.h"

using namespace std;

const std::vector<std::string> Playlist::allowedExtensions = {".wav", ".mp3"};

Playlist::Playlist(const std::wstring& name) {
    this->name = name;
    random_device rd;
    randomGenerator = new mt19937(rd());
    moveIteratorToStart();
}

Playlist::~Playlist() {
    delete randomGenerator;
}

void Playlist::addSong(const std::wstring& newSong) {
    std::uniform_int_distribution<unsigned int> randomPosition(0, songList.size());

    auto randomSongListIterator = next(songList.begin(), randomPosition(*randomGenerator));

    songList.insert(randomSongListIterator, newSong);
}

void Playlist::removeSong(const wstring &songPath) {
    if (songPath == *currentSong)
        nextSong();
    songList.remove(songPath);
}

wstring Playlist::nextSong() {
    if (songList.empty())
        return L"";

    wstring result = *currentSong;
    auto nextIterator = next(currentSong);

    std::uniform_int_distribution<unsigned int> randomPositionBeforeCurrentSong(0, distance(songList.begin(), currentSong));
    auto randomSongListIterator = next(songList.begin(), randomPositionBeforeCurrentSong(*randomGenerator));

    songList.splice(randomSongListIterator, songList, currentSong);

    currentSong = nextIterator;

    if (nextIterator == songList.end())
        moveIteratorToStart();

    return result;
}

void Playlist::moveIteratorToStart() {
    currentSong = songList.begin();
}

bool Playlist::isEmpty() {
    return songList.empty();
}

std::list<std::wstring> Playlist::getSongList() {
    return songList;
}

bool Playlist::isValidSong(const std::wstring& songPath) {
    if (not filesystem::exists(songPath))
        return false;
    if (std::find(allowedExtensions.begin(), allowedExtensions.end(), filesystem::path(songPath).extension()) == allowedExtensions.end())
        return false;
    return true;
}

bool Playlist::checkCurrentSongsValidity() {
    if (isValidSong(*currentSong))
        return true;

    Terminal::getInstance().displayMessage(L"Plik " + *currentSong + L" nie istnieje lub nie jest wspierany - zostal on usuniety z playlisty.");
    removeSong(nextSong());
    return false;
}




