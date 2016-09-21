#pragma once
#include "../PoolAllocator.h"
#include "PoolParkInternal.h"
#include "DynamicList.h"

class PoolAllocatorSelfSustainedInternal
    :public PoolAllocator
{
public:
    /**
    @desc - creates one initial pool whit the size of a memory block
    @param1 - the pool park, this class will not be responsible for deleting
    */
    PoolAllocatorSelfSustainedInternal(PoolParkInternal* p_poolPark, const int& p_segmentSize);
    PoolAllocatorSelfSustainedInternal();
    ~PoolAllocatorSelfSustainedInternal();

    int TestMethod() override;
    void* Allocate() override;
    void Deallocate(void* p_memory, const int& p_size) override;

private:
    void CreateNewPool();
    bool MemoryBlockFull(void* p_startOfBlock, const int& p_segment);

    MemLib::OwnVector<void*> m_startOfMemoryBlocks;
    MemLib::OwnVector<void*> m_freedSegments;
    PoolParkInternal* m_poolPark;
    int m_segmentSize;
    int m_currentPool;
    int m_segmentsInMemoryBlock;
    int m_currentSegment;
};

