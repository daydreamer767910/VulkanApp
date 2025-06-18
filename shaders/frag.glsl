#version 450

layout(location = 0) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;

layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 normal = normalize(fragNormal);
    vec4 texColor = texture(texSampler, fragTexCoord);

    // Light from +X (white, strong)
    vec3 lightDirX = normalize(vec3(1.0, 0.0, 0.0));
    vec3 lightColorX = vec3(1.0);       // 白色
    float intensityX = 0.0;
    float diffX = max(dot(normal, lightDirX), 0.0);
    vec3 resultX = diffX * lightColorX * intensityX;

    // Light from +Y (yellow, medium)
    vec3 lightDirY = normalize(vec3(0.0, 1.0, 0.0));
    vec3 lightColorY = vec3(0, 1.0, 1.0); 
    float intensityY = 0.0;
    float diffY = max(dot(normal, lightDirY), 0.0);
    vec3 resultY = diffY * lightColorY * intensityY;

    // Light from +Z (red, weak)
    vec3 lightDirZ = normalize(vec3(0.0, 0.0, 1.0));
    vec3 lightColorZ = vec3(1.0, 0.0, 1.0); // 红色
    float intensityZ = 1.0;
    float diffZ = max(dot(normal, lightDirZ), 0.0);
    vec3 resultZ = diffZ * lightColorZ * intensityZ;

    // Combine all
    vec3 ambient = 0.02 * vec3(1.0); // 5% 环境白光
    vec3 totalLight = ambient + resultX + resultY + resultZ;

    // Final color
    outColor = texColor * vec4(totalLight, 1.0);
}
