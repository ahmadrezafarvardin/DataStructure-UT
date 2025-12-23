#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "PlaybackState.h"
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

class MusicPlayer
{
private:
    vector<shared_ptr<Song>> all_songs;
    vector<shared_ptr<Playlist>> playlists;
    queue<shared_ptr<Song>> song_queue;

    stack<PlaybackState> playback_stack;
    shared_ptr<Song> currently_playing;
    PlaybackState current_playback;
    bool is_playing;

    // Input validation
    bool get_integer_input(int &result, const string &input);
    int get_validated_integer(const string &prompt);
    string get_string_input(const string &prompt);

    // Playback status
    void display_playback_status();

    // Skip commands
    void handle_skip_command(const string &cmd);
    void skip_forward();
    void skip_backward();

    // Playback helpers
    int find_song_index(shared_ptr<Playlist> pl, shared_ptr<Song> song);
    void advance_playlist();
    void check_cycle_completion();
    void advance_queue();
    void stop_playback();
    void resume_playlist();

    // Playback control
    void start_playlist_playback(shared_ptr<Playlist> playlist, int start_pos);
    void start_queue_playback();

    // Helper functions
    shared_ptr<Playlist> find_playlist(const string &name);

    // UI Pages
    void show_main_page();
    void show_songs_list_page();
    void show_song_details_page(shared_ptr<Song> song);
    void show_playlists_containing_song(shared_ptr<Song> song);
    void add_song_to_playlist_ui(shared_ptr<Song> song);
    void show_playlists_page();
    void add_new_playlist();
    void show_playlist_page(shared_ptr<Playlist> playlist);
    void play_playlist_ui(shared_ptr<Playlist> playlist);
    void delete_song_from_playlist_ui(shared_ptr<Playlist> playlist);
    void show_queue_page();

    void initialize_sample_songs();

public:
    MusicPlayer();
    void run();
};

#endif