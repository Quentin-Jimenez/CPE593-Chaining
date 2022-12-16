#include <string.h>

#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

class hashing {
 private:
 public:
  // Murmur hash: Austin Appleby
  uint64_t hash64bit(const string &str) const {
    const void *key = str.c_str();
    int len = str.size();
    int seed = 31;
    const uint64_t m = (0xc6a4a7935bd1e995);
    const int r = 47;
    uint64_t h = seed ^ (len * m);
    const uint64_t *data = (const uint64_t *)key;
    const uint64_t *end = data + (len / 8);
    while (data != end) {
      uint64_t k = *data++;
      k *= m;
      k ^= k >> r;
      k *= m;
      h ^= k;
      h *= m;
    }
    const unsigned char *data2 = (const unsigned char *)data;
    switch (len & 7) {
      case 7:
        h ^= ((uint64_t)data2[6]) << 48;
      case 6:
        h ^= ((uint64_t)data2[5]) << 40;
      case 5:
        h ^= ((uint64_t)data2[4]) << 32;
      case 4:
        h ^= ((uint64_t)data2[3]) << 24;
      case 3:
        h ^= ((uint64_t)data2[2]) << 16;
      case 2:
        h ^= ((uint64_t)data2[1]) << 8;
      case 1:
        h ^= ((uint64_t)data2[0]);
        h *= m;
    };
    h ^= h >> r;
    h *= m;
    h ^= h >> r;
    return h;
  }

  // DJB2 Hash: Dan Bernstein
  unsigned long hash32bit(const string &str) const {
    unsigned long hash = 5381;
    unsigned int size = str.length();
    unsigned int i = 0;
    for (i = 0; i < size; i++) {
      hash = ((hash << 5) + hash) + (str[i]); /* hash * 33 + c */
    }
    return hash;
  }
};