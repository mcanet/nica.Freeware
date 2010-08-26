uniform sampler2D ShadowMap;
varying vec3 normal, lightDir, eyeVec;
varying vec4 ShadowCoord;
uniform sampler2D tex;

vec4 ShadowCoordPostW;

float chebyshevUpperBound( float distance)
{
	
	vec2 moments = texture2D(ShadowMap,ShadowCoordPostW.xy).rb;
	
	// Surface is fully lit. as the current fragment is before the light occluder
	if (distance <= moments.x)
		return 1.0 ;

	// The fragment is either in shadow or penumbra. We now use chebyshev's upperBound to check
	// How likely this pixel is to be lit (p_max)
	float variance = moments.y - (moments.x*moments.x);
	variance = max(variance,0.00002);

	float d = distance - moments.x;
	float p_max = variance / (variance + d*d);

	return p_max;
}


void main()
{	

// Added by Ben to get multitex support
	
	vec4 texel;
    texel = texture2D(tex,gl_TexCoord[0].st);

    vec4 final_color =  (texel * gl_FrontMaterial.ambient) ;
							
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	
	float lambertTerm = dot(N,L);
	
	if(lambertTerm > 0.0)
	{
		final_color += gl_LightSource[0].diffuse * 
		               gl_FrontMaterial.diffuse * 
					   lambertTerm;	
		
		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow( max(dot(R, E), 0.0), 
		                 gl_FrontMaterial.shininess );
		final_color += gl_LightSource[0].specular * 
		               gl_FrontMaterial.specular * 
					   specular;	
	}


	ShadowCoordPostW = ShadowCoord / ShadowCoord.w;
	float shadow = chebyshevUpperBound(ShadowCoordPostW.z);
	gl_FragColor = (vec4(shadow ) * (final_color) ) ;
  
  
//	gl_FragColor = final_color;
}
