#pragma once

#include "common/vulkan_common.h"

namespace engine
{
    struct DebugUtilsSettings
    {
        uint32_t VulkanMessageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        uint32_t VulkanMessageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    };

    class PhysicalDevice;

    class Instance
    {
    public:
        Instance(std::string &name,
                 std::unordered_map<const char *, bool> &required_extensions,
                 std::vector<const char *> &required_validation_layers,
                 DebugUtilsSettings debug_messenger_settings,
                 bool headless,
                 uint32_t api_version);
        Instance() = delete;
        ~Instance();

        VkInstance GetHandle() { return m_Handle; }
        PhysicalDevice &GetBestGpu();

    private:
        std::vector<const char *> m_EnabledExtensions;
        DebugUtilsSettings m_DebugUtilsSettings;

#if defined(ENG_DEBUG) || defined(ENG_VALIDATION_LAYERS)
        VkDebugUtilsMessengerEXT m_DebugUtilsMessenger = VK_NULL_HANDLE;
        VkDebugReportCallbackEXT m_DebugReportCallback = VK_NULL_HANDLE;
#endif

        void QueryGpus();

        std::vector<std::unique_ptr<PhysicalDevice>> m_Gpus;

        VkInstance m_Handle = nullptr;
    };
}