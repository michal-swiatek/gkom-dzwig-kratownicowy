#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

void main() {
    gl_Position = vec4(vPos, 1.0f);
}
