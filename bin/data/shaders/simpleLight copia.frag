varying vec3 vertex_light_position;
varying vec3 vertex_normal;
uniform sampler2D texture;

void main() 
{
	//vec4 color = texture2D(texture,gl_TexCoord[0].st);
	// Set the diffuse value (darkness). This is done with a dot product between the normal and the light
	// and the maths behind it is explained in the maths section of the site.
	//float diffuse_value = max(dot(vertex_normal, vertex_light_position), 0.0);
	// Set the output color of our current pixel
	gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}

