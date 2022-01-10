//
// Created by Peter on 2022-01-10.
//


#ifndef MAJORULTRAREWRITE_COMMANDSTOP_H
#define MAJORULTRAREWRITE_COMMANDSTOP_H

#include <vector>
#include <string>
#include "Command.h"

class CommandStop : public Command {
    bool execute(std::vector <std::wstring> arguments) override;
};

#endif //MAJORULTRAREWRITE_COMMANDSTOP_H

