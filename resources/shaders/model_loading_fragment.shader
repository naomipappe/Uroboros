#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D diffuse_map;
    sampler2D specular_map;
    sampler2D normal_map;
    float shininess;
};

uniform Material material;

void main() {
    FragColor = texture(material.diffuse_map, TexCoords);
}
