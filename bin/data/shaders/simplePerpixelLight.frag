varying vec3 cLightPosition;
varying vec3 vertex_light_position;
varying vec3 vertex_normal; 
varying vec3 lightDir; 
varying vec3 eyeVec;

//uniform sampler2D texture;

void main() 
{

	vec3 L = normalize(cLightPosition - vertex_light_position); 
	vec3 E = normalize(-vertex_light_position); // we are in Eye Coordinates, so EyePos is (0,0,0)
	vec3 R = normalize(-reflect(L,vertex_normal)); 

    //vec4 color = texture2D(texture,gl_TexCoord[0].st)
	//calculate Ambient Term:
	vec4 Iamb = gl_FrontLightProduct[0].ambient;

	//calculate Diffuse Term:
	float lambertTerm = max(dot(vertex_normal,L), 0.0);
	vec4 Idiff = gl_FrontLightProduct[0].diffuse * lambertTerm;

	// calculate Specular Term:
	vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),gl_FrontMaterial.shininess);

	// write Total Color:
	vec4 final_color = gl_FrontLightModelProduct.SceneColor + Iamb + Idiff + Ispec; 

	gl_FragColor = final_color;
	

}


