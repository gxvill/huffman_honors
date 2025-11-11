// this is where I will learn the min heap implementation

#include "minHeap.hpp"
#include <random>
#include <cstdlib>

int main(){
	minHeap<int> h(10);
	for(int i = 0; i < 10; i++){
		int c = 1+(rand() % 100);
		h.insert(c);
	}

	while(h.getSize() > 0){
		h.printHeap();
		std::cout << h.extractMin() << std::endl;
	}

	return 0;
}
