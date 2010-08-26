/*
 *  arToolkit.h
 *  ARToolkitExample
 *
 *  Created by Mar Canet Sola on 28/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _ARTOOLKIT
#define _ARTOOLKIT

#include "ofMain.h"
#include "ofxCvHaarFinder.h"
#include "ofx3DModelLoader.h"
#include "lightShader.h"
#include "ofxOpenCv.h"
#include "constants.h"

class arToolkit
{
public:	
	arToolkit();
	~arToolkit();
	void draw();
	void update();
	void keyPressed(int key);
	void saveImage();
	void sendImageToFlickr();
	
	
private:
	ofImage				imgGrabbed;
	ofx3DModelLoader	nicaModel;
	ofVideoGrabber		grabber;
	lightShader			mylightShader;
	ofxCvGrayscaleImage gray;
	ofxCvColorImage		convert;
	unsigned char		*cameraBuffer;
	int					bpp;
	size_t				numPixels;
	bool				useBCH;
	float				nicePosX;
	float				nicePosY;
	float				nicePosZ;
	bool				debug;
	ofxCvHaarFinder     finder;
};

#endif