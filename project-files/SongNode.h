#ifndef SONGNODE_H__
#define SONGNODE_H__

#include <string>

using namespace std;

// This struct represents ONE song in the playlist.
// Each node stores a song title and pointers to the next and previous nodes.

struct SongNode {
    string title;     // stores the song's title
    SongNode* next;   // pointer to the next song in the playlist
    SongNode* prev;   // pointer to the previous song in the playlist

    // Constructor: sets up a SongNode with a title
    SongNode(string songTitle) {
        title = songTitle;  // set the title for this song
        next = nullptr;     // next pointer starts as NULL (no next song yet)
        prev = nullptr;     // previous pointer starts as NULL (no previous song yet)
    }
};

#endif // SONGNODE_H__