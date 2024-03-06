#include "VulkanPhysDevice.h"

VulkanPhysDevice::VulkanPhysDevice(VkPhysicalDevice physicalDevice) : device(physicalDevice)
{
	vkGetPhysicalDeviceProperties(device, &properties);
	vkGetPhysicalDeviceFeatures(device, &features);
	vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);

	uint32_t numQueueFamilies{};

	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, nullptr);

	if (!numQueueFamilies)
		throw RenderingEngineException{"No Queue Family Available"};

	queueFamilies.resize(numQueueFamilies);

	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, queueFamilies.data());
}

const VkPhysicalDeviceFeatures& VulkanPhysDevice::getFeatures() const
{
	return features;
}

const std::vector<VkQueueFamilyProperties>& VulkanPhysDevice::getQueueFamilies() const
{
	return queueFamilies;
}

VulkanPhysDevice::operator VkPhysicalDevice() const
{
	return device;
}
