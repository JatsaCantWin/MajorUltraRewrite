//
// Created by Peter on 2022-01-06.
//

#ifndef MAJORULTRAREWRITE_COMMAND_H
#define MAJORULTRAREWRITE_COMMAND_H

#include <vector>
#include <map>
#include <string>

class Command {
    public:
        virtual bool execute(std::vector<std::wstring> arguments) = 0;
};

class Commands {
    private:
        std::map<std::wstring, Command*> commandDictionary;
    public:
        Commands();
        Command * getCommand(const std::wstring& commandName);
};

#endif //MAJORULTRAREWRITE_COMMAND_H