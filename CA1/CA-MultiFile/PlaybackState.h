#ifndef PLAYBACK_STATE_H
#define PLAYBACK_STATE_H

#include "Playlist.h"
#include <set>
#include <memory>
#include <string>

using namespace std;

struct PlaybackState
{
    enum class Source
    {
        PLAYLIST,
        QUEUE
    };

    Source source;
    string source_name;

    // For playlist playback
    shared_ptr<Playlist> playlist;
    set<shared_ptr<Song>> cycle_songs;  // Songs that need to be played in this cycle
    set<shared_ptr<Song>> played_songs; // Songs already played in this cycle
    shared_ptr<Song> last_played_song;  // Last song that was playing

    PlaybackState();
};

#endif