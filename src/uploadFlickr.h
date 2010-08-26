/*
 *  uploadFlickr.h
 *  ARToolkitExample
 *
 *  Created by Mar Canet Sola on 26/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _UPLOAD_FLICKR
#define _UPLOAD_FLICKR

#include "ofxHttpUtils.h"
#include "ofMain.h"

class uploadFlickr{
public:
	uploadFlickr();
	~uploadFlickr();
	void sendImage(string filePath, string title);
	void newResponse(ofxHttpResponse & response);
	string getLastResponse();
	string getAuthentification(string url);
	string getToken();
private:
	string action_url;
	string responseStr;
	string api_key;
	string api_sig;
	string token;
	ofxHttpUtils httpUtils;
	bool isAuthentificated;
};

#endif