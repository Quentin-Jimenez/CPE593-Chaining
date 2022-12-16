// Source for base mempool https://iq.opengenus.org/memory-pool/
#include <stdio.h>>


//TODO:: Need to change implemntation of this using chunks
class MemoryPool
{
    private:
    typedef struct SMemoryChunk
    {
        char *Data ;
        std::size_t DataSize ;
        std::size_t UsedSize ;    
        bool IsAllocationChunk ; 
        SMemoryChunk *Next ;      
    } SMemoryChunk ;

    public:
    MemoryPool(const MemoryPool&);
    MemoryPool& operator=(const MemoryPool);


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

        void *tmpPool = mempool;


    }

    void clearMemPool(void)
    {
        //TODO:: Implement this
    }


}
