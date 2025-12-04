#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

int main()
{
    Playlist playlist;    // Playlist object that stores all songs
    string input;         // Stores the user's menu choice.
    string title;         // Stores song titles entered by the user.

    cout << "\n\n";
    cout << "Loopify: Doubly Linked Playlist Application" << endl;
    cout << "This program lets you build and play a music playlist." << endl;
     cout << "\n\n";
    // Main menu loop.
    while(true)
    {
        // Print menu options.
        cout << "Playlist Menu" << endl;
        cout << "\n";
        cout << "0 - Add a song" << endl;
        cout << "1 - Remove a song" << endl;
        cout << "2 - Print playlist" << endl;
        cout << "3 - Play next song" << endl;
        cout << "4 - Play previous song" << endl;
        cout << "5 - Shuffle playlist" << endl;
        cout << "Q - Quit" << endl;
        cout << "\n";
        cout << "Enter your choice: ";

        // Read the user's menu choice as a whole string
        getline(cin, input);

        // Option 0: Add a song
        if (input == "0")
        {
            cout << "\nAdd selected song." << endl;
            cout << "Enter song title: "; 
            getline(cin, title);        // Read a full line for the song title

            playlist.addSong(title);   // Add the song to the playlist.

            cout << "Song added to playlist." << endl;

            cout << "\n";
        }

        // Option 1: Remove song
        else if (input == "1")
        {
            cout << "\nRemove selected song." << endl;
            cout << "Enter song title to remove: ";
            getline(cin, title);          // Read the title to remove

            playlist.removeSong(title);  // Remove the first song with this title.

            cout << "If the song was found, it has been removed." << endl;

            cout << "\n";
        }

        // Option 2: Print the playlist.
        else if(input == "2")
        {
            cout << "\nPrint selected playlist." << endl;
            cout << "Current playlist: " << endl;

            playlist.printOnce();       // Print all songs in order

            cout << "\n";
        }

        // Option 3: Play next song.
        else if (input == "3")
        {
           cout << "\nPlay the next song." << endl;

           string nextTitle = playlist.playNext();   //Move to the next song.

           if (nextTitle == "")
           {
            cout << "Playlist is empty. No song to play." << endl;
           }
           else
           {
            cout << "Now playing (next): " << nextTitle << endl;
           }

           cout << "\n";
        }
        
        // Option 4: Play previous song.
        else if (input == "4")
        {
            cout << "\nPlay previous song." << endl;

            string prevTitle = playlist.playPrevious();   // Move to the previous song.

            if (prevTitle == "")
            {
                cout << "Playlist is empty. No song to play." << endl;
            }
            else
            {
                cout << "Now playing (previous): " << prevTitle << endl;

            }

            cout << "\n";
        }

        // Option 5: Shuffle playlist.
        else if (input == "5")
        {
            cout << "\nShuffle selected playlist." << endl;

            playlist.shuffle(); // Randomly rearrange the songs.

            cout << "Playlist has been shuffled." << endl;
            cout << "New order:" << endl;
            playlist.printOnce();

            cout << "\n";
        }

        // Option Q: Quit
        else if (input == "Q" || input == "q")
        {
            cout << "\nThank you for using Loopify!" << endl;
            cout << "Quitting program..." << endl;
            cout << "\n";
            break;
        }

        // Any other input: invalid.

        else
        {
            cout << "\nInvalid input. Please enter 0-5 or Q to quit." << endl;
        }

        cout << "\n";
    }

    return 0;
}

/*
How to compile:
1.  cd project-files (to move into this folder because all of the files are in this subfolder)
2.  g++ -std=c++17 main.cpp Playlist.cpp -o loopify
3.  ./loopify
*/
