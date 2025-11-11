#include <cstdlib>
#include <map>
#include <queue>
#include <string>

using namespace std;

struct Node{
    int val;
    char c;
    Node *left;
    Node *right;
};

// our goal is to create a min heap of the data which acts as our priority queue
Node* mapToHeap(map<char,int> m){

    priority_queue<Node> min_heap;


    //iterates through each key value pair in the given map m
    
    for (const auto& pair : m){
        Node* new = 
    }
}



