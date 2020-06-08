#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 fragNormal;
out vec3 fragPos;
out vec2 texCoords;
out vec4 FragPosLightSpace;

uniform mat4 model;
uniform mat4 mvp;
uniform mat3 modelInvTrans;
uniform mat4 lightSpaceMatrix;

void main() {
    fragNormal = modelInvTrans * vNormal;
    fragPos = vec3(model * vec4(vPos, 1.0f));
    texCoords = aTexCoords;
    FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
    gl_Position = mvp * vec4(vPos, 1.0f);
}
