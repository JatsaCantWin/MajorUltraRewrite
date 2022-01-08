//
// Created by Peter on 2022-01-06.
//

#include "Command.h"
#include "CommandExit.h"

#include <iostream>
#include <exception>

using namespace std;

Command *Commands::getCommand(const wstring &commandName) {
    if (commandDictionary.empty())
        Initialize();
    auto result = commandDictionary[commandName];
    if (result == nullptr)
        throw invalid_argument("Polecenie nie istnieje.");
    return result;
}

void Commands::Initialize() {
    commandDictionary[L"exit"] = new CommandExit();
}
