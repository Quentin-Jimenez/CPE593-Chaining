# compiler for C++
CXX := g++

# -g for debugging format
# -Wall for compiler warnings
CFLAGS := -g -Wall

# Includes
INC := include/

OBJECTS := testchain.o

default: testchain 

testchain: $(OBJECTS) 
	$(CXX) $(OBJECTS) -o testchain  

testchain.o: src/testchain.cc
	$(CXX) $(INC) $(CFLAGS) -c src/testchain.cc -o testchain.o

clean:
	rm -rf testchain.o testchain.exe make.out
