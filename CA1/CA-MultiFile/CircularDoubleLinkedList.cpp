#include "CircularDoubleLinkedList.h"

SongNode::SongNode(shared_ptr<Song> s)
    : song(move(s)), next(nullptr), prev(nullptr) {}

CircularDoubleLinkedList::CircularDoubleLinkedList()
    : tail(nullptr), size(0) {}

int CircularDoubleLinkedList::get_size() const
{
    return size;
}

bool CircularDoubleLinkedList::empty() const
{
    return size == 0;
}

SongNode *CircularDoubleLinkedList::get_node_at(int index) const
{
    if (!head || index < 0 || index >= size)
        throw out_of_range("Index out of range");

    SongNode *current = head.get();
    for (int i = 0; i < index; i++)
        current = current->next.get();
    return current;
}

SongNode *CircularDoubleLinkedList::get_next(SongNode *node) const
{
    if (!node)
        return nullptr;
    return node->next ? node->next.get() : head.get();
}

SongNode *CircularDoubleLinkedList::get_prev(SongNode *node) const
{
    if (!node)
        return nullptr;
    return node->prev ? node->prev : tail;
}

void CircularDoubleLinkedList::add_song(shared_ptr<Song> s, int index)
{
    if (index < 0 || index > size)
        throw out_of_range("Index out of range");

    auto newNode = make_unique<SongNode>(move(s));

    if (!head)
    {
        tail = newNode.get();
        head = move(newNode);
    }
    else if (index == 0)
    {
        newNode->next = move(head);
        newNode->next->prev = newNode.get();
        head = move(newNode);
    }
    else if (index == size)
    {
        newNode->prev = tail;
        tail->next = move(newNode);
        tail = tail->next.get();
    }
    else
    {
        SongNode *prevNode = get_node_at(index - 1);
        newNode->next = move(prevNode->next);
        newNode->prev = prevNode;
        newNode->next->prev = newNode.get();
        prevNode->next = move(newNode);
    }

    size++;
}

void CircularDoubleLinkedList::remove_song(int index)
{
    if (empty() || index < 0 || index >= size)
        throw out_of_range("Index out of range");

    if (size == 1)
    {
        head.reset();
        tail = nullptr;
    }
    else if (index == 0)
    {
        auto oldHead = move(head);
        head = move(oldHead->next);
        head->prev = nullptr;
    }
    else
    {
        SongNode *prevNode = get_node_at(index - 1);
        auto removeNode = move(prevNode->next);
        prevNode->next = move(removeNode->next);

        if (prevNode->next)
        {
            prevNode->next->prev = prevNode;
        }
        else
        {
            tail = prevNode;
        }
    }

    size--;
}

shared_ptr<Song> CircularDoubleLinkedList::get_song(int index) const
{
    return get_node_at(index)->song;
}