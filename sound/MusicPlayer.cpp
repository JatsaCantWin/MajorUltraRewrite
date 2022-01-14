//
// Created by Peter on 2021-12-24.
//

#include "MusicPlayer.h"
#include "windows.h"
#include "../input/Terminal.h"

#include <stdexcept>
#include <iostream>

using namespace std;

/**
 * MusicPlayerStateRunning
 */

MusicPlayerState *MusicPlayerStateRunning::play() {
    return this;
}

MusicPlayerState *MusicPlayerStateRunning::pause() {
    if (FAILED(parent->getMediaControl()->Pause()))
        return this;                                                                              //TODO: Error Handling
    return new MusicPlayerStatePaused(parent);
}

MusicPlayerState *MusicPlayerStateRunning::stop() {
    if (FAILED(parent->getMediaControl()->Stop()))
        return this;                                                                              //TODO: Error Handling
    parent->generateFilterGraphManager();                                                         //Regenerate Filter Graph Manager to
    return new MusicPlayerStateStopped(parent);                                                   //stop current music from playing
}

MusicPlayerStateRunning::MusicPlayerStateRunning(MusicPlayer *parent) {
    this->parent = parent;
}

/**
 * MusicPlayerStatePaused
 */

MusicPlayerState *MusicPlayerStatePaused::play() {
    if (FAILED(parent->getMediaControl()->Run()))
        return this;                                                                              //TODO: Error Handling
    return new MusicPlayerStateRunning(parent);
}

MusicPlayerState *MusicPlayerStatePaused::pause() {
    return this;
}

MusicPlayerState *MusicPlayerStatePaused::stop() {
    if (FAILED(parent->getMediaControl()->Stop()))
        return this;                                                                              //TODO: Error Handling
    parent->generateFilterGraphManager();                                                         //Regenerate Filter Graph Manager to
    return new MusicPlayerStateStopped(parent);                                                   //stop current music from playing
}

MusicPlayerStatePaused::MusicPlayerStatePaused(MusicPlayer *parent) {
    this->parent = parent;
}

/**
 * MusicPlayerStateStopped
 */

MusicPlayerState *MusicPlayerStateStopped::play() {
    if (parent->getCurrentSongPath().empty())
        parent->setCurrentSongPath(parent->selectNextFromPlaylist());
    if (FAILED(parent->getFilterGraphManager()->RenderFile(const_cast<wchar_t *>(parent->getCurrentSongPath().c_str()), nullptr)))
        return this;                                                                              //TODO: Error Handling
    if (FAILED(parent->getMediaControl()->Run()))
        return this;                                                                              //TODO: Error Handlin
    return new MusicPlayerStateRunning(parent);
}

MusicPlayerState *MusicPlayerStateStopped::pause() {
    return this;
}

MusicPlayerState *MusicPlayerStateStopped::stop() {
    return this;
}

MusicPlayerStateStopped::MusicPlayerStateStopped(MusicPlayer *parent) {
    this->parent = parent;
}

/**
 * MusicPlayer
 */

MusicPlayer::MusicPlayer() {
    if (FAILED(CoInitialize(
            nullptr)))                                                                                                  //Initialize COM Library
        return;                                                                                                                             //TODO: Error handling
    generateFilterGraphManager();
    currentState = new MusicPlayerStateStopped(this);
    currentPlaylist = nullptr;
}

MusicPlayer::~MusicPlayer() {
    mediaEvent->Release();
    mediaControl->Release();
    filterGraphManager->Release();
    CoUninitialize();
}

void MusicPlayer::play() {
    MusicPlayerState *oldState = currentState;
    currentState = currentState->play();
    if (oldState != currentState)
        delete oldState;
}

void MusicPlayer::pause() {
    MusicPlayerState *oldState = currentState;
    currentState = currentState->pause();
    if (oldState != currentState)
        delete oldState;
}

void MusicPlayer::stop() {
    MusicPlayerState *oldState = currentState;
    currentState = currentState->stop();
    if (oldState != currentState)
        delete oldState;
}

void MusicPlayer::playSong(const wstring &newSong) {
    stop();
    currentSongPath = newSong;
    play();
}

wstring MusicPlayer::selectNextFromPlaylist() {
    try
    {
        if (currentPlaylist == nullptr)
            throw logic_error("Nie wybrano zadnej playlisty.");
        while ((not currentPlaylist->isEmpty()) and (not currentPlaylist->checkCurrentSongsValidity()));
        if (currentPlaylist->isEmpty())
        {
            throw logic_error("Obecna playlista jest pusta. Zatrzymano odtwarzanie.");
        }
        return  currentPlaylist->nextSong();
    }
    catch (logic_error& e)
    {
        string message = e.what();
        wstring wmessage;
        for (auto c:message)
            wmessage.push_back(c);
        Terminal::getInstance().displayMessage(wmessage);
        return L"";
    }
}

void MusicPlayer::generateFilterGraphManager() {
    if (filterGraphManager != nullptr) {
        mediaEvent->Release();
        mediaControl->Release();
        filterGraphManager->Release();
    }
    if (FAILED(CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **) &filterGraphManager)))    //Initialize Filter Graph Manager
        return;                                                                                                                             //TODO: Error handling
    if (FAILED(filterGraphManager->QueryInterface(IID_IMediaControl, (void **) &mediaControl)))                                          //Initialize Media Control Interface
        return;                                                                                                                             //TODO: Error handling
    if (FAILED(filterGraphManager->QueryInterface(IID_IMediaEvent, (void **) &mediaEvent)))                                              //Initialize Media Event Interface
        return;                                                                                                                             //TODO: Error handling                                                                                                                           //TODO: Error handling
}

IGraphBuilder *MusicPlayer::getFilterGraphManager() const {
    return filterGraphManager;
}

IMediaControl *MusicPlayer::getMediaControl() const {
    return mediaControl;
}

const wstring &MusicPlayer::getCurrentSongPath() const {
    return currentSongPath;
}

void MusicPlayer::setCurrentPlaylist(Playlist *newPlaylist) {
    currentPlaylist = newPlaylist;
    currentPlaylist->moveIteratorToStart();
}

MusicPlayer &MusicPlayer::getInstance() {
    static MusicPlayer instance;
    return instance;
}

void MusicPlayer::checkIfMusicIsCompleted() {
    if (dynamic_cast<const MusicPlayerStateRunning*>(currentState) != nullptr)
    {
        long result;
        if (mediaEvent->WaitForCompletion(10, &result) != E_ABORT)
            playSong(selectNextFromPlaylist());
    }
}

Playlist * MusicPlayer::getCurrentPlaylist() {
    return currentPlaylist;
}

void MusicPlayer::setCurrentSongPath(const wstring &newSongPath) {
    currentSongPath = newSongPath;
}
