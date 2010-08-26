/*
 *  lightShader.h
 *  ARToolkitExample
 *
 *  Created by Mar Canet Sola on 27/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _LIGHT_SHADER
#define _LIGHT_SHADER

#include "ofMain.h"
#include "ofxShader.h" 
#include "ofxFBOTexture.h"

class lightShader{
public:
	lightShader();
	~lightShader();
	void beginRender();
	void endRender();
	void setParams();
	void setLighting();
	void setMaterial();
private:	
	ofxShader shader;
};

#endif