#ifndef _TEST_APP
#define _TEST_APP

//#include "ofMain.h"

//#include "uploadFlickr.h"

#include "faceDetection.h"
#include "arToolkit.h"
#include "constants.h"


class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
		


		//int width, height, ;
		
		size_t        numBytesRead;
		

		bool bDraw;
		
		ofTrueTypeFont idNumb;
	
		
		
	
		//uploadFlickr	myuploadFlickr;
		ofTexture		videoTexture;
		

		arToolkit		myarToolkit;
};

#endif
