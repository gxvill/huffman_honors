// this folder is where I will combine both the map and heap to create the priority queue for the nodes in order to start the build of the binary tree
//
#include <cstdlib>
#include "map.cpp"
#include "minHeap.hpp"

struct Node{
	int freq;
	char c;
	Node* left;
	Node* right;
	Node(int f) : freq(0), c('\0'), left(nullptr), right(nullptr) {}
	Node(int f, char a) : freq(0), c(a), left(nullptr), right(nullptr) {}
	Node(int f, char a, Node* l) : freq(0), c(a), left(l), right(nullptr) {}
	Node(int f, char a, Node* l, Node* r) : freq(0), c(a), left(l), right(r) {}
};

int main(){

    ifstream* inputFilePtr = new ifstream("map.txt"); 

    map<char,int> res = mapTxt(inputFilePtr);

	for(auto m : res){
		cout << "The char is: " <<  m.first << " The frequency is: " << m.second << endl;
	}



	return 0;
};

