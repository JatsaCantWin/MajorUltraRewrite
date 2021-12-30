//
// Created by Peter on 2021-12-26.
//

#include "Playlist.h"

using namespace std;

Playlist::Playlist(const std::wstring& name) {
    this->name = name;

    random_device rd;
    randomGenerator = new mt19937(rd());
}

Playlist::~Playlist() {
    delete randomGenerator;
}

void Playlist::addSong(const std::wstring& newSong) {
    std::uniform_int_distribution<unsigned int> randomPosition(0, songList.size());

    auto randomSongListIterator = next(songList.begin(), randomPosition(*randomGenerator));

    songList.insert(randomSongListIterator, newSong);
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




