varying vec3 vertex_light_position;
varying vec3 vertex_normal;
uniform sampler2D texture;

void main() 
{
	vec4 color = texture2D(texture,gl_TexCoord[0].st);
	float diffuse_value = max(dot(vertex_normal, vertex_light_position), 0.0);
	gl_FragColor = color * diffuse_value;
}

