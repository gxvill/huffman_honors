#pragma once

#include <cstdlib>
#include <vector>


// class for the min heap
template <typename T>
class minHeap{
private:
	std::vector<T> array;
	int size;
	int capacity;

public:
	minHeap();
	minHeap(int);
	~minHeap();
	int getSize();
	void heapify(int);
	void build(const std::vector<T>&);
	void insert(T);
	void remove(T&);
	const T& peek();
	T extractMin();
	void printHeap()const;
};

#include "minHeap.tpp"
