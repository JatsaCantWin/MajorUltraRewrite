//
// Created by Peter on 2022-01-06.
//

#include "CommandPlaylistAdd.h"
#include "../../sound/PlaylistContainer.h"
#include <iostream>

using namespace std;

bool CommandPlaylistAdd::execute(std::vector<std::wstring> arguments) {
    if (arguments.empty())
        throw invalid_argument("Nie podano nazwy playlisty.");

    PlaylistContainer::getInstance().addPlaylist(arguments[0]);

    if (arguments.begin() == arguments.end())
        return true;

    for (auto currentArgument = arguments.begin() + 1; currentArgument != arguments.end(); currentArgument++)
    {
        PlaylistContainer::getInstance().addSong(arguments[0], *currentArgument);
    }
    return true;
}
