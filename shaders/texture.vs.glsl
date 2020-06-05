#version 330 core

out vec4 fColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 color;

void main()
{
    fColor = texture(ourTexture, TexCoord);
}