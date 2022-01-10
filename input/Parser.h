//
// Created by Peter on 2022-01-04.
//

#ifndef MAJORULTRAREWRITE_PARSER_H
#define MAJORULTRAREWRITE_PARSER_H

#include <vector>
#include <string>
#include "Terminal.h"
#include "commands/Command.h"

class Terminal;
class Commands;

class Parser {
    private:
        Commands * commands;
        static Parser * instance;
        explicit Parser();
    public:
        static Parser getInstance();
        void parse(const std::wstring& command);
        std::vector<std::wstring> tokenize(const std::wstring& command);
        bool execute(const std::vector<std::wstring>& tokens);
};


#endif //MAJORULTRAREWRITE_PARSER_H
