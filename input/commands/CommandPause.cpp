//
// Created by Peter on 2022-01-10.
//

#include "CommandPause.h"
#include "../../sound/MusicPlayer.h"

bool CommandPause::execute(std::vector <std::wstring> arguments) {
    MusicPlayer::getInstance().pause();
    return true;
}
