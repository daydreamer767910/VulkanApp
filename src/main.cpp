#include "vulkan_setup.h"
#include <iostream>

int main() {
    VulkanApp app;
    
    try {
        app.init();
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
