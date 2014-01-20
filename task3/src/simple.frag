#version 330 core

uniform float ambient;
uniform float diffuse;
uniform float specular;
uniform float specular_power;
uniform int is_blin;

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentPos;
in vec3 fviewerPos;

out vec3 color;

void main() {
    
    vec3 lightPos = vec3(100.0f, 100.0f, 100.0f);
    
    vec3 N = fragmentNormal;
    vec3 L = normalize(lightPos - fragmentPos);
    vec3 V = normalize(fragmentPos - fviewerPos);
    vec3 R = (2 * dot(N, L) * N - L);
    

    
    float idiff = diffuse * max(dot(N, L), 0.0f);

    
    float ispec = 0;
    if(is_blin == 0){
        float cosRV = dot(normalize(R), normalize(V));
        ispec = max(specular * pow(cosRV, specular_power), 0);
    } else {
        vec3 H = normalize(L + V);
        ispec = max(specular * pow(dot(H, N), specular_power), 0);
    }

    float ires = ambient + idiff + ispec;
    // float ires = max(dot(N, fviewerPos), 0.0f);
    color = ires * fragmentColor;
    // color = fragmentPos;

}