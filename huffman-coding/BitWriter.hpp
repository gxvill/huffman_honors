#include <cstdint>
#include <vector>
#include <ostream>

using namespace std;

class BitWriter {
private:
    std::ostream& out;     // reference to output stream
    uint8_t buffer;        // current byte being filled
    int bitCount;          // number of bits currently stored (0–7)

public:
    BitWriter(std::ostream& output);

    // Write a single bit (0 or 1)
    void writeBit(int bit);

    // Write many bits (like a Huffman code)
    void writeBits(const string& codeString);

    // Flush remaining bits (pad with zeros)
    void flush();

    // Auto-flush when destroyed (RAII)
    ~BitWriter();
};
