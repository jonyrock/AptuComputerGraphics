#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentPos;
in vec3 fviewerPos;

out vec3 color;

void main() {
    
    float ambient = 0.4f;
    float diffuse = 0.3f;
    float specular = 0.3f;
    float specular_power = 0.1f;

    vec3 lightPos = vec3(100.0f, 100.0f, 100.0f);

    vec3 L = normalize(lightPos - fragmentPos);
    vec3 V = normalize(fviewerPos - fragmentPos);
    vec3 R = 2 * dot(fragmentNormal, L) * fragmentNormal - L;

    
    float idiff = max(dot(fragmentNormal, L), 0.0f);

    float cosRV = dot(normalize(R), normalize(V));
    float ispec = max(specular * pow(cosRV, specular_power), 0);

    float ires = ambient + idiff + ispec;
    // float ires = max(dot(fragmentNormal, fviewerPos), 0.0f);
    color = ires * fragmentColor;

}