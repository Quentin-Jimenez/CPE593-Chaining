# compiler for C++
CXX := g++

# -g for debugging format
# -Wall for compiler warnings
CFLAGS := -g -Wall

# Includes
INC := inc/

SRC := src/

OBJECTS := chain_main.o chain.o

default: chain_main 

chain_main: $(OBJECTS) 
	$(CXX) $(OBJECTS) -o chain_main  

chain_main.o: $(SRC)/chain_main.cc
	$(CXX) $(INC) $(CFLAGS) -c $(SRC)chain_main.cc -o chain_main.o

chain.o: $(SRC)/chain.cc 
	$(CXX) $(INC) $(CFLAGS) -c $(SRC)chain.cc -o chain.o

 
clean:
	rm -rf chain_main.o chain.o chain_main.exe make.out
