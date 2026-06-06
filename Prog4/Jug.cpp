#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <queue>
#include <list>
#include <stack>
#include "Jug.h"
using namespace std;

Vertex::Vertex() //init empty jugs and arbitrary distance
: jugA(0),jugB(0),distance(9999),decision(""),prev(0){}
Vertex::~Vertex(){
    //empty neighbors list
    neighbors.clear();

}
Jug::Jug(int aCap, int bCap, int goal, int aFillCost, int bFillCost, int aEmptyCost, int bEmptyCost, int aTobPour, int bToaPour)
: Ca(aCap), Cb(bCap), N(goal), cfA(aFillCost), cfB(bFillCost), ceA(aEmptyCost), ceB(bEmptyCost), cpAB(aTobPour), cpBA(bToaPour){
    //check validity before push
    if (valid() == false){
        return;
    }
    //push to paths vec
    paths.push_back("fill A");
    paths.push_back("fill B");
    paths.push_back("empty A");
    paths.push_back("empty B");
    paths.push_back("pour A B");
    paths.push_back("pout B A");

    //create point of new vertex, using origin
    Vertex *origin = new Vertex();
    vertices.push_back(origin);
    makeGraph(origin);
}

void Jug::makeGraph(Vertex *vert){
    //iterate through paths options
    for (unsigned i = 0; i < paths.size(); ++i){
        //create new vert
        Vertex *newVert = 0;
        int cost;
        if (i == 0 && vert->jugA < Ca){ //determine jug A fill possibility
            newVert = new Vertex(); //create new vertex, with filled attributes and new jug quants
            newVert->jugA = Ca;
            newVert->jugB = vert->jugB;
            newVert->decision = paths.at(i); //link new vert decision to current path
            cost = cfA; //cost gets assigned as passed
        }

        else if (i == 1 && vert->jugB < Cb){ //determine jug B fill possibility
            newVert = new Vertex(); //create new vertex, with filled attributes and new jug quants
            newVert->jugA = vert->jugA;
            newVert->jugB = Cb;
            newVert->decision = paths.at(i); //link new vert decision to current path
            cost = cfB; //cost gets assigned as passed
        }
        else if (i == 2 && vert->jugA > 0){ //determine jug A empty possibility
            newVert = new Vertex(); //create empty A, same B vertex
            newVert->jugA = 0;
            newVert->jugB = vert->jugB;
            newVert->decision = paths.at(i); //link new vert decision to current path
            cost = ceA;
        }
        else if (i == 3 && vert->jugB > 0){ ////determine jug B empty possibility
            newVert = new Vertex(); //create empty B, same A vertex
            newVert->jugB = 0;
            newVert->jugA = vert->jugA;
            newVert->decision = paths.at(i); //link new vert decision to current path
            cost = ceB;
        }
        else if (i == 4 && vert->jugB < Cb && vert->jugA > 0){ //pour A into B
            newVert = new Vertex(); //new vert with copied jug caps
            newVert->jugA = vert->jugA;
            newVert->jugB = vert->jugB;
            while (newVert->jugB < Cb && newVert->jugA > 0){ //while capacity exists in A jug, keep pouring into B
                newVert->jugB += 1;
                newVert->jugA -= 1;
            }
            newVert->decision = paths.at(i); //link new vert decision to current path
            cost = cpAB; //cost update
        }
        else if (i == 5 && vert->jugA < Ca && vert->jugB > 0){ //pour B into A
            newVert = new Vertex(); //new vert with copied jug caps
            newVert->jugB = vert->jugB;
            newVert->jugA = vert->jugA;
            while (newVert->jugA < Ca && newVert->jugB > 0){ //while capacity exists in B jug, keep pouring into A
                newVert->jugB -= 1;
                newVert->jugA += 1;
            }
            newVert->decision = paths.at(i); //link new vert decision to current path
            cost = cpBA; //cost update
        }

        if (newVert != 0){ //if new vertex was created, push into vect and udpate neighbor links
            bool duplicate = false;
            for (unsigned j = 0; j < vertices.size(); j++){ //dupe check case
                if (vertices.at(j)->jugA == newVert->jugA && vertices.at(j)->jugB == newVert->jugB){ //check to see if new jug states already exist
                    duplicate = true; //bool update
                }
            }
            if (duplicate != true){ //if newvert is not dupe, find index location for push and append to vect
                vertices.push_back(newVert);
                unsigned index = 0;
                for (unsigned j = 0; j < vertices.size(); j++){
                    if (vertices.at(j) == newVert){
                        index = j;
                    }
                }
                vert->neighbors.push_back(make_pair(index, cost)); //make newvert neighbor of the dupe vert
            }else{ //if dupe: dealloc and set null
                delete newVert; 
                newVert = nullptr;
            }
        }
    }

    //iterate neighbor pairs and create graph vertices at the index of the neighbor pair (val 1)
    for (auto neighbor : vert->neighbors) {
        makeGraph(vertices.at(neighbor.first));
    }
}

Jug::~Jug(){
    //iterate through vertices and dealloc
    for(unsigned int i = 0 ; i < vertices.size(); ++i){
        delete vertices.at(i);
        vertices.at(i) = 0;
    }
}

bool Jug::valid(){
    //check passed costs to determine validity
    //if the capacity of A is not more than 0 and less than or equal to B
    //OR
    //if the goal is not less than the capacity of B and B is not an arbitrarily large capacity (aka goal is unreachable)
    
    if (!(Ca > 0 && Ca <= Cb) || !(Cb >= N && Cb < 1000)){
        return false;
    }
    // Check if the operation costs are non-negative
    if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0){
        return false;
    }

    // If none of the conditions are triggered, the parameters are valid
    return true;
}

int Jug::solve(string &solution){
    //init solution existance to false
    bool exist = false;

    //invalid game autofails
    if (valid() == false){
        //empty out the string
        solution.clear();
        return -1;
    }

    //iteration for solution determination
    for (unsigned int i = 0 ; i < vertices.size() ; ++i){
        //if the goal is reached at index I
        if (vertices.at(i)->jugA == 0 && vertices.at(i)->jugB == N){
            exist = true;
            break;
        }
    }
    if (exist == false){
        solution = "";
        return 0;
    }

    reset(vertices); //reinit all distance and prev values
    //store process queue and already visited vertices
    queue<Vertex*> q;
    vector<Vertex*> visited;

    //push all vertices into queue
    for(unsigned int i = 0; i < vertices.size(); i++){
        q.push(vertices.at(i));
    }

    while (!q.empty()){ // while q contains vertices to be processed
        // take front of queue as curr
        Vertex *curr = q.front();
        // push into visited vector to track processed
        visited.push_back(curr);
        //pop from q
        q.pop();
        //for neighbors of the current vertice
        for (auto &neighbor : curr->neighbors){ //if less costly path is found (start to node rather than curr to node)
            if (vertices.at(neighbor.first)->distance > curr->distance + neighbor.second){
                //update distance 
                vertices.at(neighbor.first)->distance = curr->distance + neighbor.second;
                //set path to neighbor from curr
                vertices.at(neighbor.first)->prev = curr;
            }
        }
    }
    //
    Vertex *goal = 0;
    //iterate through visited vector until goal is reached
    for (unsigned int i = 0; i < visited.size(); i++){
        if (visited.at(i)->jugA == 0 && visited.at(i)->jugB == N){
            goal = visited.at(i);
        }
    }
    Vertex *curr = goal;
    Vertex *before = 0;
    stack<string> s;
    int total = 0;

    while (curr){//sum up all steps until goal is reached
        string proposedSolution = "";
        before = curr->prev;
        //check curr->prev for existance
        if (before){
            //append the next step from curr followed by a newline
            proposedSolution = curr->decision + "\n";
        }
        //add into stack of steps
        s.push(proposedSolution);
        //prev exists
        if (before){
            //move through neighbors
            for (auto &neighbor : before->neighbors){
                //if one of the neighbor pairs has the same jugA and jugB values, it is added into the total (second being the cost)
                if (vertices.at(neighbor.first)->jugA == curr->jugA && vertices.at(neighbor.first)->jugB == curr->jugB){
                    total = total + neighbor.second;
                }
            }
        }
        //reset curr to prev
        curr = before;
    }
    //while the stack contains values
    while (!s.empty()){ //append stack instruction to solution string
        solution = solution + s.top();
        //pop top instruction, so new top is the next in the sequece
        s.pop();
    }
    //append successful solution with the cost
    solution = solution + "success " + to_string(total);

    return 1;
}

void Jug::reset(vector<Vertex*> vertices){
    for (unsigned int i = 0 ; i < vertices.size() ; ++i){
        vertices.at(i)->distance = 9999;
        vertices.at(i)->prev = 0;
    }
    //new base
    vertices.at(0)->distance = 0;
    return;
}