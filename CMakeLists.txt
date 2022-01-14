cmake_minimum_required(VERSION 3.20)
project(MajorUltraRewrite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(MajorUltraRewrite main.cpp
        sound/MusicPlayer.cpp sound/MusicPlayer.h sound/Playlist.cpp sound/Playlist.h
        input/Terminal.h input/Terminal.cpp input/Parser.cpp input/Parser.h
        input/commands/Command.cpp input/commands/Command.h input/commands/CommandExit.cpp input/commands/CommandExit.h input/commands/CommandNExt.cpp input/commands/CommandNExt.h input/commands/CommandPlay.cpp input/commands/CommandPlay.h input/commands/CommandPause.cpp input/commands/CommandPause.h input/commands/CommandStop.cpp input/commands/CommandStop.h
        input/commands/CommandPlaylist.cpp input/commands/CommandPlaylist.h input/commands/CommandPlaylistAdd.cpp input/commands/CommandPlaylistAdd.h  input/commands/CommandPlaylistPrint.cpp input/commands/CommandPlaylistPrint.h input/commands/CommandPlaylistRemove.cpp input/commands/CommandPlaylistRemove.h input/commands/CommandPlaylistDelete.h input/commands/CommandPlaylistDelete.cpp
        sound/PlaylistContainer.cpp sound/PlaylistContainer.h)

target_link_libraries(MajorUltraRewrite Strmiids.lib)
target_link_libraries(MajorUltraRewrite Quartz.lib)