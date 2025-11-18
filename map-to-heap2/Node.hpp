#ifndef NODE_HPP
#define NODE_HPP

#include <cstdlib>

using namespace std;

class Node{
public:
	int freq;
	char c;
	Node *left, *right;
	Node(int f){
		freq = f;
		c = '\0';
		left = nullptr;
		right = nullptr;
	}
	Node(int f, char c){
		freq = f;
		this->c = c;
		left = nullptr;
		right = nullptr;
	}
	Node(int f, char c, Node* l, Node* r){
		freq = f;
		this->c = c;
		left = l;
		right = r;
	}
};

#endif 
