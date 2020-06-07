#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 mvp;

out vec3 vectorNormal;
out vec2 TexCoord;

void main()
{
    gl_Position = mvp * vec4(vPos, 1.0f);
    vectorNormal = vNormal;
    TexCoord = aTexCoord;
}