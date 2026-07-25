# src/CMakeLists.txt

# --- Shader compilation ---
set(V3_SHADER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(V3_SHADER_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${V3_SHADER_BIN_DIR})

find_program(GLSLC glslc)
if(NOT GLSLC)
    message(FATAL_ERROR "glslc not found. Install Vulkan SDK.")
endif()

set(V3_SHADERS "")
set(V3_SPV_FILES "")

add_custom_target(AlethiaV3Shaders DEPENDS ${V3_SPV_FILES})

# --- Library ---
add_library(alethia_v3 STATIC
    initv3.cpp
    AlethiaV3.cpp
    Vulkan/createInstance.cpp
    Vulkan/debugMessenger.cpp
    Vulkan/createSurface.cpp
    Vulkan/pickPhysicalDevice.cpp
    Vulkan/createLogicalDevice.cpp
    initVulkan.cpp
)

target_include_directories(alethia_v3 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(alethia_v3 PUBLIC
    Vulkan::Vulkan
    glfw
)

if(APPLE)
    target_link_libraries(alethia_v3 PUBLIC
        "-framework Metal"
        "-framework Foundation"
        "-framework QuartzCore"
        "-framework CoreGraphics"
        "-framework IOSurface"
    )
    target_compile_definitions(alethia_v3 PRIVATE MVK_CONFIG_LOG_LEVEL=1)
endif()

target_compile_definitions(alethia_v3 PRIVATE
    ALETHIA_V3_SHADER_DIR="${V3_SHADER_BIN_DIR}"
)

add_dependencies(alethia_v3 AlethiaV3Shaders)
