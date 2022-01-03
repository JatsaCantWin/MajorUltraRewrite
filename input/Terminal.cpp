//
// Created by Peter on 2022-01-03.
//

#include "Terminal.h"
#include <windows.h>
#include <conio.h>

void setCursorVisiblity(bool visibility)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    //cursorInfo.dwSize = 100;
    cursorInfo.bVisible = visibility;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

/**
 * InputStateTerminal
 */

InputState *InputStateTerminal::processChar(wint_t inputCharacter) {
    switch (inputCharacter)
    {
        case '`':
            return new InputStateHotkey;
        case 13:
            _putwch('\n');
            inputString = L"";
            break;
        case 8:
            if (!inputString.empty())
            {
                _putwch('\b');
                _putwch(' ');
                _putwch('\b');
                inputString.pop_back();
            }
            break;
        case '\t':
            break;
        default:
            _putwch(inputCharacter);
            inputString.push_back(inputCharacter);
            break;
    }
    return this;
}

InputStateTerminal::InputStateTerminal() {
    setCursorVisiblity(true);
}

InputStateTerminal::~InputStateTerminal() {
    while (!inputString.empty())
    {
        _putwch('\b');
        _putwch(' ');
        _putwch('\b');
        inputString.pop_back();
    }
}

/**
 * InputStateHotkey
 */

InputState *InputStateHotkey::processChar(wint_t inputCharacter) {
    switch (inputCharacter)
    {
        case '`':
            return new InputStateTerminal;
        default:
            break;
    }
    return this;
}

InputStateHotkey::InputStateHotkey() {
    setCursorVisiblity(false);
}

/**
 * Terminal
 */

Terminal::Terminal() {
    inputState = new InputStateTerminal;
}

void Terminal::readCharacter() {
    wchar_t characterRead = _getwch();
    if ((characterRead == 0)||(characterRead==0xE0))
    {
        _getwch();
        return;
    }
    this->processCharacter(characterRead);
}

void Terminal::processCharacter(wint_t character) {
    InputState * oldState = inputState;
    inputState = inputState->processChar(character);
    if (oldState != inputState)
        delete oldState;
}
