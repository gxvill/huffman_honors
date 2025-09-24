// the goal of this file is to make a map of the input characters from the input file

#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){

    std::map<char, int> dict;

    std::ifstream input;
    char ch;

    input.open("map.txt");

    if(!input.is_open()){
        std::cerr << "error opening the file" << std::endl;
        return 1;
    }

    // problem: after getting the char from the txt file, how do we add/update the map?
    // this function needs to use the input char ch and add it to the map   
    // if it is already in the map, it needs to update the value of the key
    while(input.get(ch)){
        ++dict[ch];
    }

    // range based loop to print out results:
    int count;
    for(auto &k : dict){
        cout << k.first << " : " << k.second << endl;
        count++;
    }

    cout << "total number of keys: " << count << endl;

    input.close();


    return 0;
}