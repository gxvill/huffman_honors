#include <cstdlib>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

map<char,int> mapTxt(ifstream*);



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

