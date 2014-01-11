#version 120

varying vec3 fragmentColor;

void main(){
    // Output color = red 
    // float bright = gl_FragCoord.z;
    float bright = 1 - (gl_FragCoord.z - 0.99) * 100;
    //if(gl_FragCoord.z < .991f)
    //    gl_FragColor = vec4(fragmentColor * 100, 1);
    //else
    //    gl_FragColor = vec4(fragmentColor / 100, 1);
    gl_FragColor = vec4(fragmentColor * bright, 1);
}