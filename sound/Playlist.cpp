//
// Created by Peter on 2021-12-26.
//

#include "Playlist.h"

#include <algorithm>

using namespace std;

Playlist::Playlist() {
    currentSong = songList.begin();

    auto randomDevice = random_device{};
    randomEngine = default_random_engine { randomDevice() };
}

void Playlist::addSong(const wstring& songPath) {
    songList.insert(songList.begin()+(rand() % songList.size()), songPath);
}

wstring Playlist::nextSong() {
    wstring result = *currentSong;
    if (*currentSong == songList.back())
    {
        shuffle(begin(songList), end(songList), randomEngine);
        if (result == songList.front())
            std::reverse(songList.begin(), songList.end());
    } else
        advance(currentSong, 1);
    return result;
}