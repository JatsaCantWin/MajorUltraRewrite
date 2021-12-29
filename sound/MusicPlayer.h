//
// Created by Peter on 2021-12-24.
//

#ifndef MAJORULTRAREWRITE_MUSICPLAYER_H
#define MAJORULTRAREWRITE_MUSICPLAYER_H

#include <dshow.h>
#include <string>
#include "Playlist.h"

class MusicPlayer;

class MusicPlayerState {
    protected:
        MusicPlayer * parent{};
    public:
        virtual MusicPlayerState * play() = 0;
        virtual MusicPlayerState * pause() = 0;
        virtual MusicPlayerState * stop() = 0;
        virtual ~MusicPlayerState() = default;
};

class MusicPlayerStateRunning: public MusicPlayerState {
    public:
        MusicPlayerState * play() override;
        MusicPlayerState * pause() override;
        MusicPlayerState * stop() override;
        explicit MusicPlayerStateRunning(MusicPlayer *parent);
};

class MusicPlayerStatePaused: public MusicPlayerState {
    public:
        MusicPlayerState * play() override;
        MusicPlayerState * pause() override;
        MusicPlayerState * stop() override;
        explicit MusicPlayerStatePaused(MusicPlayer *parent);
};

class MusicPlayerStateStopped: public MusicPlayerState {
    public:
        MusicPlayerState * play() override;
        MusicPlayerState * pause() override;
        MusicPlayerState * stop() override;
        explicit MusicPlayerStateStopped(MusicPlayer *parent);
};

class MusicPlayer {
    private:
        IGraphBuilder *filterGraphManager{};
        IMediaControl *mediaControl{};
        IMediaEvent *mediaEvent{};
        MusicPlayerState *currentState;
        std::wstring currentSongPath;
        Playlist * currentPlaylist;
public:
    void setCurrentPlaylist(Playlist *newPlaylist);

public:
        void play();
        void pause();
        void stop();
        void playSong(const std::wstring& newSong);
        void playNextFromPlaylist();
        void generateFilterGraphManager();
        MusicPlayer();
        ~MusicPlayer();
        [[nodiscard]] IGraphBuilder *getFilterGraphManager() const;
        [[nodiscard]] IMediaControl *getMediaControl() const;
        [[nodiscard]] const std::wstring &getCurrentSongPath() const;
};


#endif //MAJORULTRAREWRITE_MUSICPLAYER_H
