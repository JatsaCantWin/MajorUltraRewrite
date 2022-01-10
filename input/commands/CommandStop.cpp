//
// Created by Peter on 2022-01-10.
//

#include <iostream>
#include "CommandStop.h"
#include "../../sound/MusicPlayer.h"

bool CommandStop::execute(std::vector <std::wstring> arguments) {
    MusicPlayer::getInstance().stop();
    return true;
}
