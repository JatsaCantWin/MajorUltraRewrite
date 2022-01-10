//
// Created by Peter on 2022-01-06.
//

#include "CommandPlaylistPrint.h"
#include "../../sound/PlaylistContainer.h"
#include "../Terminal.h"
#include <iostream>

using namespace std;

bool CommandPlaylistPrint::execute(std::vector<std::wstring> arguments) {
    if (arguments.empty())
        throw invalid_argument("Nie podano nazwy playlisty.");

    auto songList = PlaylistContainer::getInstance().getPlaylist(arguments[0])->getSongList();

    wcout << L"Nazwa playlisty: " + arguments[0] << endl;

    for (const auto& song : songList)
        wcout << song << endl;
    return true;
}
