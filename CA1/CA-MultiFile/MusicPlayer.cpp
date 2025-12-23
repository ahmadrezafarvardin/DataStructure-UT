#include "MusicPlayer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

MusicPlayer::MusicPlayer() : is_playing(false)
{
    initialize_sample_songs();
}

void MusicPlayer::initialize_sample_songs()
{
    all_songs.push_back(make_shared<Song>("Bohemian Rhapsody", "Queen"));
    all_songs.push_back(make_shared<Song>("Stairway to Heaven", "Led Zeppelin"));
    all_songs.push_back(make_shared<Song>("Hotel California", "Eagles"));
    all_songs.push_back(make_shared<Song>("Imagine", "John Lennon"));
    all_songs.push_back(make_shared<Song>("Smells Like Teen Spirit", "Nirvana"));
    all_songs.push_back(make_shared<Song>("Billie Jean", "Michael Jackson"));
    all_songs.push_back(make_shared<Song>("Sweet Child O' Mine", "Guns N' Roses"));
}

// ===== INPUT VALIDATION =====
bool MusicPlayer::get_integer_input(int &result, const string &input)
{
    stringstream ss(input);
    if (ss >> result)
    {
        string remainder;
        ss >> ws;
        getline(ss, remainder);
        return remainder.empty();
    }
    return false;
}

int MusicPlayer::get_validated_integer(const string &prompt)
{
    string input;
    int result;
    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (is_playing && (input == ">" || input == "<"))
        {
            handle_skip_command(input);
            continue;
        }

        if (get_integer_input(result, input))
        {
            return result;
        }
        cout << "enter an integer\n";
    }
}

string MusicPlayer::get_string_input(const string &prompt)
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (is_playing && (input == ">" || input == "<"))
        {
            handle_skip_command(input);
            continue;
        }

        return input;
    }
}

// ===== PLAYBACK STATUS DISPLAY =====
void MusicPlayer::display_playback_status()
{
    if (is_playing && currently_playing)
    {
        cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << "♪ song playing: " << currently_playing->display() << "\n";
        cout << "  source: " << current_playback.source_name << "\n";
        cout << "  > next";
        if (current_playback.source == PlaybackState::Source::PLAYLIST)
        {
            cout << " | < prev";
        }
        cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
    }
}

// ===== SKIP COMMANDS =====
void MusicPlayer::handle_skip_command(const string &cmd)
{
    if (cmd == ">")
    {
        skip_forward();
    }
    else if (cmd == "<" && current_playback.source == PlaybackState::Source::PLAYLIST)
    {
        skip_backward();
    }
}

void MusicPlayer::skip_forward()
{
    if (!is_playing)
        return;

    cout << "\n⏭️  Skipping forward...\n";

    if (current_playback.source == PlaybackState::Source::PLAYLIST)
    {
        advance_playlist();
    }
    else
    {
        advance_queue();
    }
}

void MusicPlayer::skip_backward()
{
    if (!is_playing || current_playback.source != PlaybackState::Source::PLAYLIST)
        return;

    cout << "\n⏮️  Skipping backward...\n";

    auto &pl = current_playback.playlist;
    if (!pl || pl->get_size() == 0)
    {
        stop_playback();
        return;
    }

    int current_idx = find_song_index(pl, currently_playing);
    if (current_idx == -1)
        current_idx = 0;

    int prev_idx = (current_idx - 1 + pl->get_size()) % pl->get_size();
    currently_playing = pl->songs.get_song(prev_idx);
    current_playback.last_played_song = currently_playing;
    current_playback.played_songs.insert(currently_playing);

    cout << "Now playing: " << currently_playing->display() << "\n";

    check_cycle_completion();
}

int MusicPlayer::find_song_index(shared_ptr<Playlist> pl, shared_ptr<Song> song)
{
    for (int i = 0; i < pl->get_size(); i++)
    {
        if (pl->songs.get_song(i) == song)
        {
            return i;
        }
    }
    return -1;
}

void MusicPlayer::advance_playlist()
{
    auto &pl = current_playback.playlist;
    if (!pl || pl->get_size() == 0)
    {
        stop_playback();
        return;
    }

    int current_idx = find_song_index(pl, currently_playing);
    if (current_idx == -1)
        current_idx = -1;

    int next_idx = (current_idx + 1) % pl->get_size();
    currently_playing = pl->songs.get_song(next_idx);
    current_playback.last_played_song = currently_playing;
    current_playback.played_songs.insert(currently_playing);

    cout << "Now playing: " << currently_playing->display() << "\n";

    check_cycle_completion();
}

void MusicPlayer::check_cycle_completion()
{
    bool all_played = true;
    for (const auto &song : current_playback.cycle_songs)
    {
        if (current_playback.played_songs.count(song) == 0)
        {
            bool still_exists = false;
            for (int i = 0; i < current_playback.playlist->get_size(); i++)
            {
                if (current_playback.playlist->songs.get_song(i) == song)
                {
                    still_exists = true;
                    break;
                }
            }

            if (still_exists)
            {
                all_played = false;
                break;
            }
        }
    }

    if (all_played)
    {
        cout << "✓ Playlist cycle complete.\n";
        stop_playback();
    }
}

void MusicPlayer::advance_queue()
{
    if (song_queue.empty())
    {
        cout << "Queue playback complete.\n";
        stop_playback();
        return;
    }

    currently_playing = song_queue.front();
    song_queue.pop();

    cout << "Now playing: " << currently_playing->display() << "\n";

    if (song_queue.empty())
    {
        cout << "This was the last song in queue.\n";
        stop_playback();
    }
}

void MusicPlayer::stop_playback()
{
    if (!playback_stack.empty())
    {
        cout << "⏪ Resuming previous playback...\n";
        current_playback = playback_stack.top();
        playback_stack.pop();

        if (current_playback.source == PlaybackState::Source::PLAYLIST)
        {
            resume_playlist();
        }
        else
        {
            if (!song_queue.empty())
            {
                currently_playing = song_queue.front();
                song_queue.pop();
                is_playing = true;
                cout << "Resumed: " << currently_playing->display() << "\n";
            }
            else
            {
                is_playing = false;
                currently_playing = nullptr;
            }
        }
    }
    else
    {
        is_playing = false;
        currently_playing = nullptr;
        cout << "⏹️  Playback stopped.\n";
    }
}

void MusicPlayer::resume_playlist()
{
    auto &pl = current_playback.playlist;

    int start_idx = find_song_index(pl, current_playback.last_played_song);
    if (start_idx == -1)
        start_idx = 0;

    bool found = false;
    for (int i = 0; i < pl->get_size(); i++)
    {
        int idx = (start_idx + 1 + i) % pl->get_size();
        shared_ptr<Song> candidate = pl->songs.get_song(idx);

        if (current_playback.cycle_songs.count(candidate) > 0 &&
            current_playback.played_songs.count(candidate) == 0)
        {
            currently_playing = candidate;
            current_playback.last_played_song = candidate;
            current_playback.played_songs.insert(candidate);
            is_playing = true;
            found = true;
            cout << "Resumed: " << currently_playing->display() << "\n";
            break;
        }
    }

    if (!found)
    {
        cout << "Playlist cycle was already complete.\n";
        stop_playback();
    }
}

void MusicPlayer::start_playlist_playback(shared_ptr<Playlist> playlist, int start_pos)
{
    if (!playlist || playlist->get_size() == 0)
    {
        cout << "Cannot play empty playlist.\n";
        return;
    }

    if (start_pos < 1)
        start_pos = 1;
    if (start_pos > playlist->get_size())
        start_pos = playlist->get_size();

    if (is_playing)
    {
        playback_stack.push(current_playback);
        cout << "⏸️  Pausing current playback...\n";
    }

    current_playback = PlaybackState();
    current_playback.source = PlaybackState::Source::PLAYLIST;
    current_playback.source_name = playlist->name;
    current_playback.playlist = playlist;

    for (int i = 0; i < playlist->get_size(); i++)
    {
        current_playback.cycle_songs.insert(playlist->songs.get_song(i));
    }

    int idx = start_pos - 1;
    currently_playing = playlist->songs.get_song(idx);
    current_playback.last_played_song = currently_playing;
    current_playback.played_songs.insert(currently_playing);
    is_playing = true;

    cout << "\n▶️  Playing playlist '" << playlist->name << "' from position " << start_pos << "\n";
    cout << "Now playing: " << currently_playing->display() << "\n";
}

void MusicPlayer::start_queue_playback()
{
    if (song_queue.empty())
    {
        cout << "Queue is empty.\n";
        return;
    }

    if (is_playing)
    {
        playback_stack.push(current_playback);
        cout << "⏸️  Pausing current playback...\n";
    }

    current_playback = PlaybackState();
    current_playback.source = PlaybackState::Source::QUEUE;
    current_playback.source_name = "queue";

    currently_playing = song_queue.front();
    song_queue.pop();
    is_playing = true;

    cout << "\n▶️  Playing from queue\n";
    cout << "Now playing: " << currently_playing->display() << "\n";
}

shared_ptr<Playlist> MusicPlayer::find_playlist(const string &name)
{
    for (auto &pl : playlists)
    {
        if (pl->name == name)
            return pl;
    }
    return nullptr;
}

void MusicPlayer::run()
{
    cout << "🎵 Welcome to Music Player!\n";
    while (true)
    {
        show_main_page();
    }
}

void MusicPlayer::show_main_page()
{
    cout << "\n╔════════════════════════════╗\n";
    cout << "║       Main Page          ║\n";
    cout << "╚════════════════════════════╝\n";
    display_playback_status();

    cout << "1. songs\n";
    cout << "2. playlists\n";
    cout << "3. song queue\n";
    cout << "0. exit\n";

    int choice = get_validated_integer("Select: ");

    switch (choice)
    {
    case 1:
        show_songs_list_page();
        break;
    case 2:
        show_playlists_page();
        break;
    case 3:
        show_queue_page();
        break;
    case 0:
        cout << "\n👋 Goodbye!\n";
        exit(0);
    default:
        cout << "Invalid option.\n";
    }
}

void MusicPlayer::show_songs_list_page()
{
    while (true)
    {
        cout << "\n╔════════════════════════════╗\n";
        cout << "║      list of songs       ║\n";
        cout << "╚════════════════════════════╝\n";
        display_playback_status();

        for (size_t i = 0; i < all_songs.size(); i++)
        {
            cout << (i + 1) << ". " << all_songs[i]->display() << "\n";
        }
        cout << "0. back\n";

        int choice = get_validated_integer("Select: ");

        if (choice == 0)
            return;
        if (choice < 1 || choice > (int)all_songs.size())
        {
            cout << "Invalid selection.\n";
            continue;
        }

        show_song_details_page(all_songs[choice - 1]);
    }
}

void MusicPlayer::show_song_details_page(shared_ptr<Song> song)
{
    while (true)
    {
        cout << "\n"
             << song->display() << "\n";
        display_playback_status();

        cout << "1. list of playlists\n";
        cout << "2. add to play list\n";
        cout << "3. add to queue\n";
        cout << "0. back\n";

        int choice = get_validated_integer("Select: ");

        switch (choice)
        {
        case 1:
            show_playlists_containing_song(song);
            break;
        case 2:
            add_song_to_playlist_ui(song);
            return;
        case 3:
            song_queue.push(song);
            cout << "song added to queue\n";
            return;
        case 0:
            return;
        default:
            cout << "Invalid option.\n";
        }
    }
}

void MusicPlayer::show_playlists_containing_song(shared_ptr<Song> song)
{
    cout << "\n=== Playlists containing this song ===\n";

    vector<shared_ptr<Playlist>> containing;
    for (auto &pl : playlists)
    {
        if (pl->contains_song(song->get_title()))
        {
            containing.push_back(pl);
        }
    }

    if (containing.empty())
    {
        cout << "(none)\n";
        return;
    }

    for (size_t i = 0; i < containing.size(); i++)
    {
        cout << (i + 1) << ". " << containing[i]->name << "\n";
    }
    cout << "0. back\n";

    int choice = get_validated_integer("Select: ");

    if (choice > 0 && choice <= (int)containing.size())
    {
        show_playlist_page(containing[choice - 1]);
    }
}

void MusicPlayer::add_song_to_playlist_ui(shared_ptr<Song> song)
{
    string name = get_string_input("Enter playlist name: ");

    auto playlist = find_playlist(name);
    if (!playlist)
    {
        cout << "Playlist not found.\n";
        return;
    }

    if (playlist->contains_song(song->get_title()))
    {
        cout << "song already exists\n";
        return;
    }

    cout << "\nCurrent songs in '" << playlist->name << "':\n";
    if (playlist->get_size() == 0)
    {
        cout << "(empty)\n";
    }
    else
    {
        for (int i = 0; i < playlist->get_size(); i++)
        {
            cout << (i + 1) << ". " << playlist->songs.get_song(i)->display() << "\n";
        }
    }

    int pos = get_validated_integer("where do you want to add it: ");

    if (pos < 1)
    {
        pos = 0;
    }
    else if (pos > playlist->get_size())
    {
        pos = playlist->get_size();
    }
    else
    {
        pos = pos - 1;
    }

    playlist->add_song_to_playlist(song, pos);
    song->add_playlist_reference(playlist->name);

    cout << "song added to playlist\n";
}

void MusicPlayer::show_playlists_page()
{
    while (true)
    {
        cout << "\n╔════════════════════════════╗\n";
        cout << "║    list of playlists     ║\n";
        cout << "╚════════════════════════════╝\n";
        display_playback_status();

        if (playlists.empty())
        {
            cout << "(No playlists)\n\n";
        }
        else
        {
            for (size_t i = 0; i < playlists.size(); i++)
            {
                cout << (i + 1) << ". " << playlists[i]->name << "\n";
            }
        }

        cout << "-1. add playlist\n";
        cout << "0. back\n";

        int choice = get_validated_integer("Select: ");

        if (choice == 0)
            return;
        if (choice == -1)
        {
            add_new_playlist();
            continue;
        }
        if (choice > 0 && choice <= (int)playlists.size())
        {
            show_playlist_page(playlists[choice - 1]);
        }
        else
        {
            cout << "Invalid selection.\n";
        }
    }
}

void MusicPlayer::add_new_playlist()
{
    while (true)
    {
        string name = get_string_input("enter a name for the new playlist: ");

        if (find_playlist(name))
        {
            cout << "playlist already exists\n";
            continue;
        }

        playlists.push_back(make_shared<Playlist>(name));
        cout << "new playlist added to list\n";
        return;
    }
}

void MusicPlayer::show_playlist_page(shared_ptr<Playlist> playlist)
{
    while (true)
    {
        cout << "\n"
             << playlist->name << "\n";
        display_playback_status();

        if (playlist->get_size() == 0)
        {
            cout << "(empty)\n";
        }
        else
        {
            for (int i = 0; i < playlist->get_size(); i++)
            {
                cout << (i + 1) << ". " << playlist->songs.get_song(i)->display() << "\n";
            }
        }

        cout << "-2. play\n";
        cout << "-1. delete a song\n";
        cout << "0. back\n";

        int choice = get_validated_integer("Select: ");

        if (choice == 0)
            return;
        if (choice == -2)
        {
            play_playlist_ui(playlist);
        }
        else if (choice == -1)
        {
            delete_song_from_playlist_ui(playlist);
        }
        else if (choice > 0 && choice <= playlist->get_size())
        {
            show_song_details_page(playlist->songs.get_song(choice - 1));
        }
        else
        {
            cout << "Invalid selection.\n";
        }
    }
}

void MusicPlayer::play_playlist_ui(shared_ptr<Playlist> playlist)
{
    if (playlist->get_size() == 0)
    {
        cout << "Cannot play empty playlist.\n";
        return;
    }

    int pos = get_validated_integer("Start from position: ");
    start_playlist_playback(playlist, pos);
}

void MusicPlayer::delete_song_from_playlist_ui(shared_ptr<Playlist> playlist)
{
    if (playlist->get_size() == 0)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    int pos = get_validated_integer("which song: ");

    if (pos < 1)
        pos = 1;
    if (pos > playlist->get_size())
        pos = playlist->get_size();

    shared_ptr<Song> removed = playlist->delete_song_from_playlist(pos - 1);
    if (removed)
    {
        removed->remove_playlist_reference(playlist->name);
        cout << "song deleted\n";
    }
}

void MusicPlayer::show_queue_page()
{
    while (true)
    {
        cout << "\n╔════════════════════════════╗\n";
        cout << "║      songs in queue      ║\n";
        cout << "╚════════════════════════════╝\n";
        display_playback_status();

        if (song_queue.empty())
        {
            cout << "(empty)\n";
        }
        else
        {
            queue<shared_ptr<Song>> temp = song_queue;
            int i = 1;
            while (!temp.empty())
            {
                cout << i++ << ". " << temp.front()->display() << "\n";
                temp.pop();
            }
        }

        cout << "-1. play\n";
        cout << "0. back\n";

        int choice = get_validated_integer("Select: ");

        if (choice == 0)
            return;
        if (choice == -1)
        {
            start_queue_playback();
        }
        else if (choice > 0)
        {
            queue<shared_ptr<Song>> temp = song_queue;
            int idx = 1;
            shared_ptr<Song> selected = nullptr;

            while (!temp.empty() && idx <= choice)
            {
                if (idx == choice)
                {
                    selected = temp.front();
                    break;
                }
                temp.pop();
                idx++;
            }

            if (selected)
            {
                show_song_details_page(selected);
            }
            else
            {
                cout << "Invalid selection.\n";
            }
        }
    }
}