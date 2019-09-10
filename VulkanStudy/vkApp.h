
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

	PSMemoryAllocator m_MemoryAllocator;
public:
	VkResult Init();
	VkResult Finish();
};