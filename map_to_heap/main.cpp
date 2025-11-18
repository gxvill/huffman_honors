// this folder is where I will combine both the map and heap to create the priority queue for the nodes in order to start the build of the binary tree
//
#include <cstdlib>
#include <map>
#include <fstream>
#include <iostream>
#include "minHeap.hpp"
#include "huffman.cpp"

using namespace std;

std::map<char, int> mapTxt(std::ifstream*);

int main(){

    ifstream* inputFilePtr = new ifstream("map.txt"); 
    map<char,int> res = mapTxt(inputFilePtr);
	// map test
	cout << "original map from file\n";
	for(auto m : res){
		cout <<  m.first << ":" << m.second << "\t";
	}
	cout << endl;

	// create the baseline vector for the heap to use
	vector<minHeap::Node*> nodes;
	int len = res.size();
	for(auto m : res){
		minHeap::Node* n = new minHeap::Node(m.second, m.first);
		nodes.push_back(n);
	}

	cout << "\nprinting from map->vector of same freq and characters\n";
	for(auto n : nodes){
		cout << n->c << ":" << n->freq << "\t";
	}
	cout << endl;

	minHeap heap;

	cout << "\ncapacity of new heap: " << heap.capacity << endl;
	heap.build(nodes);
	cout << "looking at heap.build(vec)\n";
	cout << "char:freq\t";
	for(auto n : heap.array){
		cout << n->c << ":" << n->freq << "\t";
	}
	cout << endl;

	cout << "testing the extractMin function on the heap\n";

	cout << "extracted nodes: \n";
	minHeap::Node* n = new minHeap::Node;
	n = heap.extractMin();
	/*
	while(heap.getSize() > 0){
		minHeap::Node* n = heap.extractMin();
		cout << n->c << ":" << n->freq << "\t";
	}
	*/

	// create the heap by building it based on the given vector

	// now the heap should have all the elements of the vector (which came from the map)
	

	// testing if the heap exists:

	return 0;
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
    cout << "total number of keys: " << count << endl;

    return dict;
}
