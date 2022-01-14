//
// Created by Peter on 2022-01-06.
//

#ifndef MAJORULTRAREWRITE_COMMANDNEXT_H
#define MAJORULTRAREWRITE_COMMANDNEXT_H

#include "Command.h"

class CommandNext: public Command {
    bool execute(std::vector<std::wstring> arguments) override;
};


#endif //MAJORULTRAREWRITE_COMMANDNEXT_H
