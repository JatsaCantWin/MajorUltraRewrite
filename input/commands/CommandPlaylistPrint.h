//
// Created by Peter on 2022-01-06.
//

#ifndef MAJORULTRAREWRITE_COMMANDPLAYLISTPRINT_H
#define MAJORULTRAREWRITE_COMMANDPLAYLISTPRINT_H

#include "Command.h"

class CommandPlaylistPrint: public Command {
    public:
        bool execute(std::vector<std::wstring> arguments) override;
};


#endif //MAJORULTRAREWRITE_COMMANDPLAYLISTPRINT_H
