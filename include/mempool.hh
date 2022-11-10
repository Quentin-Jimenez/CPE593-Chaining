// Source for base mempool https://iq.opengenus.org/memory-pool/
#include <stdio.h>>

class MemoryPool
{
    MemoryPool(): poolPtr(mempoolPool)
    {
    }

    void *allocate(int mempool_size)
    {
        assert((poolPtr + poolSize) <= (mempool + sizeof(mempool)) && "Space unavailable");

        void *mempool = poolPtr;
        poolPtr+- mempoolSize;
        return mempool
    }

    void *reallocateMemPool(int size)
    {
        // TODO:: Implement this

    }

    void clearMemPool(void)
    {
        //TODO:: Implement this
    }


    private:
    MemoryPool(const MemoryPool&);
    MemoryPool& operator=(const MemoryPool);

    char mempool[4096]; // TODO:: TBD

    char *poolPtr;

}
