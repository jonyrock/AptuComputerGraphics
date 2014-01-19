#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentPos;

out vec3 color;

void main() {
    
    float ambient = 0.4f;
    float diffuse = 0.3f;

    vec3 lightPos = vec3(100.0f, 100.0f, 100.0f);

    vec3 L = normalize(lightPos - fragmentPos);

    float idiff = max(dot(fragmentNormal, L), 0.0f);

    //color = normalize(fragmentPos);
    float ires = ambient + idiff;
    color = ires * fragmentColor;

}