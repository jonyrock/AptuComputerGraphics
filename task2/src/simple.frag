#version 120

varying vec3 fragmentColor;

void main(){
    float bright = 1 - (gl_FragCoord.z - 0.99) * 100;
    gl_FragColor = vec4(fragmentColor * bright, 1);
}