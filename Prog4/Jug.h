#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct Vertex{
    //list of int pairs to denote neighbors
    list<pair<int,int>> neighbors;

    int jugA;
    int jugB;
    int distance;
    string decision;
    Vertex* prev;

    //vertex constructor
    Vertex();
    //vertex destructor
    ~Vertex();
};
class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
    
        int Ca; //a cap
        int Cb; //b cap
        int N; //goal
        int cfA; //fill cost a
        int cfB; //fill cost b
        int ceA; //empty cost a
        int ceB; //empty cost b
        int cpAB; //pour cost a -> b
        int cpBA; //pour cost b -> a
        void makeGraph(Vertex *);
        bool valid(); //check op cost for validity
        void reset(vector<Vertex*> vertices);
        vector<Vertex*> vertices; //determine op possitibilites
        vector<string> paths; //determined op path
};