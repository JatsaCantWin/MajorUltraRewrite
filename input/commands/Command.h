//
// Created by Peter on 2022-01-06.
//

#ifndef MAJORULTRAREWRITE_COMMAND_H
#define MAJORULTRAREWRITE_COMMAND_H

#include <vector>
#include <map>
#include <string>

class Commands;

class Command {
    public:
        virtual bool execute(std::vector<std::wstring> arguments) = 0;
};

class Commands {
    private:
        inline static std::map<std::wstring, Command*> commandDictionary;
        static void Initialize();
    public:
        static Command * getCommand(const std::wstring& commandName);
};

#endif //MAJORULTRAREWRITE_COMMAND_H