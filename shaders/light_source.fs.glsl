#version 330 core
out vec4 fColor;

uniform float lightIntensity;
uniform vec3 color;

void main()
{
    float colorPart = lightIntensity * 0.7 + 0.3; // linear transformation: from [0.0; 1.0] to [0.3; 1.0]
    fColor = vec4(colorPart*color, 1.0);
}