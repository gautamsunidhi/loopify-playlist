# Loopify: Doubly Linked Playlist

## Introduction:
Loopify is a simple console application that demonstrates a **doubly linked list** used as a music playlist.
Each song is stored in a node that points both **forward** and **backward**, which lets the user move to the next or previous song and wrap around the playlist.
The app includes a small text menu so you can build a playlist, shuffle it, and "play" songs by their titles.

## Features:
- Doubly linked list playlist with 'head', 'tail,' and 'current' pointers.
- Menu-driven console interface:
    - Add a song by title.
    - Remove a song by title (first match).
    - Print the playlist in order.
    - Play next song (wraps around at the end).
    - Play previous song (wraps around at the beginning).
    - Shuffle playlist using a randomized algorithm.
- Handling the edge cases:
    - Empty playlist.
    - Single-song playlist.
    - Removing head, tail, and middle songs.
    - Playing next/previous repeatedly with wrapping.

## How the data structure works:
The core of the project is a **doubly linked list**:


- Each song is stored in a 'SongNode':
    - 'string title'
    - 'SongNode* prev'
    - 'SongNode* next'
- The 'Playlist' class keeps track of:
    - 'head' - first node in the list
    - 'tail' - last node in the list
    - 'current' - node that is currently "playing"


### Main Operations


- **addSong(title)**
Creates a new 'SongNode' and attaches it to the **end** of the list.
    - If the list is empty, 'head' and 'tail' both point to this node.
    - Otherwise it links 'tail <-> newNode' and updates 'tail'.


- **removeSong(title)**
Walks through the list until it finds the first node with the matching title and removes it by relinking its neighbors:
   - If it is 'head', move 'head' to 'head->next'.
   - If it is 'tail', move 'tail' to 'tail->prev'.
   - Updates 'current' if needed so future 'playNext' / 'playPrevious' calls still work.



- **playNext()**
    - If 'current' is 'nullptr' and the list is not empty, it starts at 'head'.
    - Otherwise it moves to 'current->next'.
    - If we were at 'tail' and there is no 'next', it **wraps around** to 'head'.
    - Returns the title of the new 'current' node (or '""' if the list is empty).




- **playPrevious()**
    - If 'current' is 'nullptr' and the list is not empty, it starts at 'tail'.
    - Otherwise it moves to 'current->prev'.
    - If we were at 'head' and there is no 'prev', it **wraps around** to 'tail'.
    - Returns the title of the new 'current' node (or '""' if the list is empty).



- **shuffle()**
    - Copies pointers to all nodes into an array.
    - Uses a Fisher-Yates-style shuffle to randomize the array of pointers.
    - Rebuilds the 'prev' / 'next' links according to the shuffled order.
    - Updates 'head', 'tail', and sets 'current' back to 'nullptr' so the next call to 'playNext()' starts at the new first song.


---


## Usage
When we run the program, we see:

```
Loopify: Doubly Linked Playlist Application
This program lets you build and play a music playlist.


Playlist Menu

0 - Add a song
1 - Remove a song
2 - Print playlist
3 - Play next song
4 - Play previous song
5 - Shuffle playlist
Q - Quit

Enter your choice:
```
### Example session:
1. Add a few songs
    - Choose 0 and enter titles like A, B, C, D.

2. Print playlist
    - Choose 2 to see:
    Current playlist:
    1.A
    2.B
    3.C
    4.D

3. Play next and previous
    - Choose 3 repeatedly to step forward through the list and wrap from D back to A.
    - Choose 4 repeatedly to step backward and wrap from A back to D.

4. Shuffle
    - Choose 5 to randomize order
    - Use 2 and 3/4 again to see the shuffled order and play through it.

5. Quit
    - Choose Q or q to exit.


## File Structure

All project source files are stored in the project-files directory.
This folder contains:

- **main.cpp** - menu system and user interface
- **Playlist.cpp** - implementation of playlist operations
- **Playlist.h** - class declarations
- **SongNode.h** - definition of the doubly linked list node
- **loopify** - compiled executable after running g++

The repository root contains the main README.md file.

All compilation and program execution should be done from inside 'project-files/'.




## Application Demo
Loopify's demo focuses on interacting with the linked list via the console:

- Shows how adding/removing nodes changes the linked list.
- Demonstrates bidirectional traversal with playNext and playPrevious.
- Demonstrates reordering nodes with shuffle without recreating or deleting the songs themselves.
- Handles edge cases like:
    - Printing or playing when the playlist is empty.
    - Playing next/previous in a single-song playlist.
    - Removing head, tail, or the currently playing song.



## Testing

I manually tested the playlist operations through the menu:


- **Add/Print**
    - Added multiple songs and confirmed they appear in order.
    - Verified printing on an empty playlist shows no songs but does not crash.

- **Remove**
    - Removed a song from the:
        - Beginning (head)
        - Middle
        - End (tail)
        - And tested titles that don't exist.
    - Confirmed that printing after each removal shows the correct remaining songs.
    - Verified that removing from a single-song playlist leaves the list empty.

- **Play Next/ Previous**
    - Called 'playNext' and 'playPrevious' repeatedly in playlists of size 1 and >1.
    - Confirmed playback wraps correctly from tail->head and head->tail.
    - Checked behaviour after shuffles and removals.

- **Shuffle**
    - Shuffled lists of different sizes (2,3,4+ songs) and verified:
        - Playlist size stays the same.
        - All original songs remain.
        - Order changes most times the function is called.
    

## References (Description):
- Course materials and lectures for linked lists and doubly linked lists.
- Standard C++ documentation for <string>, <cstdlib> / <ctime> used in the shuffle implementation.
- Fisher-Yates shuffle concept, adapted into array-based pointer shuffle.

## References(Cited):

1. Vahid,F.,Lysecky,R.,Edgcomb,A.,Jimenez,A.,Lysecky,S.,Rajasekhar,Y.,& Wheatland,N.(2022). 
   *CSPB 2270: Computer Science 2: Data Structures. zybooks.*
   https://learn.zybooks.com/zybook/COLORADOCSPB2270DataStructuresGuinnFall2025

2. CppReference.com(n.d.).C++ *standard library reference.* Retrieved November 21,2025, from 
   https://en.cppreference.com/

3. GeeksforGeeks.(n.d.).*Shuffle a given array using Fisher-Yates shuffle algorithm.* Retrieved November 21, 2025 from
   https://www.geeksforgeeks.org/dsa/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/

4. GeeksforGeeks.(n.d.).*Doubly linked list.* Retrieved November 21, 2025, from 
   https://www.geeksforgeeks.org/dsa/doubly-linked-list/


## Future Improvements:
- Store additional song metadata (artist, album, duration).
- Save and load playlists from a file.
- Support skipping directly to a specific index in the playlist.
- Add a graphical or web interface on top of the same data structure.


