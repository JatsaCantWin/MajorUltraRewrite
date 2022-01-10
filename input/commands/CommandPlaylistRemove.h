//
// Created by Peter on 2022-01-10.
//

#ifndef MAJORULTRAREWRITE_COMMANDPLAYLISTREMOVE_H
#define MAJORULTRAREWRITE_COMMANDPLAYLISTREMOVE_H

#include <vector>
#include <string>
#include "Command.h"

class CommandPlaylistRemove : public Command {
    bool execute(std::vector <std::wstring> arguments) override;
};

#endif //MAJORULTRAREWRITE_COMMANDPLAYLISTREMOVE_H

