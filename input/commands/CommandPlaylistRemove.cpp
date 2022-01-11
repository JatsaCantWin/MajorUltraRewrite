//
// Created by Peter on 2022-01-10.
//

#include <stdexcept>
#include "CommandPlaylistRemove.h"
#include "../../sound/PlaylistContainer.h"

bool CommandPlaylistRemove::execute(std::vector <std::wstring> arguments) {
    if (arguments.empty())
        throw std::invalid_argument("Nie podano nazwy playlisty.");
    if (arguments.size() == 1)
        throw std::invalid_argument("Nie podano sciezki do pliku muzycznego ktory nalezy usunac.");

    for (auto currentSong = arguments.begin() + 1; currentSong != arguments.end(); currentSong++)
        PlaylistContainer::getInstance().removeSong(arguments[0], *currentSong);
    return true;
}
