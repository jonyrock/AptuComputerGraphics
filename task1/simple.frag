#version 120

void main()
{
	
	mat4 myMatrix;
	vec4 myVector;
	// fill myMatrix and myVector somehow
	vec4 transformedVector = myMatrix * myVector; // Yeah, it's pretty much the same than GLM
	
	// Output color = red 
	gl_FragColor = vec4(1,1,0,1);

}