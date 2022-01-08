//
// Created by Peter on 2022-01-04.
//

#ifndef MAJORULTRAREWRITE_PARSER_H
#define MAJORULTRAREWRITE_PARSER_H

#include <vector>
#include <string>
#include "Terminal.h"

class Terminal;

class Parser {
    private:
        Terminal * terminal;
    public:
        explicit Parser(Terminal * parentTerminal);
        void parse(const std::wstring& command);
        std::vector<std::wstring> tokenize(const std::wstring& command);
        bool execute(const std::vector<std::wstring>& tokens);
};


#endif //MAJORULTRAREWRITE_PARSER_H
