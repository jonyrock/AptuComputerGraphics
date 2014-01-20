#version 330 core

uniform float ambient;
uniform float diffuse;
uniform float specular;
uniform float specular_power;

uniform float kc;
uniform float kl;
uniform float kq;

uniform int is_blinn;

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentPos;
in vec3 fviewerPos;

out vec3 color;

void main() {
    
    vec3 lightColor = vec3(1.0f, 235.0f/255, 30.f/255);
    vec3 lightPos = vec3(30.0f, 30.0f, 20.0f);
    
    vec3 N = fragmentNormal;
    vec3 L = normalize(lightPos - fragmentPos);
    vec3 V = normalize(fragmentPos - fviewerPos);
    vec3 R = (2 * dot(N, L) * N - L);
    
    float d = length(lightPos - fragmentPos) * 1000 + 100;
    float intensity = 1.0f / (kc + kl * d + kq * d * d);
    //float intensity = 1.0f;
    
    
    float idiff = diffuse * max(dot(N, L), 0.0f);

    
    float ispec = 0;
    if(is_blinn == 0){
        float cosRV = dot(normalize(R), normalize(V));
        ispec = max(specular * pow(cosRV, specular_power), 0);
    } else {
        vec3 H = normalize(L + V);
        ispec = max(specular * pow(dot(H, N), specular_power), 0);
    }

    float ires = ambient + idiff + ispec;
    ires *= intensity;
    // float ires = max(dot(N, fviewerPos), 0.0f);
    color.r = ires * lightColor.r * fragmentColor.r;
    color.g = ires * lightColor.g * fragmentColor.g;
    color.b = ires * lightColor.b * fragmentColor.b;
    // color = fragmentPos;

}