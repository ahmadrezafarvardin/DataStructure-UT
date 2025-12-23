#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "CircularDoubleLinkedList.h"
#include <set>
#include <string>
#include <memory>

using namespace std;

class Playlist
{
public:
    string name;
    CircularDoubleLinkedList songs;
    set<string> song_titles;

    Playlist(string n);

    bool add_song_to_playlist(const shared_ptr<Song> &song, int position);
    shared_ptr<Song> delete_song_from_playlist(int index);
    bool contains_song(const string &title) const;
    int get_size() const;
};

#endif