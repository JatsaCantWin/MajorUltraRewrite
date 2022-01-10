//
// Created by Peter on 2022-01-06.
//

#include <iostream>
#include "CommandPlay.h"
#include "../../sound/MusicPlayer.h"
#include "../../sound/PlaylistContainer.h"

bool CommandPlay::execute(std::vector<std::wstring> arguments) {
    MusicPlayer::getInstance().stop();
    std::cout <<"daadwawd" << std::endl;
    if (not arguments.empty())
        MusicPlayer::getInstance().setCurrentPlaylist(PlaylistContainer::getInstance().getPlaylist(arguments[0]));
    std::cout <<"zxzxzxzzx" << std::endl;
    MusicPlayer::getInstance().play();
    return true;
}