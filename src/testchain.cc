//#include "util/benchmark.hh"
#include <fstream>
#include <iostream>
#include <string>

#include "../include/bst.hh"
#include "../include/chain.hh"
#include "../include/hashing.hh"

using namespace std;

// read in document and save it out to disk again under a new name
void read_and_write_test(const char filename[], const char file2[]) {
  string fileString;
  ifstream testDocFile(filename);
  ofstream outputFile(file2);

  while (testDocFile.is_open()) {
    testDocFile >> fileString;
  }

  if (outputFile.is_open()) {
    // outputFile << TODO:: write what is needed to file
  }

  testDocFile.close();
  outputFile.close();  // Close file
}

// read in a document and append size byte chunks of text num_appends times ,
// then return the document
void appendtest(const char filename[], uint64_t num_appends, uint64_t size) {
  ifstream testDocFile(filename);

  while (testDocFile.is_open()) {
    // TODO:: append
  }

  testDocFile.close();
}

void inserttest(uint32_t append_size, uint32_t num_appends,
                uint32_t insert_size, uint32_t num_inserts) {}

void testHashing() {
  hashing h;
  const char* str = "Teststring";
  uint64_t hash1 = h.hash64bit(str);
  cout << "64 bit hash key is : " << hash1 << '\n';
  unsigned long hash2 = h.hash32bit(str);
  cout << "32 bit hash key is : " << hash2 << '\n';
}

int main() {
  const char* str = "Hello, World!!";
  const char* other = "What's up?";
  const char* another = "Lets go to LaLaLand.";

  // Test Hashing functions
  // testHashing();

  int minDegree = 3;  // TODO:: Determine best mindegree
  Chain chain(minDegree);

  int a = 0;
  //cin >> a;
  
  chain.insert(0, str);
  chain.insert(1, other);
  chain.insert(2, another);
  chain.printTree();

  for (int i = 1; i < 100; i = i + 3) {
    chain.insert(i, str);
    chain.insert(i + 1, other);
    chain.insert(i + 2, another);
  }

  // cout << "Traversal of the constructed tree is ";
  // chain.traverseTree();
  // chain.insert(0, str);
  // chain.insert(1, other);
  // chain.insert(2, another);

  // chain.insert(10, str);
  // chain.insert(20, other);
  // chain.insert(5, another);
  // chain.insert(6, str);
  // chain.insert(12, other);
  // chain.insert(30, another);
  // chain.insert(17, str);
  // chain.insert(13, other);
  // chain.insert(7, another);
  // chain.traverseTree();

/*
  for(int i=0;i<20; i++){
    cout << i << '\n';
    chain.insert(i, str);
  }
*/
  //chain.printTree();

  //   Rope r(str);
  //  r.insert(5,other);
  // r.print_tree(std::cout);

  //	read_and_write_test("testdoc.txt", "chainResult.txt");

  // read in 100MB document
  //	appendtest("testDoc.txt", 1000000);

  // build 100MB document with 1 million 100 byte appends
  // then do 100MB of insertions
  //	insertTest(100, 1000000, 100, 1000000);
  return 0;
}
