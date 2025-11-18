#include <cstdlib>
#include "funcs.cpp"

using namespace std;

int main(){
	// taking in a text file, maping the frequencies of the chars
    ifstream* inputFilePtr = new ifstream("funcs.cpp"); 
    map<char,int> res = mapTxt(inputFilePtr);
	int count = 0;
	for(auto m : res){
		count += m.second;
	}
	cout << "total characters: " << count << endl;
	// map test
	/*
	cout << "original map from file\n";
	for(auto m : res){
		cout <<  m.first << ":" << m.second << "\t";
	}
	cout << endl;
	*/

	// holding the codes of the characters in a map (for simplicity)
	// the map was only used for testing
	// now we are returning the root of the tree since we can get the map from the preOrder function itself.
	Node* root = huffmanCodes(res);
	map<char,string> ans;
	preOrder(root, ans, "");

	// making sure that the codes are mapped properly
	/*
	for(auto n : codes){
		if(n.first == '\n'){
			cout << "\\n" << ":" << n.second << "\n";
		}
		else{
			cout << n.first << ":" << n.second << "\n";
		}
	}
	*/

	// [ ] test run by going through the text file and writing all the codes into another text file.
	cout << "characters in the tree: " << root->freq << endl;
	
    ifstream* input = new ifstream("funcs.cpp"); 
	encode(ans, input);


	ifstream* encode = new ifstream("encoding.txt");
	decode(root, encode);
	


	return 0;
}
