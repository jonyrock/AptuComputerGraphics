#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentPos;

out vec3 color;

void main() {
    color = normalize(fragmentNormal);
}