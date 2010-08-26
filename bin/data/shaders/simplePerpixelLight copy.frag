varying vec3 vertex_light_position;
varying vec3 vertex_normal;
//uniform sampler2D texture;

void main() 
{
	vec3 L = normalize(gl_LightSource[0].position.xyz - vertex_light_position); 
	vec3 E = normalize(-vertex_light_position); // we are in Eye Coordinates, so EyePos is (0,0,0)
	vec3 R = normalize(-reflect(L,vertex_normal)); 

	//calculate Ambient Term:
	vec4 Iamb = gl_FrontLightProduct[0].ambient;

	//calculate Diffuse Term:
	vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(vertex_normal,L), 0.0);

	// calculate Specular Term:
	vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);

	// write Total Color:
	gl_FragColor = gl_FrontLightModelProduct.SceneColor + Iamb + Idiff + Ispec; 
	
	
	
}


