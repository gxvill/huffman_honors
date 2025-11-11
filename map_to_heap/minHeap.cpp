#include <vector>
#include <iostream>
#include <stdexcept> 
#include "minHeap.hpp"

struct Node{
	int freq;
	char c;
	Node* left;
	Node* right;
	Node() : freq(0), c('\0'), left(nullptr), right(nullptr) {}
	Node(int f) : freq(0), c('\0'), left(nullptr), right(nullptr) {}
	Node(int f, char a) : freq(0), c(a), left(nullptr), right(nullptr) {}
	Node(int f, char a, Node* r) : freq(0), c(a), left(nullptr), right(r) {}
	Node(int f, char a, Node* r, Node* l) : freq(0), c(a), left(l), right(r) {}
};


minHeap::minHeap(){
	size = 0;
	capacity = 1;
	array.resize(1);
}
minHeap::minHeap(int i){
	size = 0;
	capacity = i;
	array.resize(i);

}
minHeap::~minHeap(){
}
int minHeap::getSize(){
	return size;
}
void minHeap::heapify(int i){
	// rearranges the order of the vector to keep the min heap property
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if(left < size && array[left]->freq < array[smallest]->freq)
		smallest = left;

	if(right < size && array[right] < array[smallest])
		smallest = right;

	if(smallest != i){
		std::swap(array[i], array[smallest]);
		heapify(smallest);
	}
}
void minHeap::build(const std::vector<Node*>& arr){
	// go through the array element by element and calling the heapify function
	// change and update all variables
	capacity = arr.size();
	size = capacity;
	array = arr;

	// heapify the the (n-1)/2 nodes
	for(int i = (size - 1)/2; i >= 0; i--){
		heapify(i);
	}
}
void minHeap::insert(Node* elem){
	if(size == capacity){			// doubling size if full
		capacity *= 2;
		array.resize(capacity);	
	}

	size++;
	array.push_back(elem);
	int i = size - 1;
	array[i] = elem;

	while(i != 0 && array[(i -1)/2] > array[i]){
		std::swap(array[i],array[(i -1)/2]);
		i = (i - 1) / 2;
	}

}
void minHeap::remove(Node* key){
	int index = -1;
	for(int i = 0; i < size; ++i){
		if(array[i]->c == key->c){
			index = i;
			break;
		}
	}

	if(index == -1){					// if the key doens't exist
		std::cout << "key not found" << std::endl;
		return;
	}

	if(index == size - 1){ 				// if it is the last node
		size --;
		return;
	}

	array[index] = array[size -1];		// puts the last elem in index
	size --;							// decrement size (delete last elem)

	heapify(index);						// heapify from the index

	if(size == 0){
		throw std::out_of_range("Key not found");
	}
}

Node* minHeap::extractMin(){

	if(size == 0){					// if empty return -1
		return nullptr;
	}
	if(size == 1){					// if ther is only 1 element return i 0
		size--;
		Node* root = array[0];
		return root;
	}

	Node* root = array[0];				// store the current root
	array[0] = array[size - 1];		// last elem goes to front
	size--;							// decrement size (delete last elem)

	heapify(0); 					// heapify on the root
	return root;
}

Node* minHeap::peek(){

	return nullptr;
}

void minHeap::printHeap() const{
	for (int i = 0; i < size; ++i){
		std::cout << array[i]->c << " ";
	}
	std::cout << std::endl;
}
