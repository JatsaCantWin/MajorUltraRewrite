//
// Created by Peter on 2022-01-06.
//

#include <iostream>
#include "CommandPlay.h"
#include "../../sound/MusicPlayer.h"
#include "../../sound/PlaylistContainer.h"

bool CommandPlay::execute(std::vector<std::wstring> arguments) {
    if (not arguments.empty())
        MusicPlayer::getInstance().setCurrentPlaylist(PlaylistContainer::getInstance().getPlaylist(arguments[0]));
    MusicPlayer::getInstance().play();
    return true;
}