=======================================================================
|	Index
=======================================================================
 
  About Memory Pools
  Memory Pool Classes
	memory_pool
	object_memory_pool
	bucket_memory_pool
		determining distribution
	mempool_callbacks
  License

=======================================================================
|	About Memory Pools
=======================================================================

mempool++ is a header-only library that contains several classes for optimizing a program using 
memory pools.  Memory pools are chunks of data that have been preallocated, and can be quickly 
used to store data, since malloc/free and new/delete require operating system calls, which are 
slow in comparison to just flagging preallocated memory.

=======================================================================
|	Memory Pool Classes
=======================================================================

	------------------------------------------
	| memory_pool
	------------------------------------------
	memory_pool<bytes, size> - Is a memory pool for blocks of a specific size.  If you constantly 
		allocate data that is always the same size, then this type is what you want.  The bytes 
		template tells the library how big each block that gets returned should be.  The size
		parameter tells it haw large to make the memory pool.  The pool will not grow larger 
		than this, if it gets full, it will start dynamically allocating memory.
		
		memory_pool<16, 50> pool();      //creates a pool with 50 blocks, 16 bytes each
		void * block = pool.allocate();  //returns a valid block of 16 free bytes
		pool.deallocate(block);          //returns the block to the pool
		
		
		------------------------------------------
		| Interface
		------------------------------------------
		void * allocate(size_t);
		deallocate(void *);
			
	
	------------------------------------------
	| object_memory_pool
	------------------------------------------	
	object_memory_pool<type, size> - Is a memory pool for a specific type of object.
		This allows you to have constructors called, so that you don't have to worry about 
		doing that yourself.
		
		object_memory_pool<string, 50> pool();  //creates a pool with room for 50 strings
		string * test =	pool.allocate();        //returns a valid string
		pool.deallocate(test);                  //returns the block to the pool
		test = new_object(pool, string("hi"));  //returns a valid string, after calling const char * ctor
		pool.deallocate(test);                  //returns the block to the pool
		
		
		------------------------------------------
		| Interface
		------------------------------------------
		Type * allocate(size_t);
		deallocate(Type *);
		
		Type * new_object(object_memory_pool &, ctor); //Actually a macro
		
		
	------------------------------------------
	| bucket_pool_*
	------------------------------------------
	bucket_pool_*<bytes, size, …> - These are flexible memory pools that hold a range of sizes.  These are 
		especially useful for dynamically allocating strings, since you aren't really sure what 
		size the strings we be at compile time.  This type of memory pool contains several other
		memory_pool objects of various sizes and distributions.  You can have mempool++ 
		recommend some template parameters by running it with some common data with the 
		MEMPOOL_DETERMINE_DISTRIBUTION macro defined.  There are also predefined versions of this
		
		bucket_pool_3<           //creates a bucket pool with 3 buckets
			8,  10,          //10 blocks of 8 bytes each
			16, 20,          //20 blocks of 16 bytes each
			64, 20> pool();  //20 blocks of 64 bytes each
		#ifdef MEMPOOL_DETERMINE_DISTRIBUTION
			pool.profile_on_delete(64, "mypool"); //64 is the longest string, mypool is the identifier
		#endif
		char * str = (char*)pool.allocate(12);   //returns a block of at least 12 chars (will be 16)
		char * str2 = (char*)pool.allocate(90);  //will return a block of at least 90 chars
		char * str3 = (char*)pool.allocate(7);   //will return a block of at least 7 chars (will be 8)
		pool.deallocate(str);
		pool.deallocate(str2);
		pool.deallocate(str3);
		
		
		------------------------------------------
		| Interface
		------------------------------------------
		void * allocate(size_t);
		void * reallocate(void *, size_t);
		deallocate(void *);
		profile_on_delete(size_t, const std::string &); //Only if MEMPOOL_DETERMINE_DISTRIBUTION is defined
		
		
		------------------------------------------
		| Determining distribution
		------------------------------------------
		bucket_pools are hard to determine what the best setup for them is, so this library includes
		a simple tool to figure it out for you.  On like 13 of mempool.h there is a commented line:
		
		//#define MEMPOOL_DETERMINE_DISTRIBUTION
		
		Uncomment that.  It will turn all pooling off for the time being, but the pools will still work, they are
		simply always going to the fallback.  Now find the declaration of the pool that you want to optimize and
		place a profile_on_delete call after it.  This will tell the pool to print out it's recommendation
		when it goes out of scope.  Run it on an average set of data, then replace the template with what gets
		printed out and an optimized bucket pool is ready to go.
		

	------------------------------------------
	| mempool_callbacks
	------------------------------------------
	mempool_callbacks - This is a singleton class that holds pointers to fallback functions.  The
		pools do not grow if they run out of space, they simply start dynamically allocating 
		memory, this class holds pointers to user-defined functions that are to be used in that
		case, if they are not set, then malloc and free are used.
		
		mempool_callbacks::set(malloc, realloc, free);
		
		
=======================================================================
|	License
=======================================================================

Copyright 2011 ninja9578@sourceforge.net. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of 
conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other materials 
provided with the distribution.

THIS SOFTWARE IS PROVIDED BY ninja9578@sourceforge.net ``AS IS'' AND ANY EXPRESS OR IMPLIED 
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ninja9578@sourceforge.net 
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the authors 
and should not be interpreted as representing official policies, either expressed or implied, 
of ninja9578@sourceforge.net.
		
