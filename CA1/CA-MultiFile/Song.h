#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Song
{
public:
    Song(string t, string a);

    string display() const;
    string get_title() const;

    void add_playlist_reference(const string &playlist_name);
    void remove_playlist_reference(const string &playlist_name);
    vector<string> get_playlists() const;

private:
    string title;
    string artist;
    vector<string> playlists_containing;
};

#endif