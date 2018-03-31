SRC    := symbolmap.cpp map_parser.cpp elf_parser.cpp elf_helper.cpp
TARGET := symbolmap

all: $(TARGET)

symbolmap: $(SRC) 
	g++ -std=c++11 -o $@ $(SRC)

clean:
	rm $(TARGET) 
