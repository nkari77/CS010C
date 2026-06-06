#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Nodes aka players contain a link to next and a "payload" which is the name
struct Node {
    string payload;
    Node* next;
};

//helper for node creation
Node* newNode(string payload) {
    //establish a new node
    Node* temp = new Node;
    //define payload from the param
    temp->payload = payload;
    //node is essentially the new end node
    temp->next = nullptr;
    return temp;
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        if (head == nullptr) { //one time case for leading name
            head = newNode(name); // initialize head specially
            prev = head;
        } else {
            prev->next = newNode(name); //the "next" of the node prev to newnode becomes newnode
            prev = prev->next; //the previous of the newnode becomes the next of the node prior to it
        }
    }

    if (prev != nullptr) {
        //if after exiting the loop there exists more than 0 players, link the end player to the first player
        prev->next = head; // make circular
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next; //iterate
        if (curr == start) {
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing (aka circular links to self)
        for (int i = 0; i < k; ++i) { // find kth node
            prev = curr; //double pointer iteration
            curr = curr->next;
        }
        prev->next = curr->next; // delete kth node (prior node next leads to currnode next essentially unlinking currnode)
        delete curr;
        curr = prev->next; //set curr to the new next node (next of deleted node, aka ->next of prev)
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1, max; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
        //remove last pointer ensure no memleak
        
    } else {
        cout << "error: null game" << endl;
    }
    delete lastPerson;
    lastPerson = nullptr;
    return 0;
}

