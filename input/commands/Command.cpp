//
// Created by Peter on 2022-01-06.
//

#include "Command.h"
#include "CommandExit.h"
#include "CommandPlaylist.h"
#include "CommandPause.h"
#include "CommandPlay.h"
#include "CommandStop.h"

#include <iostream>
#include <exception>

using namespace std;

Command *Commands::getCommand(const wstring &commandName) {
    auto result = commandDictionary[commandName];
    if (result == nullptr)
        throw invalid_argument("Polecenie nie istnieje.");
    return result;
}

Commands::Commands() {
    commandDictionary[L"exit"] = new CommandExit();
    commandDictionary[L"playlist"] = new CommandPlaylist();
    commandDictionary[L"play"] = new CommandPlay();
    commandDictionary[L"stop"] = new CommandStop();
    commandDictionary[L"pause"] = new CommandPause();
}
