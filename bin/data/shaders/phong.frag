varying vec3 normal, lightDir, eyeVec;
uniform sampler2D tex;

void main (void)
{
    vec4 texel;
    texel = texture2D(tex,gl_TexCoord[0].st);
    
    vec4 final_color =  (gl_FrontLightModelProduct.sceneColor * gl_FrontMaterial.ambient) + (gl_LightSource[0].ambient * gl_FrontMaterial.ambient);

	
    //vec4 final_color =  (texel * gl_FrontMaterial.ambient) + (gl_LightSource[0].ambient * gl_FrontMaterial.ambient);
						
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

	gl_FragColor = final_color;			
	
	
/*	vec3 ct,cf;
		vec4 texel;
		float intensity,at,af;
		
		intensity = max(dot(lightDir,normalize(normal)),0.0);
		
		cf = intensity * (gl_FrontMaterial.diffuse).rgb + 
						  gl_FrontMaterial.ambient.rgb;
		
		af = gl_FrontMaterial.diffuse.a;
		
		texel = texture2D(tex,gl_TexCoord[0].st);
		ct = texel.rgb;
		at = texel.a;
		
		gl_FragColor = vec4(ct * cf, at * af);	*/

}