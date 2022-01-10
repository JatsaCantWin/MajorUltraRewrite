//
// Created by Peter on 2022-01-04.
//

#include "Parser.h"
#include <sstream>
#include <exception>
#include <iostream>

using namespace std;

Parser* Parser::instance = nullptr;

Parser::Parser() {
    commands = new Commands();
}

void Parser::parse(const wstring& command) {
    vector<wstring> tokens;

    tokens = tokenize(command);
    execute(tokens);
}

vector<wstring> Parser::tokenize(const wstring& command) {
    vector<wstring> result;

    wistringstream commandStream(command);
    wstring token;
    while(getline(commandStream, token, L' '))
        if (!token.empty())
            result.push_back(token);

    return result;
}

bool Parser::execute(const vector<wstring>& tokens) {
    try {
        vector<wstring> arguments(tokens.begin() + 1, tokens.end());
        commands->getCommand(tokens[0])->execute(arguments);
    }
    catch(invalid_argument& e){
        Terminal::getInstance().clearInputString();
        string message = e.what();
        wstring wmessage;
        for (auto c:message)
            wmessage.push_back(c);
        Terminal::getInstance().displayMessage(wmessage);
    }
    return true;
}

Parser Parser::getInstance() {
    if (instance == nullptr)
        instance = new Parser();
    return *instance;
}
