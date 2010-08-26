/*
 *  lightShader.cpp
 *  ARToolkitExample
 *
 *  Created by Mar Canet Sola on 27/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "lightShader.h"



// texture blim - ambient

//--------------------------------------------------------------
lightShader::lightShader()
{
	//load shader
	
	
	//shader.loadShader("shaders/simple");	
	shader.loadShader("shaders/simplePerpixelLight");	
	//shader.loadShader("shaders/phong");	
}

//--------------------------------------------------------------
lightShader::~lightShader()
{

}

//--------------------------------------------------------------
void lightShader::setLighting() 
{	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	
	// Light model parameters:
	// -------------------------------------------
	
	GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
	
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	
	// -------------------------------------------
	// Spotlight Attenuation
	
	GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
	GLint spot_exponent = 30;
	GLint spot_cutoff = 180;
	
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
	glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
	GLfloat Kc = 1.0;
	GLfloat Kl = 0.0;
	GLfloat Kq = 0.0;
	
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);

	//diffuse light color variables
	GLfloat dlr = 1.0;
	GLfloat dlg = 1.0;
	GLfloat dlb = 1.0;
	
	//ambient light color variables
	GLfloat alr = 0.95;
	GLfloat alg = 0.85;
	GLfloat alb = 0.0;
	
	//light position variables
	GLfloat lx = 0.0;
	GLfloat ly = -450.0;
	GLfloat lz = -200.0;
	GLfloat lw = 0.0;
	
    GLfloat DiffuseLight[] = {dlr, dlg, dlb}; //set DiffuseLight[] to the specified values
    glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight); //change the light accordingly
    
	GLfloat AmbientLight[] = {alr, alg, alb}; //set AmbientLight[] to the specified values
	glLightfv (GL_LIGHT0, GL_AMBIENT, AmbientLight); //change the light accordingly
    
    GLfloat LightPosition[] = {lx, ly, lz, lw}; //set the LightPosition to the specified values
    glLightfv (GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly
}

//--------------------------------------------------------------
void lightShader::setMaterial() 
{

	GLfloat mShininess[] = {80};
		
	GLfloat DiffuseMaterial[] = {1.0, 0.0, 0.0};
	GLfloat AmbientMaterial[] = {0.0, 0.0, 0.0};
	GLfloat SpecularMaterial[] = {1.0, 1.0, 1.0};
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
}
//--------------------------------------------------------------

void lightShader::beginRender()
{
	shader.setShaderActive(true);
	setLighting();
	setMaterial();
    shader.setUniformVariable3f("cLightPosition", LightPosition[0], LightPosition[1], LightPosition[2]);
	glActiveTexture(GL_TEXTURE0);
	
}
//--------------------------------------------------------------
void lightShader::endRender()
{
	shader.setShaderActive(false); 
	glDisable(GL_LIGHTING);
	
}


