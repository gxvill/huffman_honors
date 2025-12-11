#include <cstdlib>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Node.hpp"
#include "BitReader.hpp"

using namespace std;

struct Compare {
    bool operator()(Node* a, Node* b) const {
        return a->freq > b->freq;
    }
};

map<char, int> mapTxt(ifstream& file);
void preOrder(Node* root, map<char,string> &ans, string curr);
Node* huffmanCodes(map<char,int> res);
void writeMap(map<char, string> codes, ofstream outFile);
map<string,char> readMap(ifstream& binFile);
void decodeWithMap(BitReader& br, const std::map<std::string, char>& codeToChar, std::ostream& out, std::size_t originalSize);
long long getFileSizeInBytes(const std::string& filename);


map<char, int> mapTxt(ifstream& file){
	std::map<char, int> dict;
	char ch;

	if(!file.is_open()){
		std::cerr << "error opening the file" << std::endl;
		return dict;
	}

	// problem: after getting the char from the txt file, how do we add/update the map?
	// this function needs to use the input char ch and add it to the map   
	// if it is already in the map, it needs to update the value of the key
	int fileCount = 0;
	while(file.get(ch)){
		++dict[ch];
		fileCount++;
	}
	// range based loop to print out results:
	// file->close();
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

void writeMap(map<char, string> codes, string fileName){

	// if(!outFile.is_open()){
	// 	cerr << "outfile couldn't be opened" << endl; 
	// }	
	ofstream outFile(fileName, ios::binary | ios::app );
	int mapSize = codes.size();
	outFile.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

	for(const auto pair : codes){
		const char key = pair.first;
		const string code = pair.second;
		outFile.write(reinterpret_cast<const char*> (&key), sizeof(key));
		// write the freqency of the char 
		// (first testing this, then will change to the binary code represetation?
		outFile.write(reinterpret_cast<const char*> (&code), sizeof(code));
	}
	outFile.close();
}

map<string,char> readMap(ifstream& binFile){

	map<string, char> outMap;
	//ifstream inFile(fileName, ios::in | ios::binary);

	int outSize = 0;

	binFile.read(reinterpret_cast<char*>(&outSize), sizeof(outSize));
	for(int i = 0; i < outSize; i++){
		char c;
		string code;
		binFile.read(reinterpret_cast<char*>(&c),sizeof(c));
		binFile.read(reinterpret_cast<char*>(&code),sizeof(code));
		outMap[code] = c;
	}
	//binFile.close();
	return outMap;
}

void decodeWithMap(BitReader& br, const std::map<std::string, char>& codeToChar, std::ostream& out, std::size_t originalSize){
	std::size_t decodedCount = 0;
	std::string currentCode;
	currentCode.reserve(64); // just to avoid frequent reallocs

	while (decodedCount < originalSize) {
		int bit = br.readBit();
		if (bit == -1) {
			// Ran out of bits unexpectedly
			break;
		}

		currentCode.push_back(bit ? '1' : '0');
		//cout << bit;

		auto it = codeToChar.find(currentCode);
		if (it != codeToChar.end()) {
			// Found a complete code
			char ch = it->second;
			out.put(ch);
			decodedCount++;

			currentCode.clear(); // start fresh for the next symbol
		}
	}
}
long long getFileSizeInBytes(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1; // Indicate an error
    }
    long long size = file.tellg(); // Get current position (which is at the end due to ios::ate)
    file.close();
    return size;
}


// not used
void encode(map<char,string> codes, ifstream* text, ofstream* encoded);
void decode(Node* root, ifstream* encoded, ofstream* decoded);

// taking in the map as well as the ifsteam* of the original file
// output will be an output.txt file for now
void encode(map<char,string> codes, ifstream* text, ofstream* encoded){
	if(!text->is_open()){
		cerr << "error opening the input file" << endl;
	}
	if(!encoded->is_open()){
		cerr << "error opening the output file" << endl;
	}

	char ch;
	int bitLen = 0;
	while(text->get(ch)){
		if(codes.count(ch)){
			bitLen += codes.at(ch).length();
			*encoded << codes.at(ch);
		}
	}
	encoded->close();
	text->close();
}

void decode(Node* root, ifstream* encoded, ofstream* decoded){
	if(!encoded->is_open()){
		cerr << "error opening the input file" << endl;
	}
	if(!decoded->is_open()){
		cerr << "error opening the output file" << endl;
	}

	char ch;
	Node* treePtr = root;

	int printed = 0;

	while(encoded->get(ch)){
		if(ch == '0'){
			treePtr = treePtr->left; 	// 0 signifies moving left
		}
		else{
			treePtr = treePtr->right;	// 1 signifies moving right
		}
		if(treePtr->left == nullptr && treePtr->right == nullptr){ //when we have reached a leaf node
			*decoded << treePtr->c; 	// print the char to the "decodedFile"
			treePtr = root; 			// reset the ptr back to the root
			printed ++;
		}
	}

	decoded->close();
	encoded->close();
}
