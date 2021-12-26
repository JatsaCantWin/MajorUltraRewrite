//
// Created by Peter on 2021-12-24.
//

#include "MusicPlayer.h"

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
    if (FAILED(parent->getFilterGraphManager()->RenderFile(const_cast<wchar_t *>(parent->getCurrentSongPath().c_str()), nullptr)))
        return this;                                                                              //TODO: Error Handling
    if (FAILED(parent->getMediaControl()->Run()))
        return this;                                                                              //TODO: Error Handling
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
    if (FAILED(CoInitialize(nullptr)))                                                                                                  //Initialize COM Library
        return;                                                                                                                             //TODO: Error handling
    generateFilterGraphManager();
    currentState = new MusicPlayerStateStopped(this);
}

MusicPlayer::~MusicPlayer() {
    mediaEvent->Release();
    mediaControl->Release();
    filterGraphManager->Release();
    CoUninitialize();
}

void MusicPlayer::play() {
    MusicPlayerState * oldState = currentState;
    currentState = currentState->play();
    if (oldState != currentState)
        delete oldState;
}

void MusicPlayer::pause() {
    MusicPlayerState * oldState = currentState;
    currentState = currentState->pause();
    if (oldState != currentState)
        delete oldState;
}

void MusicPlayer::stop() {
    MusicPlayerState * oldState = currentState;
    currentState = currentState->stop();
    if (oldState != currentState)
        delete oldState;
}

void MusicPlayer::playSong(const std::wstring& newSong) {
    stop();
    currentSongPath = newSong;
    play();
}

void MusicPlayer::generateFilterGraphManager() {
    if (filterGraphManager != nullptr){
        mediaEvent->Release();
        mediaControl->Release();
        filterGraphManager->Release();
    }
    if (FAILED(CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&filterGraphManager)))    //Initialize Filter Graph Manager
        return;                                                                                                                             //TODO: Error handling
    if (FAILED(filterGraphManager->QueryInterface(IID_IMediaControl, (void**)&mediaControl)))                                           //Initialize Media Control Interface
        return;                                                                                                                             //TODO: Error handling
    if (FAILED(filterGraphManager->QueryInterface(IID_IMediaEvent, (void**)&mediaEvent)))                                               //Initialize Media Event Interface
        return;                                                                                                                             //TODO: Error handling                                                                                                                           //TODO: Error handling
}

IGraphBuilder *MusicPlayer::getFilterGraphManager() const {
    return filterGraphManager;
}

IMediaControl *MusicPlayer::getMediaControl() const {
    return mediaControl;
}

const std::wstring &MusicPlayer::getCurrentSongPath() const {
    return currentSongPath;
}

