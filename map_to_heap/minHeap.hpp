#ifndef MINHEAP_HPP
#define MINHEAP_HPP
#include <cstdlib>
#include <vector>


// class for the min heap
class minHeap{
protected:
public:
	struct Node{
		int freq;
		char c;
		Node* left;
		Node* right;
		Node() : freq(0), c('\0'), left(nullptr), right(nullptr) {}
		Node(int f) : freq(f), c('\0'), left(nullptr), right(nullptr) {}
		Node(int f, char a) : freq(f), c(a), left(nullptr), right(nullptr) {}
		Node(int f, char a, Node* r) : freq(f), c(a), left(nullptr), right(r) {}
		Node(int f, char a, Node* r, Node* l) : freq(f), c(a), left(l), right(r) {}
	};
	std::vector<Node*> array;
	int size;
	int capacity;
	minHeap(); 								// default constructor
	minHeap(int);							// create a heap of given size
	~minHeap();								// destructor
	int getSize();							// returns number of heap elements
	void heapify(int);						// makes sure its min heap at certain index
	// might want to change this function to take in a map
	void build(const std::vector<Node*>&);	// builds the heap given a vector of nodes
	void clear();
	void insert(Node*);						// inserts a node into the map
	void push(); 							// inserts w/o heapify
	void remove(Node*);						// removes a node from the map
	Node* peek();						// returns the node at the top
	Node* extractMin();						// returns and removes top node
	void printHeap()const;					// prints the current heap in vector order
private:

};
#endif
