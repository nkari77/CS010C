#include "arithmeticExpression.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    int height = 0;
    visualizeTree(outFS,root, height);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

arithmeticExpression::arithmeticExpression(const string &expression)
:infixExpression(expression) , root(nullptr){}

arithmeticExpression::~arithmeticExpression(){
    destroyTree(root);
}

void arithmeticExpression::destroyTree(TreeNode* root){
    if (!root){
        return;
    }
    //recursively destruct left subtree
    destroyTree(root->left);
    //recursively destruct right subtree
    destroyTree(root->right);
    //finally, dealloc root
    delete root;
}
bool arithmeticExpression::isOperator(char c) const{
    //check if the input is an operator, else return false
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){
        return true;
    }
    else{
        return false;
    }
}
void arithmeticExpression::buildTree(){
    //create postFixExpression and stack to store elements
    string postFixExp = infix_to_postfix();
    stack<TreeNode*> expStack;

    for(unsigned int i = 0 ; i < postFixExp.size() ; ++i){
        //if the element is an operator, pop two make those nodes the lhs and rhs of the op node
        if (isOperator(postFixExp.at(i))){
            TreeNode* newNode = new TreeNode(postFixExp.at(i),postFixExp.at(i));
            
            //rhs operand
            newNode->right = expStack.top();
            expStack.pop();

            //lhs operand
            newNode->left = expStack.top();
            expStack.pop();

            //push new node to stack
            expStack.push(newNode);
        }
        else {
            //operand push
            TreeNode* pushOp = new TreeNode(postFixExp.at(i),postFixExp.at(i));
            expStack.push(pushOp);
        }
    }
    //new root is the top of the expression stack
    root = expStack.top();
}

void arithmeticExpression::prefix() const{
    prefix(root);
}

void arithmeticExpression::prefix(TreeNode* root) const{
    //edge, root empty
    if(!root){
        return;
    }   

    //print value of the node
    cout << root->data;

    //left child print
    prefix(root->left);

    //right child print
    prefix(root->right);
}


void arithmeticExpression::infix() const{
    infix(root);
}

void arithmeticExpression::infix(TreeNode* root) const{
    //edge, root empty
    if(!root){
        return;
    }   

    bool needParentheses = false;


    //if root is an operator and one child is an operator, use parantheses
    if (isOperator(root->data) && (root->left || root->right)) {
        needParentheses = true;
    }   
    //if root (which is operator) does not have both left and right child, throw exception
    else if(isOperator(root->data) && !(root->left && root->right)) {
        throw runtime_error("Operator requires two operands");
    }

    //opening before op
    if (needParentheses){
        cout << '(';
    } 
    infix(root->left);

    cout << root->data;

    infix(root->right);
    //closing after op
    if (needParentheses){
        cout << ')';
    }
    
}

void arithmeticExpression::postfix() const{
    postfix(root);
}

void arithmeticExpression::postfix(TreeNode* root) const{
    //base, root empty 
    if(!root){
        return;
    }
    //left child print
    postfix(root->left);

    //right child print
    postfix(root->right);

    //print node data
    cout << root->data;
}

const string& arithmeticExpression::getExpression() const {
      return infixExpression;
}

int arithmeticExpression::visualizeTree(ofstream& out, TreeNode* root, int& height) const {
    //ending case
    if (!root) {
        return -1;
    }
    
    int currNode = height;

    out << "h" << currNode << " [color = lightblue, style = filled, label=\"" << root->key << "\"];" << endl;

    if (root->left) {
        int leftNode = ++height;
        out << "h" << currNode << " -> h" << leftNode << ";" << endl;
        visualizeTree(out, root->left, height);
    }

    if (root->right) {
        int rightNode = ++height;
        out << "h" << currNode << " -> h" << rightNode << ";" << endl;
        visualizeTree(out, root->right, height);
    }

    return currNode;
}