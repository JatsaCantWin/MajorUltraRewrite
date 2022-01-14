//
// Created by Peter on 2022-01-06.
//

#include "CommandPlaylistAdd.h"
#include "../../sound/PlaylistContainer.h"
#include <iostream>
#include <filesystem>

using namespace std;

bool CommandPlaylistAdd::execute(std::vector<std::wstring> arguments) {
    if (arguments.empty())
        throw invalid_argument("Nie podano nazwy playlisty.");

    PlaylistContainer::getInstance().addPlaylist(arguments[0]);

    if (arguments.begin() == arguments.end())
        return true;

    for (auto currentArgument = arguments.begin() + 1; currentArgument != arguments.end(); currentArgument++)
    {
        if (filesystem::is_directory(*currentArgument))
        {
            for (const auto &file: filesystem::directory_iterator(*currentArgument))
                if (Playlist::isValidSong(file.path()))
                    PlaylistContainer::getInstance().addSong(arguments[0], file.path());
        }
        else
            PlaylistContainer::getInstance().addSong(arguments[0], *currentArgument);
    }
    return true;
}
