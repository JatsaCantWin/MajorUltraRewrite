//
// Created by Peter on 2022-01-06.
//

#ifndef MAJORULTRAREWRITE_COMMANDPLAYLIST_H
#define MAJORULTRAREWRITE_COMMANDPLAYLIST_H

#include "Command.h"

class CommandPlaylist: public Command {
    private:
        std::map<std::wstring, Command*> subCommands;
    public:
        explicit CommandPlaylist();
        bool execute(std::vector<std::wstring> arguments) override;
};


#endif //MAJORULTRAREWRITE_COMMANDPLAYLIST_H
