#version 120

uniform mat4 MVP;

uniform float isWireframe;
uniform float nearClippingPlaneId;
uniform float farClippingPlaneId;

attribute vec3 vertexPosition_modelspace;
attribute vec3 vertexColor;

varying vec3 fragmentColor;

void main() {
    
    vec4 v = vec4(vertexPosition_modelspace, 1);
    v.y = v.y * cos(v.y * 20.0) + sin(v.x) * 2;
    v = MVP * v;
    


    gl_Position = v;
    if(isWireframe == 1.0)
        fragmentColor = vertexColor;
    else
        fragmentColor = vec3(.9f, .5f, .5f);
    
}