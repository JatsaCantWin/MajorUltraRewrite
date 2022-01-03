cmake_minimum_required(VERSION 3.20)
project(MajorUltraRewrite)

set(CMAKE_CXX_STANDARD 17)

add_executable(MajorUltraRewrite main.cpp sound/MusicPlayer.cpp sound/MusicPlayer.h sound/Playlist.cpp sound/Playlist.h input/Terminal.cpp input/Terminal.h input/Parser.cpp input/Parser.h)

target_link_libraries(MajorUltraRewrite Strmiids.lib)
target_link_libraries(MajorUltraRewrite Quartz.lib)