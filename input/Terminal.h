//
// Created by Peter on 2022-01-03.
//

#ifndef MAJORULTRAREWRITE_TERMINAL_H
#define MAJORULTRAREWRITE_TERMINAL_H

#include <conio.h>
#include <string>
#include "Parser.h"

class Parser;
class Terminal;

class InputState {
    public:
        virtual void clearInputString() = 0;
        virtual void displayMessage(const std::wstring& message) = 0;
        virtual InputState * processChar(wint_t inputCharacter) = 0;
        virtual ~InputState() = default;
};

class InputStateTerminal: public InputState {
    private:
        Terminal * terminal;
        std::wstring inputString;
        void backspace();
    public:
        void clearInputString() override;
        void displayMessage(const std::wstring& message) override;
        InputState * processChar(wint_t inputCharacter) override;
        InputStateTerminal(Terminal * parentTerminal);
        ~InputStateTerminal() override;
};

class InputStateHotkey: public InputState {
    private:
        Terminal * terminal;
    public:
        void clearInputString();
        void displayMessage(const std::wstring& message) override;
        InputState * processChar(wint_t inputCharacter) override;
        InputStateHotkey(Terminal * parentTerminal);
};

class Terminal {
    private:
        InputState * inputState;
        Parser * parser;
    public:
        Terminal();
        void clearInputString();
        void parse(const std::wstring& inputString);
        void readCharacter();
        void displayMessage(const std::wstring& message);
        void processCharacter(wint_t character);
};


#endif //MAJORULTRAREWRITE_TERMINAL_H
