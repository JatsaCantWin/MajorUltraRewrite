//
// Created by Peter on 2022-01-06.
//

#ifndef MAJORULTRAREWRITE_COMMANDEXIT_H
#define MAJORULTRAREWRITE_COMMANDEXIT_H

#include "Command.h"

class CommandExit: public Command {
    bool execute(std::vector<std::wstring> arguments) override;
};


#endif //MAJORULTRAREWRITE_COMMANDEXIT_H
