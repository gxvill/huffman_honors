#include <iostream>
#include <vector>
#include "minHeap.hpp"

using namespace std;

// this file is going to hold the function where we take in the 

// we return the root node, and we are given the minHeap

void preOrder(minHeap::Node* root, vector<string> ans, string curr){
	if(root == nullptr){
		return;
	}
	if(root->left == nullptr && root->right == nullptr){
		ans.push_back(curr);
		return;
	}

	preOrder(root->left, ans, curr + "0");
	preOrder(root->right, ans, curr + "1");
}


vector<string> huffman(minHeap heap){

	int len = heap.getSize();

	while(heap.getSize() >= 2){

		// getting the left node
		minHeap::Node* l = heap.peek();
		heap.extractMin();

		// getting the right node
		minHeap::Node* r = heap.peek();
		heap.extractMin();

		minHeap::Node* parent = new minHeap::Node(l->freq + r->freq);
		parent->left = l;
		parent->right = r;

		heap.insert(parent);
	}
	minHeap::Node* root = new minHeap::Node;
	root = heap.peek();
	vector<string> ans;
	preOrder(root, ans, "");
	return ans;
}
