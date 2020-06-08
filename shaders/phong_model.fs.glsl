#version 330
out vec4 fColor;

//struct Material
//{
//    sampler2D ambient;
//    sampler2D diffuse;
//    sampler2D specular;
//
//    float shininess;
//};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
// źle ustawione == czarny objekt
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];
//  Lighting is specified in view space
uniform DirLight dirLight;
//uniform Material material;

in vec2 texCoords;
in vec3 fragNormal; //  In model space
in vec3 fragPos;    //  In model space
uniform sampler2D ourTexture;
uniform vec3 eyePos;
uniform float shininess;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(eyePos - fragPos);

    // define an output color value

    // add the directional light's contribution to the output
    vec3 color = CalcDirLight(dirLight, normal, viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        color += CalcPointLight(pointLights[i],normal,fragPos,viewDir);

//    color += CalcSpotLight(light, normal, fragPos, viewDir);

    fColor = vec4(color, 1.0f);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDi = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDi), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDi, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(ourTexture, texCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(ourTexture, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(ourTexture, texCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(ourTexture, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(ourTexture, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(ourTexture, texCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(ourTexture, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(ourTexture, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(ourTexture, texCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}