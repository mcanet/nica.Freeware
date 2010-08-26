/*
 *  arToolkit.cpp
 *  ARToolkitExample
 *
 *  Created by Mar Canet Sola on 28/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "arToolkit.h"

// ----  AR TK+ STUFF - ripped from the multi marker demo app
// needs a home in a nice ofxARToolkit addon :)

#include "ARToolKitPlus/TrackerMultiMarkerImpl.h"

//--------------------------------------------------------------

class MyLogger : public ARToolKitPlus::Logger
{
    void artLog(const char* nStr)
    {
        printf(nStr);
    }
};

static    MyLogger      logger;
ARToolKitPlus::TrackerMultiMarker *tracker;

//--------------------------------------------------------------

arToolkit::arToolkit()
{
	debug = true;
	bpp = 1;
	numPixels = width*height*bpp;
	cameraBuffer = new unsigned char[numPixels];
	
	useBCH = true;
	
	convert.allocate(width, height);
	gray.allocate(width, height);
	grabber.initGrabber(width, height);
	grabber.setDeviceID(1);
	
	// ofImage
	imgGrabbed.allocate(width,height, 1);
	
	// ----------------------------------  AR TK+ STUFF - ripped from the single marker demo app
	
    // create a tracker that does:
    //  - 6x6 sized marker images
    //  - samples at a maximum of 6x6
    //  - works with luminance (gray) images
    //  - can load a maximum of 10 patterns
    //  - can detect a maximum of 10 patterns in one image
	tracker = new ARToolKitPlus::TrackerMultiMarkerImpl<6,6,6, 10, 10>(width,height);
	
	const char* description = tracker->getDescription();
	printf("ARToolKitPlus compile-time information:\n%s\n\n", description);
	
    // set a logger so we can output error messages
    tracker->setLogger(&logger);
	tracker->setPixelFormat(ARToolKitPlus::PIXEL_FORMAT_LUM);	
	
    if( !tracker->init( "logitechPro4000.dat", "markerboard_480-499.cfg", 1.0f, 1000.0f) )            // load std. ARToolKit camera file
	{
		printf("ERROR: init() failed\n");
		delete cameraBuffer;
		delete tracker;
		return;
	}
	
    // define size of the marker
    //tracker->setPatternWidth(80); // I'm not sure how to define the size with multimarkers since it doesnt seem to have this option.
	
	// the marker in the BCH test image has a thin border...
    tracker->setBorderWidth(useBCH ? 0.125f : 0.250f);
	
    // set a threshold. alternatively we could also activate automatic thresholding
    //tracker->setThreshold(20);
	tracker->activateAutoThreshold(true);
    // let's use lookup-table undistortion for high-speed
    // note: LUT only works with images up to 1024x1024
    tracker->setUndistortionMode(ARToolKitPlus::UNDIST_LUT);
	
    // RPP is more robust than ARToolKit's standard pose estimator
    tracker->setPoseEstimator(ARToolKitPlus::POSE_ESTIMATOR_RPP);
	
    // switch to simple ID based markers
    // use the tool in tools/IdPatGen to generate markers
    tracker->setMarkerMode(useBCH ? ARToolKitPlus::MARKER_ID_BCH : ARToolKitPlus::MARKER_ID_SIMPLE);
	
	// load 3d
	
	//nicaModel.loadModel("models/Squirrel.3ds", 20); 
	//nicaModel.setScale(0.5, 0.5, 0.5);
	
	nicaModel.loadModel("models/nica_v4.3ds", 20);
    nicaModel.setScale(0.5, 0.5, 0.5);
	nicePosX = 5;
	nicePosY = 8;
	nicePosZ = 44;
	
	nicaModel.setPosition(0, 0, 0);
	nicaModel.setRotation(0, -90,0 , 0, 1);
	
	finder.setup("haarXML/haarcascade_frontalface_default.xml");
}

//--------------------------------------------------------------

arToolkit::~arToolkit()
{

}

//--------------------------------------------------------------

void arToolkit::update()
{
	grabber.grabFrame();
	
	if(grabber.isFrameNew())
	{
		
		//convert our camera frame to grayscale
		convert.setFromPixels(grabber.getPixels(), width, height);
		gray = convert;
		
		//find the marker and get back the confidence
		int markerId = tracker->calc(gray.getPixels());	
		finder.findHaarObjects( gray,10, 10000, 5 );
	}
	
}
	
//--------------------------------------------------------------

void arToolkit::draw()
{
		
	bool isPeople = finder.blobs.size()>0;
		
	// camera image
	ofSetColor(0xffffff);
	grabber.draw(0, 0);
	
	
	//this is where we use the calculated matrix from ARToolkitPlus to put
	//in our graphics at the location and orientation of the marker.
	//- the matrix has the 0,0 point as the center of the marker. 
	
	int numDetected = tracker->getNumDetectedMarkers();
	//cout<<"numberofmarkers:"<<numDetected<<endl;
	
	glViewport(0, 0, 640, 480 );
	glMatrixMode( GL_PROJECTION );
	glLoadMatrixf(tracker->getProjectionMatrix());
	
	for(int i=0; i<numDetected; i++)
	{
		
		ARToolKitPlus::ARMarkerInfo marker = tracker->getDetectedMarker(i);
		
		float m34[ 3 ][ 4 ];
		float c[ 2 ] = { 0.0f, 0.0f };
		float w = 40.0f;
		
		
		tracker->rppGetTransMat( &marker, c, w, m34 );
		
		float m[ 16 ]; //this is some crazy matrix transformative stuff. I think initially it came out of one of the arToolkit functions.... but i got it from here: http://chihara.naist.jp/people/STAFF/imura/computer/OpenGL/artp/disp_content
		for ( int i = 0; i < 3; i++ ) {
			for ( int j = 0; j < 4; j++ ) {
				m[ j * 4 + i ] = m34[ i ][ j ];
			}
		}
		for ( int j = 0; j < 3; j++ ) {
			m[ j * 4 + 3 ] = 0.0f;
		}
		m[ 3 * 4 + 3 ] = 1.0f;
		
		glPushMatrix();
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( m );
		
		// Draw image (background)
		
		
		ofSetColor(255 , 255, 0 );
		//-- grabber.draw(-30,-20,60,40);
		ofRect(-30,-20,60,40);
		glPopMatrix();
		
		// Draw 3d model ()
		//mylightShader.setParams(4, (float)mouseX / 100.0);
		glEnable(GL_DEPTH_TEST);
		mylightShader.beginRender();
		
		glPushMatrix();
		ofSetColor(255 , 255, 255 );
		//-- idNumb.drawString(ofToString(marker.id), -idNumb.stringWidth(ofToString(marker.id))/2,0);
		glTranslated(nicePosX, nicePosY , nicePosZ );
		glRotatef(-90,0 , 0, 1);
		//glutSolidTeapot(10.0);
		nicaModel.draw();
		
		mylightShader.endRender();
		glDisable(GL_DEPTH_TEST);
		glPopMatrix();
	}
	
}

//--------------------------------------------------------------

void arToolkit::keyPressed(int key)
{
	if(key == 's'){ grabber.videoSettings(); }
	
	if(key == 'y'){ nicePosX+=0.5f; }
	if(key == 'h'){ nicePosX-=0.5f; }
	
	if(key == 'u'){ nicePosY+=0.5f; }
	if(key == 'j'){ nicePosY-=0.5f; }
	
	if(key == 'i'){ nicePosZ+=0.5f; }
	if(key == 'k'){ nicePosZ-=0.5f; }
}

//--------------------------------------------------------------

void arToolkit::saveImage()
{
	imgGrabbed.grabScreen(0,0,width, height);
	imgGrabbed.saveImage("userAwarded.png"); 
}

//--------------------------------------------------------------

void arToolkit::sendImageToFlickr()
{
	string path = "/Users/mcanet/Documents/OF/of_preRelease_v0061_osxSL_FAT/apps/nica/NicaDemo/bin";
	string command = "python "+path+"/data/uploadrFlickr_freeNica.py "+path+"/data/userAwarded.png 2010";
	system(command.c_str());
}