//
// Created by Peter on 2022-01-11.
//


#ifndef MAJORULTRAREWRITE_COMMANDPLAYLISTDELETE_H
#define MAJORULTRAREWRITE_COMMANDPLAYLISTDELETE_H

#include <vector>
#include <string>
#include "Command.h"

class CommandPlaylistDelete : public Command {
    bool execute(std::vector <std::wstring> arguments) override;
};

#endif //MAJORULTRAREWRITE_COMMANDPLAYLISTDELETE_H

