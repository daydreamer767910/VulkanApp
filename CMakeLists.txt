cmake_minimum_required(VERSION 3.10)
project(glfw_demo)

set(CMAKE_CXX_STANDARD 17)

# 假设你安装在这个目录
set(VULKAN_SDK_ROOT "d:/VulkanSDK/1.4.313.2")

include_directories(${VULKAN_SDK_ROOT}/Include)
link_directories(${VULKAN_SDK_ROOT}/Lib)

# 设置头文件路径和库文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include)
link_directories(${CMAKE_SOURCE_DIR}/glfw/lib)

# 生成可执行文件
add_executable(${PROJECT_NAME} src/main.cpp src/vulkan_setup.cpp src/vertex.cpp)

# 链接 GLFW 和系统库
target_link_libraries(${PROJECT_NAME} glfw3 gdi32 vulkan-1 opengl32)
