SRC = main.cpp

TARGET = main


$(TARGET): $(SRC)
	g++ -std=c++20 $< BitWriter.cpp -o $@

run:
	./$(TARGET)

clean:
	rm -f ./$(TARGET)
	rm -f bin/binary.bin
	rm -f input/input.txt.gz
	rm -f input/input.txt.xz
	rm -f output/output.txt
