#include <iostream>
#include <map>

#include "../mempool.h"

size_t failed = 0;
size_t passed = 0;
size_t ctor = 0;
size_t dtor = 0;
size_t mallocs = 0;
size_t reallocs = 0;
size_t frees = 0;

// test structure for checking that nothing overlaps

// tells me if everything constructed gets destructed
std::map<void *, bool> object_mapping;

// test to be sure of a condition
#define assertEquals(one, two)                                           \
  if (!((one) == (two))) {                                               \
    std::cout << #one << " != " << #two << ", " << #one << " == " << one \
              << ", " << #two << " == " << two << std::endl;             \
    ++failed;                                                            \
  } else {                                                               \
    ++passed;                                                            \
  }
#define assertEqualsO(one, two)                       \
  if (!((one) == (two))) {                            \
    std::cout << #one << " != " << #two << std::endl; \
    ++failed;                                         \
  } else {                                            \
    ++passed;                                         \
  }
#define assertNotEqualsO(one, two)                    \
  if (!((one) != (two))) {                            \
    std::cout << #one << " == " << #two << std::endl; \
    ++failed;                                         \
  } else {                                            \
    ++passed;                                         \
  }
#define assertZero(d) assertEquals(d, 0)
#define echo(x) std::cout << x << std::endl;

#ifdef __GNUC__
#pragma pack(push, 1)
#elif _MSC_VER
#pragma pack(push, testStruct_pack, 1)
#endif
struct testStruct {
 public:
  testStruct(void) {
    // make sure it's not already constructed
    assertEqualsO(object_mapping.find(this), object_mapping.end());
    object_mapping[this] = true;
    ++ctor;
  }
  testStruct(char _c, short _s, int _i, long _l) : c(_c), s(_s), i(_i), l(_l) {
    // make sure it's not already constructed
    assertEqualsO(object_mapping.find(this), object_mapping.end());
    object_mapping[this] = true;
    ++ctor;
  }
  ~testStruct(void) {
    // make sure that it's been constructed
    assertNotEqualsO(object_mapping.find(this), object_mapping.end());
    object_mapping.erase(this);
    ++dtor;
    c = 0;
    s = 0;
    i = 0;
    l = 0;
  }
  char c;
  short s;
  int i;
  long l;

 private:
  testStruct &operator=(const testStruct &other);
  testStruct(const testStruct &other);
};
#ifdef __GNUC__
#pragma pack(pop)
#elif _MSC_VER
#pragma pack(pop, testStruct_pack)
#endif

template <typename T>
static void testMemoryPool(T &pool) {
  testStruct *test = (testStruct *)pool.allocate();
  test->c = 1;
  test->s = 2;
  test->i = 3;
  test->l = 4;

  testStruct *test2 = (testStruct *)pool.allocate();
  test2->c = 21;
  test2->s = 22;
  test2->i = 23;
  test2->l = 24;

  assertEquals(test->c, 1);
  assertEquals(test->s, 2);
  assertEquals(test->i, 3);
  assertEquals(test->l, 4);
  assertEquals(test2->c, 21);
  assertEquals(test2->s, 22);
  assertEquals(test2->i, 23);
  assertEquals(test2->l, 24);

  for (int i = 0; i < 5; ++i) {
    testStruct *mems[15];  // more than what's in the pool
    for (int j = 0; j < 15; ++j) {
      mems[j] = (testStruct *)pool.allocate();
      mems[j]->c = 31;
      mems[j]->s = 32;
      mems[j]->i = 33;
      mems[j]->l = 34;

      assertEquals(test->c, 1);
      assertEquals(test->s, 2);
      assertEquals(test->i, 3);
      assertEquals(test->l, 4);
      assertEquals(test2->c, 21);
      assertEquals(test2->s, 22);
      assertEquals(test2->i, 23);
      assertEquals(test2->l, 24);
    }

    assertEquals(pool.load(), 10);

    for (int j = 0; j < 15; ++j) {
      pool.deallocate(mems[j]);
    }

    assertEquals(pool.load(), 2);
  }
}

// tests the memory_pool object
static void test_memory_pool(bool announce = true) {
  if (announce) {
    std::cout << "Testing Memory Pool" << std::endl;
  }
  memory_pool<sizeof(testStruct), 10> pool;
  testMemoryPool<memory_pool<sizeof(testStruct), 10> >(pool);
}

template <typename T>
static void testObjectPool(T &pool) {
  ctor = 0;
  dtor = 0;

  testStruct *test = new_object(pool, testStruct(1, 2, 3, 4));
  assertEquals(test->c, 1);
  assertEquals(test->s, 2);
  assertEquals(test->i, 3);
  assertEquals(test->l, 4);

  assertEquals(ctor, 1);
  assertEquals(dtor, 0);

  testStruct *test2 = pool.allocate();
  test2->c = 21;
  test2->s = 22;
  test2->i = 23;
  test2->l = 24;

  assertEquals(ctor, 2);
  assertEquals(dtor, 0);

  assertEquals(test->c, 1);
  assertEquals(test->s, 2);
  assertEquals(test->i, 3);
  assertEquals(test->l, 4);
  assertEquals(test2->c, 21);
  assertEquals(test2->s, 22);
  assertEquals(test2->i, 23);
  assertEquals(test2->l, 24);

  for (int i = 0; i < 5; ++i) {
    testStruct *mems[15];  // more than what's in the pool
    for (int j = 0; j < 15; ++j) {
      mems[j] = pool.allocate();
      mems[j]->c = 31;
      mems[j]->s = 32;
      mems[j]->i = 33;
      mems[j]->l = 34;
      // echo(pool.dump());
      assertEquals(test->c, 1);
      assertEquals(test->s, 2);
      assertEquals(test->i, 3);
      assertEquals(test->l, 4);
      assertEquals(test2->c, 21);
      assertEquals(test2->s, 22);
      assertEquals(test2->i, 23);
      assertEquals(test2->l, 24);
    }

    assertEquals(pool.load(), 10);

    for (int j = 0; j < 15; ++j) {
      pool.deallocate(mems[j]);
      // echo(pool.dump());
    }

    assertEquals(pool.load(), 2);
  }

  assertEquals(ctor, 77);
  assertEquals(dtor, 75);
}

// tests the object_memory_pool
static void test_object_memory_pool(void) {
  std::cout << "Testing Object Memory Pool" << std::endl;
  object_memory_pool<testStruct, 10> pool;
  testObjectPool<object_memory_pool<testStruct, 10> >(pool);
}

template <typename T>
static void testBucket3(T &pool) {
#ifdef MEMPOOL_DETERMINE_DISTRIBUTION
  pool.profile_on_delete(50, "pool");  // 50 is the longest string
#endif

  char *buffer = (char *)pool.allocate(20);
  memcpy(buffer, "I am nineteen chars", 20);  // plus a null terminator
  assertZero(strcmp(buffer, "I am nineteen chars"));

  for (int i = 0; i < 5; ++i) {
    char *mems[50];
    for (int j = 0; j < 50; ++j) {
      mems[j] = (char *)pool.allocate(j);
      // just set it to something random
      memcpy(mems[j],
             "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
             "XXXXXXXXXX",
             j);

      assertZero(strcmp(buffer, "I am nineteen chars"));
    }

    assertEquals(pool.load()[0], 5);
    assertEquals(pool.load()[1], 4);
    assertEquals(pool.load()[2], 30);

    for (int j = 0; j < 50; ++j) {
      pool.deallocate(mems[j]);
    }

    assertEquals(pool.load()[0], 0);
    assertEquals(pool.load()[1], 0);
    assertEquals(pool.load()[2], 1);
  }
}

template <typename T>
static void testBucket4(T &pool) {
#ifdef MEMPOOL_DETERMINE_DISTRIBUTION
  pool.profile_on_delete(50, "normal distribution");  // 50 is the max length
#endif

  char *buffer = (char *)pool.allocate(20);
  memcpy(buffer, "I am nineteen chars", 20);  // plus a null terminator
  assertZero(strcmp(buffer, "I am nineteen chars"));

  for (int i = 0; i < 5; ++i) {
    char *mems[50];
    for (int j = 0; j < 50; ++j) {
      // make a normal distribution between 0 and 50
      size_t bytes = rand() % 50;
      bytes += rand() % 50;
      bytes += rand() % 50;
      bytes /= 3;

      mems[j] = (char *)pool.allocate(bytes);
      // just set it to something random
      memcpy(mems[j],
             "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
             "XXXXXXXXXX",
             bytes);

      assertZero(strcmp(buffer, "I am nineteen chars"));
    }

    for (int j = 0; j < 50; ++j) {
      pool.deallocate(mems[j]);
    }

    assertEquals(pool.load()[0], 0);
    assertEquals(pool.load()[1], 0);
    assertEquals(pool.load()[2], 1);
    assertEquals(pool.load()[3], 0);
  }

  pool.deallocate(buffer);
  assertEquals(pool.load()[0], 0);
  assertEquals(pool.load()[1], 0);
  assertEquals(pool.load()[2], 0);
  assertEquals(pool.load()[3], 0);
}

template <typename T>
static void testResizeableBucket4(T &pool) {
#ifdef MEMPOOL_DETERMINE_DISTRIBUTION
  pool.profile_on_delete(50, "normal distribution");  // 50 is the max length
#endif

  char *buffer = (char *)pool.allocate(20);
  memcpy(buffer, "I am nineteen chars", 20);  // plus a null terminator
  assertZero(strcmp(buffer, "I am nineteen chars"));
  buffer = (char *)pool.reallocate(buffer, 25);
  assertZero(strcmp(buffer, "I am nineteen chars"));
  buffer = (char *)pool.reallocate(buffer, 20);
  assertZero(strcmp(buffer, "I am nineteen chars"));

  for (int i = 0; i < 5; ++i) {
    char *mems[50];

    for (int j = 0; j < 50; ++j) {
      // make a normal distribution between 0 and 50
      size_t bytes = rand() % 45;
      bytes += rand() % 45;
      bytes += rand() % 45;
      bytes /= 3;
      bytes += 6;

      mems[j] = (char *)pool.allocate(bytes);
      char *temp = mems[j];
      // just set it to something random
      memcpy(mems[j],
             "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
             "XXXXXXXXXXXXXXX",
             bytes);

      assertZero(strcmp(buffer, "I am nineteen chars"));

      mems[j] = (char *)pool.reallocate(mems[j], bytes);
      assertEquals(temp, mems[j]);  // dont get reallocated, same size
      bytes -= 5;
      mems[j] = (char *)pool.reallocate(mems[j], bytes);
      assertEquals(temp, mems[j]);  // dont get reallocated, smaller
      bytes += 50;
      if (bytes < 65) bytes = 65;  // because the bucket size is 30, then 64
      mems[j] = (char *)pool.reallocate(mems[j], bytes);
      assertNotEqualsO(temp, mems[j]);  // expanded
      assertZero(strcmp(buffer, "I am nineteen chars"));
    }

    for (int j = 0; j < 50; ++j) {
      pool.deallocate(mems[j]);
    }

    assertEquals(pool.load()[0], 0);
    assertEquals(pool.load()[1], 0);
    assertEquals(pool.load()[2], 0);
    assertEquals(pool.load()[3], 1);
  }

  pool.deallocate(buffer);
  assertEquals(pool.load()[0], 0);
  assertEquals(pool.load()[1], 0);
  assertEquals(pool.load()[2], 0);
  assertEquals(pool.load()[3], 0);
}

// tests the bucket_pools
static void test_bucket_pool(void) {
  std::cout << "Testing Bucket Memory Pool" << std::endl;
  {
    bucket_pool_3<4, 10, 8, 10, 64, 30> pool;
    testBucket3<bucket_pool_3<4, 10, 8, 10, 64, 30> >(pool);
  }
  {
    bucket_pool_4<4, 10, 8, 10, 20, 30, 64, 10> pool;
    testBucket4<bucket_pool_4<4, 10, 8, 10, 20, 30, 64, 10> >(pool);
  }

  {
    bucket_pool_4<4, 10, 8, 10, 20, 30, 64, 10> pool;
    testResizeableBucket4<bucket_pool_4<4, 10, 8, 10, 20, 30, 64, 10> >(pool);
  }
}

static void *_malloc(size_t bytes) {
  ++mallocs;
  return malloc(bytes);
}

static void _free(void *ptr) {
  ++frees;
  free(ptr);
}

static void *_realloc(void *ptr, size_t bytes) {
  ++reallocs;
  return realloc(ptr, bytes);
}

static void test_memory_callbacks(void) {
  std::cout << "Testing Callbacks" << std::endl;
  mempool_callbacks::set(_malloc, _realloc, _free);
  test_memory_pool(false);
  assertEquals(mallocs, 1);  // only needed to create another bucket
  assertEquals(frees, 1);
  mempool_callbacks::set(std::malloc, std::realloc, std::free);
}

#define SIZE_OF_POOL 100
#define POOL_LOOPS 1000
#define ALLOCATION_SIZE 50
#define LOAD 5
#define LOAD_INCREMENT 4

static void test_speed() {
  std::cout << "Load, Malloc/Free, Mempool," << std::endl;
  void *mem[SIZE_OF_POOL * LOAD];

  for (size_t malloc_count = 0; malloc_count < SIZE_OF_POOL * LOAD;
       malloc_count += SIZE_OF_POOL / LOAD_INCREMENT) {
    clock_t start = clock();
    for (int i = 0; i < POOL_LOOPS; ++i) {
      for (int j = 0; j < malloc_count; ++j) {
        mem[j] = malloc(ALLOCATION_SIZE);
      }
      for (int j = 0; j < malloc_count; ++j) {
        free(mem[j]);
      }
    }
    std::cout << (float)malloc_count / (float)SIZE_OF_POOL << ", "
              << clock() - start;

    start = clock();
    memory_pool<ALLOCATION_SIZE, SIZE_OF_POOL> pool;
    for (int i = 0; i < POOL_LOOPS; ++i) {
      for (int j = 0; j < malloc_count; ++j) {
        mem[j] = pool.allocate();
      }
      for (int j = 0; j < malloc_count; ++j) {
        pool.deallocate(mem[j]);
      }
    }
    std::cout << ", " << clock() - start << std::endl;
  }
}

int main(int argc, const char *argv[]) {
  test_memory_pool();
  test_object_memory_pool();
  test_bucket_pool();
  test_memory_callbacks();
  test_speed();

  std::cout << "Passed: " << passed << std::endl;
  std::cout << "Failed: " << failed << std::endl;

  // Put code to try and crash the library here

  return 0;
}
