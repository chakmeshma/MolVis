#pragma once

#include "RenderingEngineException.hpp"
#include "VulkanPhysDevice.h"
#include "vulkan/vulkan.h"
#include <vector>

class VulkanInstance
{
public:
	VulkanInstance(bool validation);
	~VulkanInstance();
	VulkanPhysDevice& getPhysicalDevice();
private:
	void selectPhysicalDevice();

	VkInstance instance{ VK_NULL_HANDLE };
	VkApplicationInfo appInfo{};
	VkInstanceCreateInfo createInfo{};
	VulkanPhysDevice* physicalDevice{};

	static const uint32_t targetAPIVersion;
	static const char* appName;
	static const uint32_t appVersion;
	static const char* engineName;
	static const uint32_t engineVersion;
	static std::vector<const char*> layers;
	static const std::vector<const char*> extensions;
};

