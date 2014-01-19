#version 330 core

uniform float ambient;
uniform float diffuse;
uniform float specular;
uniform float specular_power;

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentPos;
in vec3 fviewerPos;

out vec3 color;

void main() {
    
    vec3 lightPos = vec3(100.0f, 100.0f, 100.0f);

    vec3 L = normalize(lightPos - fragmentPos);
    vec3 V = normalize(fviewerPos - fragmentPos);
    vec3 R = -(2 * dot(fragmentNormal, L) * fragmentNormal - L);

    
    float idiff = diffuse * max(dot(fragmentNormal, L), 0.0f);

    float cosRV = dot(normalize(R), normalize(V));
    float ispec = max(specular * pow(cosRV, specular_power), 0);

    float ires = ambient + idiff + ispec;
    // float ires = max(dot(fragmentNormal, fviewerPos), 0.0f);
    color = ires * fragmentColor;
    // color = fragmentPos;

}