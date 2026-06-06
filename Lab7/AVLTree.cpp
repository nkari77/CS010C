#include "AVLTree.h"

using namespace std;

int AVLTree::height(Node* node){
    if (node == NULL){
        return 0;
    }
    //use node height helper to return the node height
    return node->getHeight();
}

Node* AVLTree::rotate(Node* rotateNode, string key, int balance){
    //left2
    if (balance > 1 && key < rotateNode->getLeft()->getKey()){
        return rightRotate(rotateNode);
    }
    //right2
    if (balance < -1 && key > rotateNode->getRight()->getKey()){
        return leftRotate(rotateNode);
    }

    //leftright
    if (balance > 1 && key > rotateNode->getLeft()->getKey()){
        rotateNode->setLeft(leftRotate(rotateNode->getLeft()));
        return rightRotate(rotateNode);
    }
    //rightleft
    if (balance < -1 && key < rotateNode->getRight()->getKey()){
        rotateNode->setRight(rightRotate(rotateNode->getRight()));
        return leftRotate(rotateNode);
    }
    else return nullptr;
}


void AVLTree::printBalanceFactors(Node* node){
    if (node != NULL){
        printBalanceFactors(node->getLeft());
        cout << node->getKey() <<"(" << balanceFactor(node) <<"), ";
        printBalanceFactors(node->getRight());
    }
}

void AVLTree::printBalanceFactors(){
    printBalanceFactors(root);
}
void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->getLeft()){
            visualizeTree(outFS,n->getLeft());
            outFS<<n->getKey() <<" -> " <<n->getLeft()->getKey()<<";"<<endl;    
        }

        if(n->getRight()){
            visualizeTree(outFS,n->getRight());
            outFS<<n->getKey() <<" -> " <<n->getRight()->getKey()<<";"<<endl;    
        }
    }
}

Node* AVLTree::rightRotate(Node* originalMid){
    //store new center as ogmid left
    Node* newCenter = originalMid->getLeft();
    //make ogright the new right
    Node* ogRight = newCenter->getRight();

    //set right of new center to the ogmid
    newCenter->setRight(originalMid);
    //set ogmid left to the right
    originalMid->setLeft(ogRight);

    //adjust heights based on maximum height of left and right subtrees
    originalMid->setHeight(max(height(originalMid->getLeft()), height(originalMid->getRight())) + 1);
    newCenter->setHeight(max(height(newCenter->getLeft()), height(newCenter->getRight())) + 1);

    return newCenter;
}

Node* AVLTree::leftRotate(Node* originalMid){
    //store new center as ogmid right
    Node* newCenter = originalMid->getRight();
    //make ogleft the new left
    Node* ogLeft = newCenter->getLeft();

    //set left of new center to be ogmid
    newCenter->setLeft(originalMid);
    //set ogmid right to the left
    originalMid->setRight(ogLeft);

    //adjust heights based on maximum height of left and right subtrees
    originalMid->setHeight(max(height(originalMid->getLeft()), height(originalMid->getRight())) + 1);
    newCenter->setHeight(max(height(newCenter->getLeft()), height(newCenter->getRight())) + 1);

    return newCenter;
}
Node* AVLTree::insert(Node* node, string key){
    //rotate
    if (node == nullptr){
        return(new Node(key));
    }
    //if key is pre curr key, traverse left
    else if (key < node->getKey()){
        node->setLeft(insert(node->getLeft(), key));
    }
    //if key is post curr key, traverse right
    else if (key > node->getKey()){
        node->setRight(insert(node->getRight(), key));
    }
    else{
        //duplicate case
        return node;
    }

    //check balance if rebalance is required
    int balance = balanceFactor(node);
    Node* unbalancedNode = node;

    //adjust height
    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));
    //rebalance
    if (balance < -1 || balance > 1){
        return rotate(unbalancedNode, key , balance);
    }
    else{
        return node;
    }
}
//recurse help
void AVLTree::insert(const string &key){
    root = insert(root, key);
}

int AVLTree::balanceFactor(Node* node){
    if (node == nullptr){
        return 0;
    }
    //calc balance factor based on heights of children
    return height(node->getLeft()) - height(node->getRight());
}



int AVLTree::maxFinder(int a, int b){
    //simple max finder case for height calcs
    if (a>b){
        return a;
    }else{
        return b;
    }
    
}