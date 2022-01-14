//
// Created by Peter on 2022-01-06.
//

#include "CommandNext.h"
#include "../../sound/MusicPlayer.h"

bool CommandNext::execute(std::vector<std::wstring> arguments) {
    auto nextSong = MusicPlayer::getInstance().selectNextFromPlaylist();
    if (not nextSong.empty())
        MusicPlayer::getInstance().playSong(nextSong);
    return true;
}
