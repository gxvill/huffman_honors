#include <cstdlib>
#include <filesystem>
#include <chrono>
#include "funcs.cpp"
#include "BitWriter.hpp"

using namespace std;

int main(){

	cout << "Welcome to the file compressor!\n";
	cout << "Please type in the name of the file you would like to compress (make sure the file is in the input/ folder): ";
	string select =  ""; // this is the target file
	string inPath = "input/";
	bool flag = true;
	string filePath = inPath + select; // this is the target file
	filesystem::path p(filePath);
	do{

		if(flag == false){
			cout << "that file doesn't exist in folder 'input', try again: ";
		}
		getline(cin, select);
		p = inPath + select;
		if(!exists(p)){
			flag = false;
		}
		else flag = true;
	}while(!flag);
	filePath = inPath + select; // this is the target file
	p = filePath;

	string outPath = "output/";

	string fileNameStem = p.stem().string();
	string extension = p.extension().string();
	string encoded = outPath + fileNameStem + "_encoded.txt"; // this is the target file
	string decoded = outPath + fileNameStem + "_decoded" + extension; // this is the target file
	
	/*
	cout << "\nThe stem name of the file is: " << fileNameStem << endl;
	cout << "The file extention of the target file is: " << extension << endl;
	cout << "The full file name is: " << fileNameStem + extension << endl << endl;
	*/

	auto startComp = chrono::high_resolution_clock::now();

	// taking in a text file, maping the frequencies of the chars
    ifstream inputFilePtr = ifstream(filePath); 
    map<char,int> res = mapTxt(inputFilePtr);
	int count = 0;
	for(auto m : res){
		count += m.second;
	}
	cout << "total characters: " << count << endl;

	Node* root = huffmanCodes(res);
	map<char,string> ans;
	preOrder(root, ans, "");

	/*
	for(auto a : ans){
		cout << a.first << ":" << "1" +  a.second << "->"<< stoi("1" + a.second,nullptr,2) << endl;
	}
	*/

	cout << endl;
	writeMap(ans, "bin/binary.bin");
	ofstream outFile("bin/binary.bin", ios::binary | ios::app);

	BitWriter bw(outFile);
	char ch;
	size_t originalSize = 0;

    ifstream testFile = ifstream(filePath); 
	while(testFile.get(ch)){
		bw.writeBits(ans[ch]);
		originalSize++;
	}
	bw.flush();
	outFile.close();
	
	// [ ] test run by going through the text file and writing all the codes into another text file.
	// cout << "\ncharacters in the tree: " << root->freq << endl;
	
    // ifstream* input = new ifstream(filePath); 
	// ofstream* encodedFile = new ofstream(encoded);
	// encode(ans, input, encodedFile);
	// encodedFile->close();

	auto endComp = chrono::high_resolution_clock::now();
	chrono::duration<double> durationComp = endComp - startComp;

	// ofstream* decodedFile = new ofstream(decoded);
	// ifstream* encodedFileOpen = new ifstream(encoded);
	
	// auto startDeco = chrono::high_resolution_clock::now();
	// decode(root, encodedFileOpen, decodedFile);

	ifstream inFile("bin/binary.bin", ios::binary);
	if(!inFile.is_open()){
		cerr << "binary file to read couldn't be opened" << endl; 
	}	
	ofstream outputFile("output/output.txt");
	BitReader br(inFile);
	map<string,char> decodeMap = readMap(inFile);
	cout << "original char size: " << originalSize << endl;
	decodeWithMap(br, decodeMap, outputFile, originalSize);

	outputFile.flush();
	outputFile.close();

	//auto endDeco = chrono::high_resolution_clock::now();
	//chrono::duration<double> durationDeco = endDeco - startDeco;

	long long binLen = getFileSizeInBytes("bin/binary.bin");


	// -- COMPARE COMPRESSION --

	system("gzip -k input/input.txt");
	system("xz -k input/input.txt");

	filesystem::path  fileIn = filePath;
	std::uintmax_t fileSize = std::filesystem::file_size(fileIn);
	filesystem::path  gzipFile = filePath + ".gz";
	std::uintmax_t gFileSize = std::filesystem::file_size(gzipFile);
	filesystem::path  xzFile = filePath + ".xz";
	std::uintmax_t xzFileSize = std::filesystem::file_size(xzFile);

	//cout << "\nCompression time: \t" << durationComp.count() << endl;
	//cout << "Decompression time: \t" << durationDeco.count() << endl;

	cout << "file path: " << fileIn << endl;
	cout << "original file byte size: " << fileSize << endl;
	cout << "byte size of binary file: " << binLen << endl;
	cout << "byte size of gzip file: " << gFileSize << endl;
	cout << "byte size of xz file: " << gFileSize << endl;

	// -- UNIT TEST INPUT AND OUTPUT FILES

	cout << endl << "unit tests:" << endl;
	cout << "matching files: " << endl;

	uintmax_t inputSize = filesystem::file_size("input/input.txt");
	uintmax_t outputSize = filesystem::file_size("output/output.txt");

	if (inputSize != outputSize) {
		cout << "files differ in length" << endl;
		cout << "input file size: " << inputSize << endl;
		cout << "output file size: " << outputSize << endl;
	}
	else{
		cout << "input length matches output length" << endl;
	}

	return 0;
}
