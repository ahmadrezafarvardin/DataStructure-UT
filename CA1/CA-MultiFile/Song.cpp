#include "Song.h"

Song::Song(string t, string a)
    : title(move(t)), artist(move(a)) {}

string Song::display() const
{
    return title + ", " + artist;
}

string Song::get_title() const
{
    return title;
}

void Song::add_playlist_reference(const string &playlist_name)
{
    playlists_containing.push_back(playlist_name);
}

void Song::remove_playlist_reference(const string &playlist_name)
{
    playlists_containing.erase(
        remove(playlists_containing.begin(), playlists_containing.end(), playlist_name),
        playlists_containing.end());
}

vector<string> Song::get_playlists() const
{
    return playlists_containing;
}