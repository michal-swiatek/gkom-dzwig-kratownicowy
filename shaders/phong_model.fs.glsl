#version 330
out vec4 fColor;

struct Material
{
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

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

in vec3 fragNormal; //  In model space
in vec3 fragPos;    //  In model space
in vec2 texCoords;

//  Lighting is specified in view space
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight = DirLight(vec3(0.0f), vec3(0.1f), vec3(1.0f), vec3(0.5f));
uniform Material material;

uniform vec3 eyePos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(eyePos - fragPos);

    // define an output color value
    vec3 color = vec3(0.0);
    // add the directional light's contribution to the output
    color += someFunctionToCalculateDirectionalLight(dirLight, normal, viewDir);

    for(int i = 0; i < nr_of_point_lights; i++)
        color += someFunctionToCalculatePointLight(pointLights[i],normal,fragPos,viewDir);

    fColor = vec4(color, 1.0f);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDi = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDi), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDi, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDi = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDi), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDi, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}