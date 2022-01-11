#include "sound/MusicPlayer.h"

#include "windows.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "input/Terminal.h"
#include "input/commands/Command.h"

using namespace std;


int main() {
    while (true){
        Terminal::getInstance().readCharacter();
        MusicPlayer::getInstance().checkIfMusicIsCompleted();
    }
    return 0;
}
