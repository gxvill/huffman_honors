// this is gonna be the start of my cs20 honors project


// the first goal is to make this file, a function that takes in a .txt file and creates of map of all the characters

#include <fstream>
#include <iostream>
#include <string>


int main(){

	// creating:
	// - ifstream object
	// - string variable object
	std::ifstream input;
	std::string line;

	// opening the txt file
	input.open("in.txt");

	// checking if the txt file has opened successfully
	// if not, throw an error
	if(!input.is_open()){
		std::cerr << "There was an error opening the file" << std::endl;
		return 1;
	}

	// getting each line from the input file and making it the output
	while (std::getline(input, line)){
		std::cout << "lines from the file " << line << std::endl;
	}

	// the above code all works! except that I need to close the file next time oops

	input.close();


    // now i am going to do the same thing, but read each word at a time

    std::fstream inputWords;
    std::string word;

    inputWords.open("in.txt");

	if(!inputWords.is_open()){
		std::cerr << "There was an error opening the file" << std::endl;
		return 1;
	}

    while(inputWords >> word){
        std::cout << "this should be one word at a time: " << word << "\n";
    }

    inputWords.close();

    // now I am going to do the same thing, but with characters

    std::fstream inChars;
    char chars;

    inChars.open("in.txt");

	if(!inChars.is_open()){
		std::cerr << "There was an error opening the file" << std::endl;
		return 1;
	}

    while(inChars.get(chars)){
        std::cout << "this should be displaying each character in the file: " << chars << "\n";
    }

    inChars.close();

    // finally, now I will make a string containing all the chars in the text
    // then output the string to make sure they copied over correctly

    std::fstream inputChars;
    std::string output;
    char ch;

    inputChars.open("in.txt");

	if(!inputChars.is_open()){
		std::cerr << "There was an error opening the file" << std::endl;
		return 1;
	}

    while(inputChars.get(ch)){
        output += ch;
    }

    inChars.close();

    std::cout << "the following should be a replica of the original text file: \n";
    std::cout << output << std::endl;

	return 0;
}


