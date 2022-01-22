#version 330 core

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;
out vec4 FragColor;

struct Material {
    sampler2D diffuse_map;
    sampler2D specular_map;
    sampler2D normal_map;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Spotlight{
    vec3 position;
    vec3 direction;
    float cutoff_cosine;
    float outer_cutoff_cosine;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


uniform vec3 viewerPosition;

uniform Material material;
uniform Spotlight light;

void main() {
    vec3 lightDirection = normalize(light.position-FragPos);
    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon   = light.cutoff_cosine - light.outer_cutoff_cosine;
    float intensity = clamp((theta - light.outer_cutoff_cosine) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * texture(material.diffuse_map, TexCoords).rgb;

    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse_map, TexCoords).rgb;

    // Calculate the specular lighting component
    vec3 viewerDirection = normalize(viewerPosition - FragPos);
    vec3 reflectionDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewerDirection, reflectionDirection), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular_map, TexCoords).rgb;

    // Attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient  *= attenuation;
    diffuse   *= attenuation;
    specular *= attenuation;

    diffuse *= intensity;
    specular *= intensity;

    // Resulting color
    vec3 result = specular + diffuse + ambient;
    FragColor = vec4(result, 1.0);
}