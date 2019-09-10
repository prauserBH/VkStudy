
#include "memoryAllocator.h"

#include <vector>

class vkApp
{
private:

	VkInstance m_Instance;
	std::vector<VkPhysicalDevice> m_PhysicalDevices;

	// todo : support multiple logical devices
	VkDevice m_Device;

	std::vector<VkLayerProperties> m_LayerProperties;
	std::vector<VkExtensionProperties> m_ExtensionProperties;

	VkAllocationCallbacks* m_CallbackPtr;
	VkAllocationCallbacks m_AllocCallbacks;
	PSMemoryAllocator m_MemoryAllocator;
public:
	VkResult Init();
	VkResult Finish();

	// todo : parameterize
	VkResult CreateBuffer(VkBuffer* buffer);
	VkResult CreateImage(VkImage* image);

};