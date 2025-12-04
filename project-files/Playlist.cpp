#include "Playlist.h" // Brings in the Playlist class and the SongNode struct declarations.

#include <iostream> 
#include <cstdlib> // For rand() and srand() to generate random numbers.
#include <ctime> // For time() to seed the random number generator.

using namespace std;

// CONSTRUCTOR / DESTRUCTOR

// Constructor: Creates an empty playlist with no songs.
Playlist::Playlist() {
    // Start with an empty list.
    head = nullptr;      // No first song yet.
    tail = nullptr;      // No last song yet.
    current = nullptr;   // No song is marked as currently playing.
}

// Destructor: Called when the playlist is no longer used.
// This function deletes all SongNodes that were created with new.
Playlist::~Playlist() {
    SongNode* cur = head;  // Start at the first song in the list.

    // Move through the list and delete each node.
    while (cur != nullptr) {                  // Stop when cur reaches the end (nullptr).
        SongNode* nextNode = cur->next;       // Remember the next node before deleting the current one.
        delete cur;                           // Delete the current SongNode from memory.
        cur = nextNode;                       // Move on to the next node.
    }

    // After deleting all nodes, the playlist is empty.
    head = nullptr;       // No head node remains.
    tail = nullptr;       // No tail node remains.
    current = nullptr;    // No current song remains.
} 


// addSong: creates a song node with the given title and adds it at the end of the playlist.
void Playlist::addSong (string title) {
    SongNode* newNode = new SongNode (title);  // Creates a new SongNode on the heap.

    // Case 1: the playlist is empty, so this song becomes the first and last song.
    if (head == nullptr) {    // The list has no songs yet.
        head = newNode;       // Head now points to this new song.
        tail = newNode;       // Tail also points to this new song.
        // current stays nullptr here; first playNext() will set it to head.
    }

    // Case 2: the playlist already has songs. Attach this song to the end.
    else {
        newNode->prev = tail;   // The new song comes after the current tail.
        tail->next = newNode;   // The current tail points forward to the new song.
        tail = newNode;         // Tail now points to the new last song.

    }
}


// removeSong: removes the first song whose title matches the given string.
void Playlist::removeSong(string title) {
    // If the playlist is empty, there is nothing to remove.
    if (head == nullptr) {
        return;
    }

    SongNode* cur = head;   // Start searching from the first song.

    // Look for the first node with a matching title.
    while (cur != nullptr && cur->title != title) {
        cur = cur->next;  // Move to the next song if this one does not match.
    }

    // if cur is nullptr, no song with this title was found.
    if (cur == nullptr) {
        return;       // Nothing to remove.
    }

    // At this point, cur points to the song that should be removed.

    // If the current pointer points to this song, move current to neighbor.
    // This prevents current from pointing to deleted memory.
    if (current == cur) {
        if (cur->next != nullptr)  {   // if there is a song after this one,
            current = cur->next;       // move current to that song.

        }
        else if (cur->prev != nullptr) { // Otherwise, if there is a song before this one,
            current = cur->prev;         // move current to that song.
        }
        else {                           // if there is no next and no previous song,
            current = nullptr;           // the playlist will become empty.
        }
    }
    
    // Fix the links around the node being removed.

    // Case 1: removing the head node.
    if (cur == head) {
        head = cur->next;         // Move head to the next song.
        if (head != nullptr) {
            head->prev = nullptr;  // New head has no previous song.
        }
    }
    else {
        // Link the previous node's next pointer around cur.
        cur->prev->next = cur->next;
    }

    // Case 2: removing the tail node.
    if (cur == tail) {
        tail = cur->prev;             // Move tail backward to the previous song.
        if (tail != nullptr) {
            tail->next = nullptr;     // New tail has no next song.
        }
    }
    else {
        // Link the next node's prev pointer around cur.
        cur->next->prev = cur->prev;
    }

    // Delete the node for the removed song.
    delete cur;

    // If the playlist is now empty, clear all pointers.
    if (head == nullptr) {
        tail = nullptr;
        current = nullptr;
    }
}


// printOnce: prints all songs from first to last, one time only.
void Playlist::printOnce() {
    SongNode* cur = head;      // Start at the first song.
    int index = 1;             // Start numbering songs at 1.

    // Move through the playlist from head to tail.
    while (cur != nullptr) {
        cout << index << "." << cur->title << endl;  // Print the song number and its title.
        cur = cur->next;                             // Move to the next song.
        index = index + 1;                           // Increase the song number.
    }
}


// playNext: moves to the next song and returns its title.
// If the current song is at the end, this function wraps back to the first song.
string Playlist::playNext() {
    // If the playlist has no songs, there is nothing to play.
    if (head == nullptr) {
        return "";      // Return an empty string to signal no song.
    }

    // If no song is selected yet, start at the first song.
    if (current == nullptr) {
        current = head;           // Select the first song.
        return current->title;    // Return the title of the first song.
    }

    // If the current song is the last song, wrap back to the first song.
    if (current == tail) {
        current = head;          // Wrap around to the beginning.
    }
    else {
        // Otherwise move to the next song in the list.
        current = current->next;
    }

    return current->title;      // Return the song that is now current.
}


// playPrevious: moves to the previous song and returns its title.
// If the current song is the first one, this function wraps around to the last song.
string Playlist::playPrevious() {
    // If the playlist has no songs, there is nothing to play.
    if (head == nullptr) {
        return "";           // Return an empty string to signal no song.
    }

    // If no song is selected yet, start at the last song.
    if (current == nullptr) {
        current = tail;            // Select the last song.
        return current->title;     // Return the title of the last song.
    }

    // If the current song is the first song, wrap back to the last song.
    if (current == head) {
        current = tail;           // Wrap around to the end.
    }
    else {
        // Otherwise move to the previous song in the list.
        current = current->prev;
    }

    return current->title;        // Return the song that is now current.
}



// shuffle: randomly changes the order of the songs in the playlist.

/*
How randomness is created in this function:
- rand() returns a pseudo-random integer between 0 and RAND_MAX.
"Pseudo-random" means it looks random but is based on a starting value (the seed).
- srand(seed) sets the seed for rand(). Different seeds give different sequences.
- time(NULL) returns the current time as an integer, which changes every second.
* Using time(NULL) as the seed makes the shuffle different almost every time the program runs.
*/

void Playlist::shuffle() {
    // If there are 0 or 1 songs, shuffling does not change anything.
    if (head == nullptr || head == tail) {
        return;
    }

    // Step 1: Count how many songs are in the playlist.
    int count = 0;                // Number of nodes in the list.
    SongNode* cur = head;         // Start at the first song.
    while (cur != nullptr) {    // Move until the end of the list.
        count = count + 1;      // Increase the count for each song.
        cur = cur->next;        // Move to the next song.
    }

    // Step 2: Copy all node pointers into a dynamic array.
    // This array does not create new SongNodes. It only holds pointers to existing ones.
    SongNode** arr = new SongNode*[count];  // Create an array of SongNode pointers.


    cur = head;                               // Reset cur to start at the head again.
    for (int i = 0; i < count; i = i + 1) {
        arr[i] = cur;                         // Store the pointer to the current node in the array. 
        cur = cur->next;                      // Move to the next node.
    }

    // Step 3: Shuffle the array using rand().
    // Seed rand() using the current time, so the sequence of random numbers is different in most program runs.
    srand(time(NULL));

    // This loop performs a simple version of the Fisher-Yates shuffle.
    // It visits each position from the end toward the beginning and swaps it with a randomly chosen earlier (or equal) position.
    for (int i = count - 1; i > 0; i = i - 1) {
        int j = rand() % (i + 1);          // Random index from 0 to i (inclusive).

        // Swap the pointers at positions i and j.
        SongNode* temp = arr[i];           // Temporary variable for the swap.
        arr[i] = arr[j];                   // Move pointer at j into position i.
        arr[j] = temp;                     // Move temp (old arr[i]) into position j.
    }

    // After this loop, arr contains all the same SongNode pointers, but now they're in a new random order.

    // Step 4: Rebuild the linked list using the shuffled array.
    // The SongNode objects stay the same in memory, but their prev/next pointers are updated to match the shuffled order in arr.
    for (int i = 0; i < count; i = i + 1) {
        // Set the prev pointer for arr[i].
        if (i == 0) {
            arr[i]->prev = nullptr;       // First song has no previous song.
        }
        else {
            arr[i]->prev = arr[i - 1];    // Previous song is the one at index i - 1.
        }

        // Set the next pointer for arr[i].
        if (i == count - 1) {
            arr[i]->next = nullptr;       // Last song has no next song.
        }
        else {
            arr[i]->next = arr[i + 1];    // Next song is the one at index i + 1.
        }
    }


    // Step 5: Update head and tail.

    head = arr[0];               // New first song in the playlist.
    tail = arr[count - 1];       // New last song in the playlist.

    current = nullptr;             // let playNext() choose the new head on the next call.


    // Step 6: Free the dynamic array (but not the nodes themselves).
    delete[] arr;                // Release the helper array from memory.
                                 // The SongNode objects remain in the list.

                                 
}



