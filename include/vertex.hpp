#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

const std::vector<Vertex> vertices = {
    // 前面（红色）
    {{-0.5f, -0.5f,  0.5f}, {1, 0, 0}, {0.0f, 0.0f}},  // 左下
    {{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}, {1.0f, 1.0f}},  // 右上
    {{ 0.5f, -0.5f,  0.5f}, {1, 0, 0}, {1.0f, 0.0f}},  // 右下
    {{-0.5f, -0.5f,  0.5f}, {1, 0, 0}, {0.0f, 0.0f}},  // 左下
    {{-0.5f,  0.5f,  0.5f}, {1, 0, 0}, {0.0f, 1.0f}},  // 左上
    {{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}, {1.0f, 1.0f}},  // 右上

    // 后面（绿色）
    {{-0.5f, -0.5f, -0.5f}, {0, 1, 0}, {1.0f, 0.0f}},  // 右下
    {{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}, {0.0f, 1.0f}},  // 左上
    {{ 0.5f, -0.5f, -0.5f}, {0, 1, 0}, {0.0f, 0.0f}},  // 左下
    {{-0.5f, -0.5f, -0.5f}, {0, 1, 0}, {1.0f, 0.0f}},  // 右下
    {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1.0f, 1.0f}},  // 右上
    {{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}, {0.0f, 1.0f}},  // 左上

    // 左面（蓝色）
    {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1.0f, 1.0f}},  // 右上
    {{-0.5f, -0.5f, -0.5f}, {0, 0, 1}, {0.0f, 0.0f}},  // 左下
    {{-0.5f,  0.5f, -0.5f}, {0, 0, 1}, {0.0f, 1.0f}},  // 左上
    {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1.0f, 1.0f}},  // 右上
    {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1.0f, 0.0f}},  // 右下
    {{-0.5f, -0.5f, -0.5f}, {0, 0, 1}, {0.0f, 0.0f}},  // 左下

    // 右面（黄色）
    {{ 0.5f,  0.5f,  0.5f}, {1, 1, 0}, {0.0f, 1.0f}},  // 左上
    {{ 0.5f, -0.5f, -0.5f}, {1, 1, 0}, {1.0f, 0.0f}},  // 右下
    {{ 0.5f,  0.5f, -0.5f}, {1, 1, 0}, {1.0f, 1.0f}},  // 右上
    {{ 0.5f,  0.5f,  0.5f}, {1, 1, 0}, {0.0f, 1.0f}},  // 左上
    {{ 0.5f, -0.5f,  0.5f}, {1, 1, 0}, {0.0f, 0.0f}},  // 左下
    {{ 0.5f, -0.5f, -0.5f}, {1, 1, 0}, {1.0f, 0.0f}},  // 右下

    // 上面（青色）
    {{-0.5f,  0.5f, -0.5f}, {0, 1, 1}, {0.0f, 0.0f}},  // 左下
    {{ 0.5f,  0.5f,  0.5f}, {0, 1, 1}, {1.0f, 1.0f}},  // 右上
    {{ 0.5f,  0.5f, -0.5f}, {0, 1, 1}, {1.0f, 0.0f}},  // 右下
    {{-0.5f,  0.5f, -0.5f}, {0, 1, 1}, {0.0f, 0.0f}},  // 左下
    {{-0.5f,  0.5f,  0.5f}, {0, 1, 1}, {0.0f, 1.0f}},  // 左上
    {{ 0.5f,  0.5f,  0.5f}, {0, 1, 1}, {1.0f, 1.0f}},  // 右上

    // 下面（品红）
    {{-0.5f, -0.5f, -0.5f}, {1, 0, 1}, {1.0f, 1.0f}},  // 右上
    {{ 0.5f, -0.5f,  0.5f}, {1, 0, 1}, {0.0f, 0.0f}},  // 左下
    {{ 0.5f, -0.5f, -0.5f}, {1, 0, 1}, {0.0f, 1.0f}},  // 左上
    {{-0.5f, -0.5f, -0.5f}, {1, 0, 1}, {1.0f, 1.0f}},  // 右上
    {{-0.5f, -0.5f,  0.5f}, {1, 0, 1}, {1.0f, 0.0f}},  // 右下
    {{ 0.5f, -0.5f,  0.5f}, {1, 0, 1}, {0.0f, 0.0f}},  // 左下
};