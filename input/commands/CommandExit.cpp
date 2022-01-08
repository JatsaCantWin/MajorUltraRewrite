//
// Created by Peter on 2022-01-06.
//

#include "CommandExit.h"
#include <cstdlib>

bool CommandExit::execute(std::vector<std::wstring> arguments) {
    exit(EXIT_SUCCESS);
}
