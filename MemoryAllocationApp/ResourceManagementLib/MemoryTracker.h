#pragma once
class MemoryTracker
{
public:
	
	bool CheckIfMemoryAvailable(size_t p_desiredMemory);
	static MemoryTracker* Get();
	static void Startup(size_t p_maximumMemory);
	void AddMemoryUsage(int p_memoryToAdd);
private:
	static MemoryTracker* m_singleton;
	size_t m_maximumMemory; 
	MemoryTracker(size_t p_maximumMemory);
	~MemoryTracker();
	int m_usedMemory;
};
