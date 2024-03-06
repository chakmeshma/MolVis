#include "VulkanDevice.h"

const std::vector<const char*> VulkanDevice::layers{};
const std::vector<const char*> VulkanDevice::extensions{ "VK_KHR_swapchain" };

VulkanDevice::VulkanDevice(VulkanPhysDevice& physicalDevice) : parentPhysicalDevice{physicalDevice}
{
	VkDeviceQueueCreateInfo queueCreateInfos[2]{ {},{} };
	bool sameQueue = getGraphicsQueueFamilyIndex() == getTransferQueueFamilyIndex();
	float queuePriorities[1]{ 1.0f };

	queueCreateInfos[0] = {
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			nullptr,
			0,
			getGraphicsQueueFamilyIndex(),
			1,
			queuePriorities
	};

	if (!sameQueue) {
		queueCreateInfos[1] = {
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			nullptr,
			0,
			getTransferQueueFamilyIndex(),
			1,
			queuePriorities
		};
	}

	VkPhysicalDeviceFeatures desiredFeatures(physicalDevice.getFeatures());

	desiredFeatures.tessellationShader = VK_FALSE;
	desiredFeatures.geometryShader = VK_FALSE;


	createInfo = {
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		nullptr,
		0,
		sameQueue ? 1U : 2U,
		queueCreateInfos,
		(uint32_t)layers.size(),
		layers.data(),
		(uint32_t)extensions.size(),
		extensions.data(),
		&desiredFeatures
	};

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		throw RenderingEngineException{ "Device Creation Failed" };
}

uint32_t VulkanDevice::getGraphicsQueueFamilyIndex()
{
	if (graphicsQueueIndex == -1) {
		for (uint16_t i = 0; i < parentPhysicalDevice.getQueueFamilies().size(); i++) {
			if (parentPhysicalDevice.getQueueFamilies()[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
			{
				graphicsQueueIndex = i;
				break;
			}
		}
	}

	return graphicsQueueIndex;
}

uint32_t VulkanDevice::getTransferQueueFamilyIndex()
{
	if (transferQueueIndex == -1) {
		for (uint16_t i = 0; i < parentPhysicalDevice.getQueueFamilies().size(); i++) {
			if (parentPhysicalDevice.getQueueFamilies()[i].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT)
			{
				transferQueueIndex = i;
				break;
			}
		}
	}

	return transferQueueIndex;
}

VulkanDevice::~VulkanDevice() {
	if (device != VK_NULL_HANDLE) {
		if (vkDeviceWaitIdle(device) != VK_SUCCESS)
			throw RenderingEngineException{ "Device Wait Idle Failed" };

		vkDestroyDevice(device, nullptr);
	}
}