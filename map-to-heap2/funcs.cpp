#include <cstdlib>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include "Node.hpp"

using namespace std;


struct Compare {
    bool operator()(Node* a, Node* b) const {
        return a->freq > b->freq;
    }
};


map<char, int> mapTxt(ifstream* file){
	std::map<char, int> dict;
	char ch;

	if(!file->is_open()){
		std::cerr << "error opening the file" << std::endl;
		return dict;
	}

	// problem: after getting the char from the txt file, how do we add/update the map?
	// this function needs to use the input char ch and add it to the map   
	// if it is already in the map, it needs to update the value of the key
	while(file->get(ch)){
		++dict[ch];
	}

	// range based loop to print out results:
	file->close();
	int count = 0;
	count = dict.size();

	return dict;
}

void preOrder(Node* root, map<char,string> &ans, string curr) {
	if (root == nullptr) return;

    // Leaf node represents a character.
	if (root->left == nullptr && root->right==nullptr) {
		ans[root->c] = curr;
		return;
	}

	preOrder(root->left, ans, curr + '0');
	preOrder(root->right, ans, curr + '1');
}

Node* huffmanCodes(map<char,int> res){

	priority_queue<Node*, vector<Node*>, Compare> minHeap;

	// pushing Nodes to the minHeap
	for(auto m : res){
		Node* n = new Node(m.second, m.first);
		minHeap.push(n);
	}

	while(minHeap.size() >= 2){
		Node* l = minHeap.top();
		minHeap.pop();

		Node* r = minHeap.top();
		minHeap.pop();

		Node* parent = new Node(l->freq + r->freq);
		parent->left = l;
		parent->right = r;

		minHeap.push(parent);
	}

	Node* root = minHeap.top();
	return root;
}

// taking in the map as well as the ifsteam* of the original file
// output will be an output.txt file for now
void encode(map<char,string> codes, ifstream* input){
	ofstream binaryText("encoding.txt");
	if(!input->is_open()){
		cerr << "error opening the input file" << endl;
	}
	if(!binaryText.is_open()){
		cerr << "error opening the output file" << endl;
	}

	char ch;

	while(input->get(ch)){
		if(codes.count(ch)){
			binaryText << codes.at(ch);
		}
	}
	binaryText.close();
	input->close();
}

void decode(Node* root, ifstream* input){
	ofstream decodedFile("decoded.txt");
	if(!input->is_open()){
		cerr << "error opening the input file" << endl;
	}
	if(!decodedFile.is_open()){
		cerr << "error opening the output file" << endl;
	}

	char ch;
	Node* treePtr = root;

	int printed = 0;

	while(input->get(ch)){
		if(ch == '0'){
			treePtr = treePtr->left; 	// 0 signifies moving left
		}
		else{
			treePtr = treePtr->right;	// 1 signifies moving right
		}
		if(treePtr->left == nullptr && treePtr->right == nullptr){ //when we have reached a leaf node
			decodedFile << treePtr->c; 	// print the char to the "decodedFile"
			treePtr = root; 			// reset the ptr back to the root
			printed ++;
		}
	}

	decodedFile.close();
	input->close();
}
