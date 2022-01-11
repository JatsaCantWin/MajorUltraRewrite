//
// Created by Peter on 2022-01-06.
//

#include "CommandPlaylist.h"
#include "CommandPlaylistAdd.h"
#include "CommandPlaylistPrint.h"
#include "CommandPlaylistRemove.h"
#include "CommandPlaylistDelete.h"

#include <iostream>

CommandPlaylist::CommandPlaylist() {
    subCommands[L"add"] = new CommandPlaylistAdd();
    subCommands[L"print"] = new CommandPlaylistPrint();
    subCommands[L"remove"] = new CommandPlaylistRemove();
    subCommands[L"delete"] = new CommandPlaylistDelete();
}

bool CommandPlaylist::execute(std::vector<std::wstring> arguments) {
    std::vector<std::wstring> newArguments;

    if (arguments.empty())
        throw std::invalid_argument("Polecenie wymaga argumentow.");
    if (subCommands[arguments[0]] == nullptr)
        throw std::invalid_argument("Niepoprawny argument polecenia \"playlist\"");

    for (const auto& i : arguments)
    {
        if (i == *arguments.begin())
            continue;
        newArguments.push_back(i);
    }
    return subCommands[arguments[0]]->execute(std::vector<std::wstring>(arguments.begin()+1, arguments.end()));
}
