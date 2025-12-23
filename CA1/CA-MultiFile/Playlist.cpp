#include "Playlist.h"

Playlist::Playlist(string n) : name(move(n)) {}

bool Playlist::add_song_to_playlist(const shared_ptr<Song> &song, int position)
{
    if (song_titles.count(song->get_title()) > 0)
        return false;

    songs.add_song(song, position);
    song_titles.insert(song->get_title());
    return true;
}

shared_ptr<Song> Playlist::delete_song_from_playlist(int index)
{
    if (index < 0 || index >= songs.get_size())
        return nullptr;

    SongNode *node = songs.get_node_at(index);
    shared_ptr<Song> removed_song = node->song;
    songs.remove_song(index);
    song_titles.erase(removed_song->get_title());
    return removed_song;
}

bool Playlist::contains_song(const string &title) const
{
    return song_titles.count(title) > 0;
}

int Playlist::get_size() const
{
    return songs.get_size();
}