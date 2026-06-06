#pragma once
#include <string>
using namespace std;

class PlaylistNode {

    public:
    PlaylistNode();
    PlaylistNode(string id, string name, string artist, int length);
    void InsertAfter(PlaylistNode* node);
    void SetNext(PlaylistNode* nextNode);
    const string GetID() const;
    const string GetSongName() const;
    const string GetArtistName() const;
    const int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void PrintPlaylistNode();

    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;
};

class Playlist {

    private:
    PlaylistNode* head = nullptr;
    PlaylistNode* tail = nullptr;
    //rule of 3 copy consttructor, ensure that it is not used 
    Playlist(const Playlist&);

    public:
    //construct destruct
    Playlist();
    ~Playlist();
    //menu functions utilized in main
    void OutputFullPlaylist();
    void AddSong();
    void RemoveSong();
    void ChangePosition();
    void TotalTime();
    void OutputByArtist();
};