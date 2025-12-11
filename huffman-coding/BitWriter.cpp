#include <cstdint>
#include <vector>
#include <ostream>
#include "BitWriter.hpp"

using namespace std;

BitWriter::BitWriter(std::ostream& output)
	: out(output), buffer(0), bitCount(0) {}

// Write a single bit (0 or 1)
void BitWriter::writeBit(int bit) {
	bit &= 1; // ensure 0 or 1

	// Put the bit in the correct MSB position
	buffer |= (bit << (7 - bitCount));
	bitCount++;

	// If we filled a byte, write it out
	if (bitCount == 8) {
		out.put(static_cast<char>(buffer));
		buffer = 0;
		bitCount = 0;
	}
}

// Write many bits (like a Huffman code)
void BitWriter::writeBits(const string& codeString) {
	for (char c : codeString){
		int bit = c - '0';		// trick to do '0'/'1' -> 0/1
		writeBit(bit);
	}
}

// Flush remaining bits (pad with zeros)
void BitWriter::flush() {
	if (bitCount > 0) {
		out.put(static_cast<char>(buffer));
		buffer = 0;
		bitCount = 0;
	}
}

// Auto-flush when destroyed (RAII)
BitWriter::~BitWriter() {
	flush();
}
