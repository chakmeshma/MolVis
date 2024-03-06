#include "../Rendering Engine/VulkanInstance.h"
#include "../Rendering Engine/VulkanDevice.h"
#include "../Rendering Engine/VulkanPhysDevice.h"

#include <iostream>

int main()
{
	{
		VulkanInstance ins{ true };

		VulkanDevice bb(ins.getPhysicalDevice());
	}

	return 0;
}
