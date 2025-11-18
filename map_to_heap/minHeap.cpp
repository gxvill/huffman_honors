#include <vector>
#include <iostream>
#include <stdexcept> 
#include "minHeap.hpp"


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
	clear();
}
void minHeap::clear(){
	for(auto n : array){
		delete n;
	}
	size = 0;
	capacity = 0;
	array.resize(size);
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

	if(right < size && array[right]->freq < array[smallest]->freq)
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

minHeap::Node* minHeap::extractMin(){

	if(size == 0){					// if empty return -1
		return nullptr;
	}
	if(size == 1){					// if ther is only 1 element return i 0
		size--;
		Node* root = new Node;
		root = array[0];
		return root;
	}

	Node* root = new Node;
	root = array[0];				// store the current root
	array[0] = array[size - 1];		// last elem goes to front
	size--;							// decrement size (delete last elem)

	heapify(0); 					// heapify on the root
	return root;
}

minHeap::Node* minHeap::peek(){

	return nullptr;
}

void minHeap::printHeap() const{
	for (int i = 0; i < size; ++i){
		std::cout << array[i]->c << " ";
	}
	std::cout << std::endl;
}
