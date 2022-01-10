//
// Created by Peter on 2022-01-06.
//

#ifndef MAJORULTRAREWRITE_COMMANDPLAYLISTADD_H
#define MAJORULTRAREWRITE_COMMANDPLAYLISTADD_H

#include "Command.h"

class CommandPlaylistAdd: public Command {
    public:
        bool execute(std::vector<std::wstring> arguments) override;
};

#endif //MAJORULTRAREWRITE_COMMANDPLAYLISTADD_H
