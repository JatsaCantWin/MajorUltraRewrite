//
// Created by Peter on 2022-01-06.
//

#ifndef MAJORULTRAREWRITE_COMMANDPLAY_H
#define MAJORULTRAREWRITE_COMMANDPLAY_H

#include "Command.h"

class CommandPlay: public Command {
    bool execute(std::vector<std::wstring> arguments) override;
};


#endif //MAJORULTRAREWRITE_COMMANDPLAY_H
