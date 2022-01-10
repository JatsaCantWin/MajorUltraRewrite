//
// Created by Peter on 2022-01-03.
//

#include "Terminal.h"

#include <windows.h>
#include <conio.h>
#include <iostream>

Terminal* Terminal::instance = nullptr;

void setCursorVisiblity(bool visibility)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
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
            return new InputStateHotkey(terminal);
        case 13:
            _putwch('\n');
            if (!inputString.empty())
            {
                auto command = inputString;
                clearInputString();
                terminal->parse(command);
            }
            break;
        case 8:
            if (!inputString.empty())
            {
                backspace();
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

InputStateTerminal::InputStateTerminal(Terminal * parentTerminal) {
    setCursorVisiblity(true);
    terminal = parentTerminal;
}

InputStateTerminal::~InputStateTerminal() {
    while (!inputString.empty())
    {
        backspace();
        inputString.pop_back();
    }
}

void InputStateTerminal::displayMessage(const std::wstring& message) {
    for(int i=0; i<inputString.length(); i++)
        backspace();
    _putws(message.c_str());
    for (wchar_t i : inputString)
        _putch(i);
}

void InputStateTerminal::backspace() {
    _putwch('\b');
    _putwch(' ');
    _putwch('\b');
}

void InputStateTerminal::clearInputString() {
    inputString = L"";
}

/**
 * InputStateHotkey
 */

InputState *InputStateHotkey::processChar(wint_t inputCharacter) {
    switch (inputCharacter)
    {
        case '`':
            return new InputStateTerminal(terminal);
        default:
            break;
    }
    return this;
}

InputStateHotkey::InputStateHotkey(Terminal * parentTerminal) {
    setCursorVisiblity(false);
    terminal = parentTerminal;
}

void InputStateHotkey::displayMessage(const std::wstring& message) {

}

void InputStateHotkey::clearInputString() {

}

/**
 * Terminal
 */

using namespace std;

Terminal::Terminal() {
    inputState = new InputStateTerminal(this);
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

void Terminal::displayMessage(const std::wstring& message) {
    inputState->displayMessage(message);
}

void Terminal::parse(const std::wstring& inputString) {
    Parser::getInstance().parse(inputString);
}

void Terminal::clearInputString() {
    inputState->clearInputString();
}

Terminal Terminal::getInstance() {
    if (instance == nullptr)
        instance = new Terminal();
    return *instance;
}
