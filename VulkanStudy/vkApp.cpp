#include "vkApp.h"

// todo : to data...
static const bool useCustomAllocator = false;

VkResult vkApp::Init()
{
	VkResult result = VK_SUCCESS;

	VkApplicationInfo appInfo = { };
	VkInstanceCreateInfo ici = { };

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = VK_MAKE_VERSION(1, 1, 114);
	appInfo.applicationVersion = 1;
	appInfo.engineVersion = 1;
	appInfo.pApplicationName = "test";
	appInfo.pEngineName = "testEngine";

	ici.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ici.pApplicationInfo = &appInfo;

	VkAllocationCallbacks* callbackPtr = nullptr;
	VkAllocationCallbacks allocCallbacks = {};
	if (useCustomAllocator)
	{
		allocCallbacks = m_MemoryAllocator;
	}

	result = vkCreateInstance(&ici, callbackPtr, &m_Instance);

	// get physical devices
	if (result != VK_SUCCESS)
		return result;
	{
		uint32_t deviceCount = 0;
		result = vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

		if (result != VK_SUCCESS || deviceCount == 0)
			return result;

		m_PhysicalDevices.resize(deviceCount);
		result = vkEnumeratePhysicalDevices(m_Instance, &deviceCount, m_PhysicalDevices.data());

		if (result != VK_SUCCESS)
			return result;
	}
	
	// get physical device features/properties 
	// todo : support multiple physical device
	{
		uint32_t queueFamilyPropertyCount;
		std::vector<VkQueueFamilyProperties> queueFamilyProperties;
		VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;

		// memory properties
		vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevices[0], &physicalDeviceMemoryProperties);

		// get queue Family count
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevices[0], &queueFamilyPropertyCount, nullptr);

		queueFamilyProperties.resize(queueFamilyPropertyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevices[0], &queueFamilyPropertyCount, queueFamilyProperties.data());
	}

	{
		VkPhysicalDeviceFeatures supportedFeatures;
		VkPhysicalDeviceFeatures requiredFeatures = { };

		vkGetPhysicalDeviceFeatures(m_PhysicalDevices[0], &supportedFeatures);

		// todo : required features to data
		requiredFeatures.multiDrawIndirect = supportedFeatures.multiDrawIndirect;
		requiredFeatures.tessellationShader = VK_TRUE;
		requiredFeatures.geometryShader = VK_TRUE;

		// create logical device
		VkDeviceQueueCreateInfo qci =
		{
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			nullptr,
			0,
			0,
			1,
			nullptr
		};
		
		VkDeviceCreateInfo dci = 
		{
			VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			nullptr,
			0,
			1,
			&qci,
			0,
			nullptr,
			0,
			nullptr,
			&requiredFeatures
		};
		
		vkCreateDevice(m_PhysicalDevices[0], &dci, callbackPtr, &m_Device);
	}
	
	// instance layer
	{
		uint32_t numInstanceLayers = 0;

		vkEnumerateInstanceLayerProperties(&numInstanceLayers, nullptr);

		if (numInstanceLayers != 0)
		{
			m_LayerProperties.resize(numInstanceLayers);

			vkEnumerateInstanceLayerProperties(&numInstanceLayers, m_LayerProperties.data());

		}
	}

	// instance extension
	{
		uint32_t numExtension = 0;

		vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, nullptr);

		if (numExtension != 0)
		{
			m_ExtensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, m_ExtensionProperties.data());
		}
	}
	return result;
}

VkResult vkApp::Finish()
{
	VkResult result = VK_SUCCESS;

	VkAllocationCallbacks* callbackPtr = nullptr;
	VkAllocationCallbacks allocCallbacks = {};
	if (useCustomAllocator)
	{
		allocCallbacks = m_MemoryAllocator;
	}

	vkDeviceWaitIdle(m_Device);
	vkDestroyDevice(m_Device, callbackPtr);

	vkDestroyInstance(m_Instance, callbackPtr);


	return result;
}