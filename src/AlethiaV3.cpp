#include "AlethiaV3.h"
#include <iostream>
#include <stdexcept>

// Constructor
AlethiaV3::AlethiaV3(GLFWwindow* window) 
    : m_window(window)
{
    std::cout << "[AlethiaV3] Constructor called\n"; 
}

// Destructor
AlethiaV3::~AlethiaV3()
{
    std::cout << "[AlethiaV3] Destructor called\n";
    cleanup();
}


void AlethiaV3::drawFrame()
{


}

void AlethiaV3::cleanup()
{
    std::cout << "  [cleanup] Starting ... \n";

    for (auto ImageView : M_SWAPCHAINIMAGEVIEWS)
    {
        vkDestroyImageView(M_DEVICE, ImageView, nullptr);
    }
    if (!M_SWAPCHAINIMAGEVIEWS.empty())
    {
        std::cout << "  [cleanup] " << M_SWAPCHAINIMAGEVIEWS.size() << " image views destroyed. \n";
    }

    for (size_t i = 0; i < M_INFLIGHTFENCES.size(); i++)
    {
        vkDestroySemaphore(M_DEVICE, M_RENDERFINISHEDSEMAPHORES[i], nullptr);
        vkDestroySemaphore(M_DEVICE, M_IMAGEAVAILABLESEMAPHORES[i], nullptr);
        vkDestroyFence(M_DEVICE, M_INFLIGHTFENCES[i], nullptr);
    }
    if (!M_INFLIGHTFENCES.empty())
    {
        std::cout << "  [cleanup] Sync Objects destroyed. \n";
    }

    if (M_COMMANDPOOL != VK_NULL_HANDLE)
    {
        vkDestroyCommandPool(M_DEVICE, M_COMMANDPOOL, nullptr);
        std::cout << "  [cleanup] Command pool destroyed. \n";
    }

    if (M_SWAPCHAIN != VK_NULL_HANDLE)
    {
        vkDestroySwapchainKHR(M_DEVICE, M_SWAPCHAIN, nullptr);
        std::cout << "  [cleanup] Swapchain destroyed. \n";
    }
    
    if (M_DEVICE != VK_NULL_HANDLE)
    {
        vkDestroyDevice(M_DEVICE, nullptr);
        std::cout << "  [cleanup] Logical device destroyed.\n";
    }

    if (M_SURFACE != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(M_INSTANCE, M_SURFACE, nullptr);
        std::cout << "  [cleanup] Surface destroyed.\n";
    }

    if (M_DEBUGMESSENGER != VK_NULL_HANDLE)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(M_INSTANCE, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(M_INSTANCE, M_DEBUGMESSENGER, nullptr);
            std::cout << "  [cleanup] Debug messenger destroyed.\n";
        }
    }

    if (M_INSTANCE != VK_NULL_HANDLE)
    {
        vkDestroyInstance(M_INSTANCE, nullptr);
        std::cout << "  [cleanup] Instance destroyed.\n";
    }

    std::cout << " [cleanup] Complete.\n";
}