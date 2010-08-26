#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{		
	bDraw = false;
	ofBackground(127,127,127);
	idNumb.loadFont("frabk.ttf", 24);	
}

//--------------------------------------------------------------
void testApp::update()
{
	myarToolkit.update();
}

//--------------------------------------------------------------
void testApp::draw()
{

	ofSetColor(0, 0, 0 );
	ofRect(40,15,130,40);
	
	// display position NICA
	ofSetColor(255 , 0, 0 );
	ofDrawBitmapString( "NICA.FREEWARE" , 50,30);
	//ofDrawBitmapString( ofToString(nicePosX, 0)+"-"+ofToString(nicePosY, 0)+"-"+ofToString(nicePosZ, 0) , 50,50);
	//ofDrawBitmapString(  "TOKEN:"+myuploadFlickr.getToken() , 50, 70);
	myarToolkit.draw();
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	if(key == 's'){ myarToolkit.saveImage(); }
	if(key == 'r'){ myarToolkit.sendImageToFlickr(); }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	
}
