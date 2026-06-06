#include <cstdio>
#include <iostream>
#include <ostream>
#include "Playlist.h"
using namespace std;

void PrintMenu(string playlistName){
    //display menu for interaction
    cout << playlistName << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;
}

int main() {
    string playlistName;
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistName);
    Playlist myPlaylist;
    char input;
    cout << endl;

    //keep displaying menu until quit key is entered
    while(input != 'q'){
        PrintMenu(playlistName);
        cin >> input;
        if (input == 'a'){
            myPlaylist.AddSong();
        }
        if (input == 'd'){
            myPlaylist.RemoveSong();
        }
        if (input == 'c'){
            myPlaylist.ChangePosition();
        }
        if (input == 's'){
            myPlaylist.OutputByArtist();
        }
        if (input == 't'){
            myPlaylist.TotalTime();
        }
        if (input == 'o'){
            cout << playlistName << " - OUTPUT FULL PLAYLIST" << endl;
            myPlaylist.OutputFullPlaylist();
        }
    }
    return 0;
}