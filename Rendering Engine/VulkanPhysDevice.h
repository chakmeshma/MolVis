#pragma once

#include "RenderingEngineException.hpp"
#include "vulkan/vulkan.h"
#include <vector>

class VulkanPhysDevice
{
public:
	VulkanPhysDevice(VkPhysicalDevice physicalDevice);
	const VkPhysicalDeviceFeatures& getFeatures() const;
	const std::vector<VkQueueFamilyProperties>& getQueueFamilies() const;
	operator VkPhysicalDevice() const;

private:

	VkPhysicalDevice device{ VK_NULL_HANDLE };
	VkPhysicalDeviceProperties properties{};
	VkPhysicalDeviceFeatures features{};
	VkPhysicalDeviceMemoryProperties memoryProperties{};
	std::vector<VkQueueFamilyProperties> queueFamilies{};
};

