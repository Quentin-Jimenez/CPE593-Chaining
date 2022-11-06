//#include "chain.hh"
#include "rope.cc"
#include "chain.cc"

/*
// read in document and save it out to disk again under a new name
void read_and_write_test(const char filename[], const char file2[]) {

}
	
//read in a document and append size byte chunks of text num_appends times , then return the document
chain appendtest(const char filename[], uint64_t num_appends, uint64_t size) {
}

void inserttest(uint32_t append_size, uint32_t num_appends,
								uint32_t insert_size, uint32_t num_inserts) {

}
*/

int main() {

	const char* str = "Hello, World!!";
    const char* other = "Lewin";

    Rope r(str);
    r.insert(5,other);
    r.print_tree(std::cout);

	/*
	read_and_write_test("mydoc.txt");
	
	// read in 100MB document
	appendtest("mydoc.txt", 1000000); 

	// build 100MB document with 1 million 100 byte appends
	// then do 100MB of insertions
	inserttest(100, 1000000, 100, 1000000);
	*/
}
