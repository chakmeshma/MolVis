#include "VulkanInstance.h"

const uint32_t VulkanInstance::targetAPIVersion{ VK_API_VERSION_1_0 };
const char* VulkanInstance::appName{ "MolVis" };
const uint32_t VulkanInstance::appVersion{ 0 };
const char* VulkanInstance::engineName{ "MolVis Engine" };
const uint32_t VulkanInstance::engineVersion{ 0 };
const std::vector<const char*> VulkanInstance::extensions{ "VK_KHR_surface", "VK_KHR_win32_surface" };
std::vector<const char*> VulkanInstance::layers{ "VK_LAYER_KHRONOS_validation" };

VulkanInstance::VulkanInstance(bool validation)
{
	appInfo = {
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		nullptr,
		appName,
		appVersion,
		engineName,
		engineVersion,
		targetAPIVersion
	};

	if (!validation)
		layers.clear();

	createInfo = {
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		nullptr,
		0,
		&appInfo,
		(uint32_t)layers.size(),
		layers.data(),
		(uint32_t)extensions.size(),
		extensions.data()
	};

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		throw RenderingEngineException{ "Instance Creation Failed"};

	selectPhysicalDevice();
}

VulkanInstance::~VulkanInstance()
{
	if (physicalDevice)
		delete physicalDevice;

	if (instance != VK_NULL_HANDLE)
		vkDestroyInstance(instance, nullptr);
}

VulkanPhysDevice& VulkanInstance::getPhysicalDevice()
{
	return *physicalDevice;
}

void VulkanInstance::selectPhysicalDevice()
{
	uint32_t numPhysicalDevices{};

	if(vkEnumeratePhysicalDevices(instance, &numPhysicalDevices, nullptr) != VK_SUCCESS)
		throw RenderingEngineException{ "Physical Device Enumeration Failed" };

	if(!numPhysicalDevices)
		throw RenderingEngineException{ "No Physical Device Available" };

	VkPhysicalDevice* _physicalDevices = new VkPhysicalDevice[numPhysicalDevices];

	if (vkEnumeratePhysicalDevices(instance, &numPhysicalDevices, _physicalDevices) != VK_SUCCESS)
		throw RenderingEngineException{ "Physical Device Enumeration Failed" };

	physicalDevice = new VulkanPhysDevice(_physicalDevices[0]); // Selecting First Available Physical Device

	delete[] _physicalDevices;
}
