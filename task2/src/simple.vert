#version 120

uniform mat4 MVP;

uniform float isWireframe;
uniform float nearClippingPlaneId;
uniform float farClippingPlaneId;

attribute vec3 vertexPosition_modelspace;
attribute vec3 vertexColor;

varying vec3 fragmentColor;

void main() {
    
    gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
    
    if(isWireframe == 1.0)
        fragmentColor = vertexColor;
    else
        fragmentColor = vec3(.9f, .5f, .5f);
    
}