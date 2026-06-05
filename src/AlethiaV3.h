#pragma once 
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <optional>

// forward struct for query helper.
struct QueueFamilyIndices{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete() const {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapchainSupportDetails{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class AlethiaV3{
public:
    explicit AlethiaV3(GLFWwindow* window);
    ~AlethiaV3();

    void drawFrame();
    void initVulkan();
    bool isInitialized() const { return m_initialized; }
private:
    GLFWwindow* m_window = nullptr;

    // CORE
    VkInstance M_INSTANCE = VK_NULL_HANDLE;
    VkPhysicalDevice M_PHYSICALDEVICE = VK_NULL_HANDLE;
    VkDevice M_DEVICE = VK_NULL_HANDLE;
    VkQueue M_GRAPHICSQUEUE = VK_NULL_HANDLE;
    VkQueue M_PRESENTQUEUE = VK_NULL_HANDLE;
    VkSurfaceKHR M_SURFACE = VK_NULL_HANDLE;

    // SWAPCHAIN
    VkSwapchainKHR M_SWAPCHAIN = VK_NULL_HANDLE;
    std::vector<VkImage> M_SWAPCHAINIMAGES;
    std::vector<VkImageView> M_SWAPCHAINIMAGEVIEWS;
    VkFormat M_SWAPCHAINIMAGEFORMAT{};
    VkExtent2D M_SWAPCHAINEXTENT{};

    // PIPELINE
    VkRenderPass M_RENDERPASS = VK_NULL_HANDLE;
    VkPipelineLayout M_PIPELINELAYOUT = VK_NULL_HANDLE;
    VkPipeline M_GRAPHICSPIPELINE = VK_NULL_HANDLE;

    // COMMANDS
    std::vector<VkFramebuffer> M_FRAMEBUFFERS;
    VkCommandPool M_COMMANDPOOL = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> M_COMMANDBUFFERS;
    
    // SYNC
    std::vector<VkSemaphore> M_IMAGEAVAILABLESEMAPHORES;
    std::vector<VkSemaphore> M_RENDERFINISHEDSEMAPHORES;
    std::vector<VkFence> M_CURRENTFRAME = 0;

    bool M_INITIALIZED = false;
    
    // SETUP
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();

    // SWAPCHAIN
    void createSwapchain();
    void createImageViews();
    void recreateSwapchain();
    void cleanupSwapchain();

    // PIPELINE
    void createRenderPass();
    void createPipelineLayout();
    void createGraphicsPipeline(); 

    // COMMANDS AND SYNC
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void recordCommandBuffers(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    // QUERY HELPERS
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device);

    // SHADER
    VkShaderModule createShaderModule(const std::vector<char>& code);
    static std::vector<char> readFile(const std::string& filename);

    void cleanup();

};
