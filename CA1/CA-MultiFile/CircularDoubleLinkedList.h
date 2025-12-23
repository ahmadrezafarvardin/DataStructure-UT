#ifndef CIRCULAR_DOUBLE_LINKED_LIST_H
#define CIRCULAR_DOUBLE_LINKED_LIST_H

#include "Song.h"
#include <memory>
#include <stdexcept>

using namespace std;

struct SongNode
{
    shared_ptr<Song> song;
    unique_ptr<SongNode> next;
    SongNode *prev;

    explicit SongNode(shared_ptr<Song> s);
};

class CircularDoubleLinkedList
{
private:
    unique_ptr<SongNode> head;
    SongNode *tail;
    int size;

public:
    CircularDoubleLinkedList();
    ~CircularDoubleLinkedList() = default;

    int get_size() const;
    bool empty() const;

    SongNode *get_node_at(int index) const;
    SongNode *get_next(SongNode *node) const;
    SongNode *get_prev(SongNode *node) const;

    void add_song(shared_ptr<Song> s, int index);
    void remove_song(int index);
    shared_ptr<Song> get_song(int index) const;
};

#endif