//#include "util/benchmark.hh"
#include <fstream>
#include <string>
#include <iostream>
#include "../include/chain.hh"
#include "../include/bst.hh"

using namespace std;

// read in document and save it out to disk again under a new name
void read_and_write_test(const char filename[], const char file2[]) {

    string fileString;
    ifstream testDocFile (filename);
    ofstream outputFile (file2);

    while(testDocFile.is_open()) 
    {
        testDocFile >> fileString;
    }

    if(outputFile.is_open())
    {
        //outputFile << TODO:: write what is needed to file
    }

    testDocFile.close();
    outputFile.close(); //Close file

}
	
//read in a document and append size byte chunks of text num_appends times , then return the document
chain appendtest(const char filename[], uint64_t num_appends, uint64_t size) {
    ifstream testDocFile (filename);

    while(testDocFile.is_open())
    {
        //TODO:: append
    }

    testDocFile.close();
}


void inserttest(uint32_t append_size, uint32_t num_appends,
								uint32_t insert_size, uint32_t num_inserts) {

}

int main() {
	const char* str = "Hello, World!!";
    const char* other = "Lewin";

    avl_tree avl;
    avl.insert(node ,"hello");

    Rope r(str);
    r.insert(5,other);
    r.print_tree(std::cout);

	read_and_write_test("testdoc.txt", "chainResult.txt");
	
	// read in 100MB document
	appendtest("testDoc.txt", 1000000); 

	// build 100MB document with 1 million 100 byte appends
	// then do 100MB of insertions
	insertTest(100, 1000000, 100, 1000000);
}