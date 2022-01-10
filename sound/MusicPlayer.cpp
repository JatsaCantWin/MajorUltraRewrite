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
    parent->stopCompletionThreadFlag = true;
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
    startWaitForCompletionThread();
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

void MusicPlayer::playNextFromPlaylist() {
    try
    {
        if (currentPlaylist == nullptr)
            throw logic_error("Nie wybrano zadnej playlisty.");
        while ((not currentPlaylist->isEmpty()) and (not currentPlaylist->checkCurrentSongsValidity()));
        if (currentPlaylist->isEmpty())
        {
            throw logic_error("Obecna playlista jest pusta. Zatrzymano odtwarzanie.");
        }
        wstring nextSong = currentPlaylist->nextSong();
        if (!nextSong.empty())
            playSong(nextSong);
    }
    catch (logic_error& e)
    {
        string message = e.what();
        wstring wmessage;
        for (auto c:message)
            wmessage.push_back(c);
        Terminal::getInstance().displayMessage(wmessage);
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

void MusicPlayer::waitForCompletion() {
    long result;
    mediaEvent->WaitForCompletion(INFINITE, &result);
}

DWORD WINAPI waitForCompletionThread(LPVOID lpParameter)
{
    auto * musicPlayer = (MusicPlayer *) lpParameter;
    musicPlayer->waitForCompletion();
    if (not musicPlayer->stopCompletionThreadFlag)
        musicPlayer->playNextFromPlaylist();
    return 0;
}

void MusicPlayer::startWaitForCompletionThread() {
    stopCompletionThreadFlag = false;
    CreateThread(nullptr, 0, waitForCompletionThread, this, 0, nullptr);
}

MusicPlayer &MusicPlayer::getInstance() {
    static MusicPlayer instance;
    return instance;
}
