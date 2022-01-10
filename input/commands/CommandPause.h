//
// Created by Peter on 2022-01-10.
//


#ifndef MAJORULTRAREWRITE_COMMANDPAUSE_H
#define MAJORULTRAREWRITE_COMMANDPAUSE_H

#include <vector>
#include <string>
#include "Command.h"

class CommandPause : public Command {
    bool execute(std::vector <std::wstring> arguments) override;
};

#endif //MAJORULTRAREWRITE_COMMANDPAUSE_H

