#ifndef PLAYLIST_H__
#define PLAYLIST_H__

#include <string>
#include "SongNode.h" // brings in the SongNode struct

using namespace std;

// The Playlist class stores songs using a non-circular doubly linked list.

// Invariant (non-empty list):
// - head points to the first SongNode
// - tail points to the last SongNode
// - head->prev == nullptr
// - tail->next == nullptr
// - for any middle node n: n->next->prev == n and n->prev->next == n

// Playback behaves logically like a circular playlist:
// - playNext() wraps from tail back to head
// - playPrevious() wraps from head back to tail
// but the next underlying next/prev pointers themselves don't form a circle.


class Playlist {
public:
    // Constructor: starts with an empty playlist.
    Playlist();

    // Destructor: deletes all SongNodes from memory.
    ~Playlist();

    // Adds a new song with the given title to the end of the playlist.
    void addSong(string title);

    // Removes the first song whose title matches the given string.
    // If no such song exists, the playlist is unchanged.
    void removeSong(string title);

    // Prints all songs in order from head to tail, exactly once.
    // (No looping, no infinite output.)
    void printOnce();

    // Moves to the next song and returns its title.

    /*
    Behavior:
    - If the playlist is empty, returns "" and leaves current as nullptr.
    - If current is nullptr and the list is non-empty, sets current to head.
    - Otherwise:
       * if current is tail, wraps around to head
       * else moves current = current->next
    */
    string playNext();

    // Moves to the previous song and returns its title.

    /*
    Behavior:
    - If the playlist is empty, returns "" and leaves current as nullptr.
    -If current is nullptr and the list is non-empty, sets current to tail.
    -Otherwise:
     * if current is head, wraps around to tail
     * else moves current = current->prev
    */
    string playPrevious();

    // Randomly shuffles the order of songs in the playlist.
    // (implementation will rearrange the next/prev pointers)
    void shuffle();

private:
    SongNode* head;        // pointer to the first song in the list (or nullptr)
    SongNode* tail;        // pointer to the last song in the list (or nullptr)
    SongNode* current;    // pointer to the currently playing song (or nullptr)

   // Optional private helpers that we can define in Playlist.cpp:
   // - void clear();   // delete all nodes
   // -SongNode * findSong(string title); // return pointer to first matching song
 
};

#endif // PLAYLIST_H__
