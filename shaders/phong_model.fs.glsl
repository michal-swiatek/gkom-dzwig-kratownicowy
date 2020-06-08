#version 330
out vec4 fColor;

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

    vec3 color;
};

// źle ustawione == czarne objekty
#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];
//  Lighting is specified in view space
uniform DirLight dirLight;

in vec2 texCoords;
in vec3 fragNormal; //  In model space
in vec3 fragPos;    //  In model space
in vec4 FragPosLightSpace;

uniform sampler2D ourTexture;
uniform sampler2D shadowMap;

uniform vec3 eyePos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec4 fragPosLightSpace);

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(eyePos - fragPos);
    // add the directional light's contribution to the output
    vec3 color = CalcDirLight(dirLight, normal, viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        color += CalcPointLight(pointLights[i],normal,fragPos,viewDir);


    fColor = vec4(color, 1.0f);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDi = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDi), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDi, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
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
    return (ambient + diffuse + specular)*light.color;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // combine results
    vec4 texel = texture(ourTexture, texCoords);
    vec3 ambient = light.ambient * texel.rgb;
    vec3 diffuse = light.diffuse * diff * texel.rgb;
    vec3 specular = light.specular * spec;
    float shadow = ShadowCalculation(FragPosLightSpace);
    return (ambient + (1 - shadow) * (diffuse + specular));
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    float bias = 0.002;
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
    shadow = 0.0;

    return shadow;
}