//
// Created by Peter on 2022-01-03.
//

#ifndef MAJORULTRAREWRITE_TERMINAL_H
#define MAJORULTRAREWRITE_TERMINAL_H

#include <conio.h>
#include <string>

class InputState {
    public:
        virtual InputState * processChar(wint_t inputCharacter) = 0;
        virtual ~InputState() = default;
};

class InputStateTerminal: public InputState {
    private:
        std::wstring inputString;
    public:
        InputState * processChar(wint_t inputCharacter) override;
        InputStateTerminal();
        ~InputStateTerminal();
};

class InputStateHotkey: public InputState {
    public:
        InputState * processChar(wint_t inputCharacter) override;
        InputStateHotkey();
};

class Terminal {
    private:
        InputState * inputState;
    public:
        Terminal();
        void toggleCursorState();
        void readCharacter();
        void processCharacter(wint_t character);
};


#endif //MAJORULTRAREWRITE_TERMINAL_H
