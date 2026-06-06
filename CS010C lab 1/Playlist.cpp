#include "Playlist.h"
#include <iostream>
#include <string>

//initialize node attributes to none for default
PlaylistNode::PlaylistNode()
: uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr)
{}

//initialize node attributes from params
PlaylistNode::PlaylistNode(string id, string name, string artist, int length)
: uniqueID(id), songName(name), artistName(artist), songLength(length)
{}

//pass in a node to be inserted after the target node. ex: a->InsertAfter(b) would insert node b after node a
void PlaylistNode::InsertAfter(PlaylistNode* nextNode){
    //store currnode next
    auto temp = GetNext();
    //set currnode next to inserted node
    SetNext(nextNode);
    //set next to equal the next of the currnode
    nextNode->SetNext(temp);
    delete temp;
}

//pass in a node to be set as the nextnodePtr for target node
void PlaylistNode::SetNext(PlaylistNode* nextNode){
    nextNodePtr = nextNode;
}

//return id
const string PlaylistNode::GetID() const{
    return uniqueID;
}

//return songname
const string PlaylistNode::GetSongName() const{
    return songName;
}

//return artist name
const string PlaylistNode::GetArtistName() const{
    return artistName;
}

//return song length
const int PlaylistNode::GetSongLength() const{
    return songLength;
}

//return next node
PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

//print all attributes of the playlistnode
void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

//default playlist has null head/tail
Playlist::Playlist()
: head(nullptr) , tail(nullptr)
{}

//iterate through list, deallocating all nodes and freeing memory
Playlist::~Playlist(){
    PlaylistNode *curr;
    //while curr keeps getting assigned to head, free up the memory
    for (curr = head ; head ; curr = head){
        //move head to next node, while also deleting the prior node (which is set to curr)
        head = head->GetNext();
        delete curr;
    }
}

//take user input attributes and create node to be added into list. If empty, head and tail are intialized otherwise node is added to back and becomes new tail
void Playlist::AddSong() {
    string id;
    string name;
    string artist;
    int length;

    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> id;
    cout << "Enter song's name:" << endl;
    cin.ignore();
    getline(cin, name);
    cout << "Enter artist's name:" << endl;
    getline(cin, artist);
    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;
    cout << endl;
    auto addNode = new PlaylistNode(id, name, artist, length);
    //catch case: if list is empty intialize new head/tail
    if (head == nullptr){
        head = addNode;
        tail = addNode;
    }
    else if(head == tail){ //catch case: if one item exists in list, make new entry tail
        head->SetNext(addNode);
        addNode->SetNext(nullptr);
        tail = addNode;

    }else{ //add item to back of list and reassign new tail;
        tail->SetNext(addNode);
        addNode->SetNext(nullptr);
        tail = addNode;
    }

    //memleak
    delete addNode;
    addNode = nullptr;
}

//iterate through existing playlist to find user entered id. Removes node and deallocates memory while maintaining linkage between surrounding nodes
void Playlist::RemoveSong(){
    string idToRemove;
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> idToRemove;

    if (head == nullptr){
        //catch empty list
        cout << "No songs in the playlist" << endl;
    }
    else{
        //double pointer iteration, to ensure that prior and post removal node can be linked together
        auto prevnode = new PlaylistNode();
        auto currnode = new PlaylistNode();
        currnode = head;
        prevnode = currnode;
        for (currnode = head ; currnode != nullptr ; currnode = currnode->GetNext()){
            //check case for head removal
            if (currnode->GetID() == idToRemove && currnode == head){
                head = currnode->GetNext();
                cout << "\"" << currnode->GetSongName() << "\" removed." << endl << endl;
                delete currnode;
            }
            //check case for tail removal
            else if (currnode->GetID() == idToRemove && currnode == tail){
                prevnode->SetNext(nullptr);
                cout << "\"" << currnode->GetSongName() << "\" removed." << endl << endl;
                delete currnode;
                tail = prevnode;
            }
            //final check, if node exists within list and is not head/tail
            else if (currnode->GetID() == idToRemove){
                auto temp = currnode;
                prevnode->SetNext(currnode->GetNext());
                cout << "\"" << currnode->GetSongName() << "\" removed." << endl << endl;
                delete temp;
            }
            prevnode = currnode;
        }
    }
}

//take in 2 position values (index begins at 1) and swap the values of the nodes. Does not work on 1 node lists, simply does not complete swap.
void Playlist::ChangePosition(){
    int currpos = 0;
    int newpos = 0;
    int playlistSize = 0;
    PlaylistNode* currposNode = nullptr;
    PlaylistNode* newposNode = nullptr;
    PlaylistNode* checknode = nullptr; //used for moving through list
    int i = 1; //starting val for iterator
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    cin >> currpos;
    cout << "Enter new position for song:" << endl;
    cin >> newpos;

    //catch case for empty or one node list
    if (head == tail || currpos == newpos){
        cout << "Swap could not be completed" << endl;
        return;
    }

    //find playlist size
    auto currnode = new PlaylistNode();
    for(currnode = head; currnode ; currnode = currnode->GetNext()){
        ++playlistSize;
    }
    
    //catch case for 2 node list
    if (playlistSize == 2){
        //if only 2 vals, swap
        auto temp = head;
        head = tail;
        tail->SetNext(temp);
        tail = temp;
        tail->SetNext(nullptr);
        //if current pos less than 1 then swap as specified in labspec (move node to head)
        //output message depends on whether tailsong was moved or headsong
        if (currpos <= 1){
            cout << "\"" << tail->GetSongName() << "\" moved to position 2" << endl;
        }
        else{
            cout << "\"" << tail->GetSongName() << "\" moved to position 1" << endl;
        }
    }


    //go through list, once the inputted possitions are found point to given nodes with currposNode and newposNode
    for (checknode = head ; checknode ; checknode = checknode->GetNext()){
        if (i == currpos){
            currposNode = checknode;
        }
        else if(i == newpos){
            newposNode = checknode;
        }
        ++i;
    }

    //by this point the input positions should have corresponding pointers to the nodes
    //(given that previous checks have not been triggered)

    //forward movement condition (currpos is BEFORE newpos)
    if (currpos < newpos){
        if (currpos == 1){ //node to be moved is head?
            head = currposNode->GetNext(); //establish new head as currhead->next
            currposNode->SetNext(newposNode->GetNext()); //currposNode is placed into the spot of newposNode
            newposNode->SetNext(currposNode); //newposNode is placed where currposNode was
        }
        else{
            PlaylistNode* currposPrev = nullptr;
            i = 1;
            //find value before currpos
            for (checknode = head ; checknode ; checknode = checknode->GetNext()){
                if (i == currpos - 1){ //if i is currently the position of the node before currposNode
                    currposPrev = checknode;
                }
                ++i;
            }
            //link currnode prev to currnode next (unlink currnode)
            currposPrev->SetNext(currposNode->GetNext());
            //link currnode to next of newposNode
            currposNode->SetNext(newposNode->GetNext());
            //place newposNode linked to currposNode
            newposNode->SetNext(currposNode);
        }
        //catch case: if we moved a node to occupy the space of the previous tail
        if(newposNode == tail){
            tail = currposNode;
        }

        //memleak 
        delete checknode;
        checknode = nullptr;
    }
    else if(currpos > newpos){ //catch case for backwards movement (currpos is AFTER newpos)
        //pointers for the nodes prior to currpos and newpos nodes
        PlaylistNode* currposPrev = nullptr;
        PlaylistNode* newposPrev = nullptr;

        i = 1;

        //find nodes prior to currposNode and newposNode, and point to them with corresponding pointers

        for (checknode = head ; checknode ; checknode = checknode->GetNext()){
            if (i == currpos - 1){
                currposPrev = checknode;
            }
            else if(i == newpos - 1){
                newposPrev = checknode;
            }
            ++i;
        }
        if (newpos == 1){ //catch case: we are moving a node into the head position
            //link prior to currposNode to next of currposNode (detach currpos from list)
            currposPrev->SetNext(currposNode->GetNext());
            //relink newpos into prior spot of currposNode
            currposNode->SetNext(newposNode);
            //reassign head to currposNode
            head = currposNode;
        }
        else{ //catch case: both currposNode and newposNode exist within the list outside of the edges
            currposPrev->SetNext(currposNode->GetNext());
            newposPrev->SetNext(currposNode);
            currposNode->SetNext(newposNode);
        }

        //catch case: the node we moved was the tail, we need to reassign

        if(currposNode == tail){
            tail = currposPrev;
        }

        //memleak 
        delete checknode;
        checknode = nullptr;


    }
    //display result of swap given that no edges were triggered
    cout << "\"" << currposNode->GetSongName() << "\" moved to position " << newpos << endl;
    cout << endl;
}

//tally all "songlength" attributes of existing nodes and return them to the user
void Playlist::TotalTime(){
    int totaltime = 0;
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    auto currnode = new PlaylistNode();
    for (currnode = head ; currnode != nullptr ; currnode = currnode->GetNext()){
        totaltime += currnode->GetSongLength();
    }

    cout << "Total time: " << totaltime << " seconds" << endl;
    cout << endl;

    //memleak
    delete currnode;
    currnode = nullptr;

}

//iterate through existing playlist and output all songs with user inputted artist name. Retains positions by iterating location counter regardless of if a song is found or not
void Playlist::OutputByArtist() {
    string artistToDisplay;
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl << endl;
    cin.ignore();
    getline(cin, artistToDisplay);

    auto currnode = new PlaylistNode();
    unsigned int location = 1;
    for (currnode = head ; currnode != nullptr ; currnode = currnode->GetNext()){
        if (currnode->GetArtistName() == artistToDisplay){
            cout << location << "." << endl;
            currnode->PrintPlaylistNode();
            cout << endl;
        }
        ++location;
    }
    delete currnode;
}

//iterate through playlist and simply print all attributes in a clean formatted manner. Also retains positions with the num counter
void Playlist::OutputFullPlaylist() {
    if (head == nullptr){
        cout << "Playlist is empty" << endl << endl;
    }
    else{
        auto currNode = new PlaylistNode();
        unsigned int num = 1;
        for (currNode = head ; currNode != nullptr ; currNode = currNode->GetNext()){
            cout << num << "." << endl;
            currNode->PrintPlaylistNode();
            cout << endl;
            ++num;
        }
        //no use, memleak
        delete currNode;
        currNode = nullptr;
    }
}