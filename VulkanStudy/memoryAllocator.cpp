#include "memoryAllocator.h"
#include <malloc.h>

void* PSMemoryAllocator::Allocation(
	size_t size,
	size_t alignment,
	VkSystemAllocationScope allocationScope)
{
	// todo : create my own allocator
	return _aligned_malloc(size, alignment);
}

void* VKAPI_CALL PSMemoryAllocator::Allocation(
	void* pUserData,
	size_t size,
	size_t alignment,
	VkSystemAllocationScope allocationScope)
{
	return static_cast<PSMemoryAllocator*>(pUserData)->Allocation(
		size,
		alignment,
		allocationScope
	);
}

void* PSMemoryAllocator::Reallocation(
	void* pOriginal,
	size_t size,
	size_t alignment,
	VkSystemAllocationScope allocationScope)
{
	// todo : create my own allocator
	return _aligned_realloc(pOriginal, size, alignment);
}

void* VKAPI_CALL PSMemoryAllocator::Reallocation(
	void* pUserData,
	void* pOriginal,
	size_t size,
	size_t alignment,
	VkSystemAllocationScope allocationScope)
{
	return static_cast<PSMemoryAllocator*>(pUserData)->Reallocation(
		pOriginal,
		size,
		alignment,
		allocationScope
	);
}

void PSMemoryAllocator::Free(
	void* pMemory)
{
	// todo : create my own allocator
	_aligned_free(pMemory);
}

void VKAPI_CALL PSMemoryAllocator::Free(
	void* pUserData,
	void* pMemory)
{
	static_cast<PSMemoryAllocator*>(pUserData)->Free(pMemory);
}
