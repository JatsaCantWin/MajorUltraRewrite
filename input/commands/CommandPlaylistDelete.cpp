//
// Created by Peter on 2022-01-11.
//

#include "CommandPlaylistDelete.h"

#include "../../sound/MusicPlayer.h"
#include "../../sound/PlaylistContainer.h"
#include <iostream>

bool CommandPlaylistDelete::execute(std::vector<std::wstring> arguments) {
    if (arguments.empty())
        throw std::invalid_argument("Nie podano nazwy playlisty.");
    if (MusicPlayer::getInstance().getCurrentPlaylist() == PlaylistContainer::getInstance().getPlaylist(arguments[0]))
        throw std::invalid_argument("Nie mozna usunac playlisty: playlista jest obecnie w uzyciu.");

    PlaylistContainer::getInstance().removePlaylist(arguments[0]);
    return true;
}
