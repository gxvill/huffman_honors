#include <cstdint>
#include <istream>

class BitReader {
private:
    std::istream& in;
    uint8_t buffer;
    int bitsLeft;

public:
    BitReader(std::istream& input)
        : in(input), buffer(0), bitsLeft(0) {}

    // returns 0 or 1, or -1 on EOF/no more bits
    int readBit() {
        if (bitsLeft == 0) {
            char c;
            if (!in.get(c)) {
                return -1; // no more bytes
            }
            buffer = static_cast<uint8_t>(c);
            bitsLeft = 8;
        }

		int bit = 0;
		if(buffer & 0b1000'0000){	// extracts the next bit in buffer
			bit = 1;
		}
		else{
			bit = 0;
		}
        buffer <<= 1;				// left shift on the buffer
        bitsLeft--;					// decreases bits left as we extract
        return bit;
    }
};

