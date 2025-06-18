#include "vertex.hpp"
#include <cmath>
#include <glm/gtc/constants.hpp>

std::vector<Vertex> vertices = {
    
};


std::vector<uint16_t> indices = {
    
};

void appendCube(
    glm::vec3 center,
    float size
) {
    uint16_t baseIndex = static_cast<uint16_t>(vertices.size());
    float h = size / 2.0f;

    glm::vec3 positions[8] = {
        {center.x - h, center.y - h, center.z - h},
        {center.x + h, center.y - h, center.z - h},
        {center.x + h, center.y + h, center.z - h},
        {center.x - h, center.y + h, center.z - h},
        {center.x - h, center.y - h, center.z + h},
        {center.x + h, center.y - h, center.z + h},
        {center.x + h, center.y + h, center.z + h},
        {center.x - h, center.y + h, center.z + h},
    };

    glm::vec3 normals[6] = {
        { 0,  0, -1}, // back
        { 0,  0,  1}, // front
        {-1,  0,  0}, // left
        { 1,  0,  0}, // right
        { 0,  1,  0}, // top
        { 0, -1,  0}, // bottom
    };

    glm::vec2 uvs[4] = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
    };

    std::array<uint16_t, 36> localIndices = {
        0, 1, 2, 2, 3, 0, // back
        4, 5, 6, 6, 7, 4, // front
        0, 3, 7, 7, 4, 0, // left
        1, 5, 6, 6, 2, 1, // right
        3, 2, 6, 6, 7, 3, // top
        0, 4, 5, 5, 1, 0  // bottom
    };

    for (int i = 0; i < 8; ++i) {
        glm::vec3 dir = glm::normalize(positions[i] - center);
        vertices.push_back(Vertex{positions[i], dir, uvs[i % 4]});
    }

    for (int i = 0; i < localIndices.size(); ++i) {
        indices.push_back(baseIndex + localIndices[i]);
    }
}

void appendSphere(glm::vec3 center,
                  float radius,
                  int segments,
                  int rings)
{
    uint16_t startIndex = static_cast<uint16_t>(vertices.size());

    for (int y = 0; y <= rings; ++y) {
        float v = float(y) / float(rings);
        float theta = v * glm::pi<float>();

        for (int x = 0; x <= segments; ++x) {
            float u = float(x) / float(segments);
            float phi = u * glm::two_pi<float>();

            float sinTheta = sin(theta);
            float cosTheta = cos(theta);
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            glm::vec3 normal = glm::vec3(
                cosPhi * sinTheta,
                sinPhi * sinTheta,
                cosTheta
            );

            glm::vec3 position = center + radius * normal;
            glm::vec2 texCoord = glm::vec2(u, 1.0f - v); // 翻转v轴

            vertices.push_back({ position, normal, texCoord });
        }
    }

    // 构建索引
    for (int y = 0; y < rings; ++y) {
        for (int x = 0; x < segments; ++x) {
            uint16_t i0 = startIndex + y * (segments + 1) + x;
            uint16_t i1 = i0 + 1;
            uint16_t i2 = i0 + (segments + 1);
            uint16_t i3 = i2 + 1;

            indices.push_back(i0);
            indices.push_back(i2);
            indices.push_back(i1);

            indices.push_back(i1);
            indices.push_back(i2);
            indices.push_back(i3);
        }
    }
}

void appendCone(glm::vec3 center,
                float radius,
                float height,
                int segments)
{
    const float PI = 3.14159265359f;

    uint16_t startIndex = static_cast<uint16_t>(vertices.size());

    glm::vec3 tip = center + glm::vec3(0.0f, height, 0.0f);     // 顶点位置
    glm::vec3 baseCenter = center;                              // 圆锥底部中心

    // 添加圆锥顶部点
    vertices.push_back(Vertex{
        tip,
        glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), // 简化法线
        {0.5f, 1.0f}
    });

    uint16_t tipIndex = startIndex;

    // 添加底部圆边的点
    for (int i = 0; i <= segments; ++i) {
        float angle = (2.0f * PI * i) / segments;
        float x = std::cos(angle) * radius;
        float z = std::sin(angle) * radius;

        glm::vec3 pos = baseCenter + glm::vec3(x, 0.0f, z);
        glm::vec3 normal = glm::normalize(glm::vec3(x, radius / height, z)); // 粗略法线
        glm::vec2 texCoord = {static_cast<float>(i) / segments, 0.0f};

        vertices.push_back(Vertex{
            pos,
            normal,
            texCoord
        });

        if (i > 0) {
            // 侧面三角形：tip - prev - curr
            indices.push_back(tipIndex);
            indices.push_back(startIndex + i);
            indices.push_back(startIndex + i + 1);
        }
    }

    // 添加底面中心点
    uint16_t baseCenterIndex = static_cast<uint16_t>(vertices.size());
    vertices.push_back(Vertex{
        baseCenter,
        glm::vec3(0.0f, -1.0f, 0.0f),
        {0.5f, 0.5f}
    });

    // 添加底面三角形
    for (int i = 1; i <= segments; ++i) {
        indices.push_back(baseCenterIndex);
        indices.push_back(startIndex + i + 1);
        indices.push_back(startIndex + i);
    }
}