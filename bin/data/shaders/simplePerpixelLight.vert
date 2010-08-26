varying vec3 cLightPosition;
//uniform vec3 cLightPosition;
varying vec3 vertex_light_position;
varying vec3 vertex_normal;
varying vec3 lightDir;
varying vec3 eyeVec;

void main() 
{
	// Calculate the normal value for this vertex, in world coordinates (multiply by gl_NormalMatrix)
	vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
	
	// Calculate the light position for this vertex
	vertex_light_position = normalize(cLightPosition);
	
	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	
	lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);
	
	eyeVec = -vVertex;
		
	// Set the front color to the color passed through with glColor*f
	gl_FrontColor = gl_Color;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	// Set the position of the current vertex
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

