#pragma once

#include "VulkanPhysDevice.h"
#include "vulkan/vulkan.h"
#include <vector>

class VulkanDevice
{
public:
	VulkanDevice(VulkanPhysDevice& physicalDevice);
	~VulkanDevice();

private:
	VkDevice device{ VK_NULL_HANDLE };
	const VulkanPhysDevice& parentPhysicalDevice;
	VkDeviceCreateInfo createInfo{};
	uint32_t getGraphicsQueueFamilyIndex();
	uint32_t getTransferQueueFamilyIndex();
	int graphicsQueueIndex{ -1 };
	int transferQueueIndex{ -1 };

	static const std::vector<const char*> layers;
	static const std::vector<const char*> extensions;
};

