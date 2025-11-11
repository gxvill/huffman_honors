// the goal of this file is to make a map of the input characters from the input file
#include <fstream>
#include <iostream>
#include <map>
#include "map.cpp"
using namespace std;


int main(){

    ifstream* inputFilePtr = new ifstream("map.txt"); 

    map<char,int> res = mapTxt(inputFilePtr);

	for(auto m : res){
		cout << "The char is: " <<  m.first << " The frequency is: " << m.second << endl;
	}

    return 0;
}
