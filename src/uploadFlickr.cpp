/*
 *  uploadFlickr.cpp
 *  ARToolkitExample
 *
 *  Created by Mar Canet Sola on 26/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "uploadFlickr.h"

//--------------------------------------------------------------
uploadFlickr::uploadFlickr()
{
	action_url = "http://api.flickr.com/services/upload/";
	api_key = "aea45f1f97c70a68b3e56beb2601d29e";
	api_sig = "68751d7ac51f388e";
	
	//http://flickr.com/services/rest/?method=flickr.auth.getToken&api_key=aea45f1f97c70a68b3e56beb2601d29e&api_sig=68751d7ac51f388e&frob=1a2b3c4d5e
	token = "";
	isAuthentificated =  false;
	ofAddListener(httpUtils.newResponseEvent,this,&uploadFlickr::newResponse);
	httpUtils.start();
	token = getAuthentification("http://flickr.com/services/rest/?method=flickr.auth.getToken&api_key="+api_key+"&api_sig="+api_sig);
}

//--------------------------------------------------------------
uploadFlickr::~uploadFlickr()
{

}

//--------------------------------------------------------------
void uploadFlickr::newResponse(ofxHttpResponse & response)
{
	responseStr = ofToString(response.status) + ": " + response.responseBody;
}

//--------------------------------------------------------------
void uploadFlickr::sendImage(string filePath, string title)
{
	if(token=="")
	{
		token = getAuthentification("http://flickr.com/services/rest/?method=flickr.auth.getToken&api_key="+api_key+"&api_sig="+api_sig);
	}
	
	/*
	[ARGUMENTS]
	photo: The file to upload.
	title (optional): The title of the photo.
	description (optional): A description of the photo. May contain some limited HTML.
	tags (optional): A space-seperated list of tags to apply to the photo.
	is_public, is_friend, is_family (optional): Set to 0 for no, 1 for yes. Specifies who can view the photo.
	safety_level (optional): Set to 1 for Safe, 2 for Moderate, or 3 for Restricted.
	content_type (optional): Set to 1 for Photo, 2 for Screenshot, or 3 for Other.
	hidden (optional): Set to 1 to keep the photo in global search results, 2 to hide from public searches.
	*/			
	ofxHttpForm form;
	form.action = action_url;
	form.method = OFX_HTTP_POST;
	form.addFormField("title", title);
	form.addFile("photo", filePath);
	httpUtils.addForm(form);
}
//--------------------------------------------------------------
string uploadFlickr::getToken()
{
	return token;
}
//--------------------------------------------------------------
string uploadFlickr::getLastResponse()
{
	return responseStr;
}
//--------------------------------------------------------------

string uploadFlickr::getAuthentification(string url)
{
	std::ostringstream ostr;
	// first step
	try{
		URI uri( url );
		std::string path(uri.getPathAndQuery());
	
		if (path.empty()) path = "/";
		
        HTTPClientSession s;
		s.setHost(uri.getHost());
		s.setPort(uri.getPort());
	
		HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		s.sendRequest(request);
	
		HTTPResponse dataResponse;
		std::istream& rs = s.receiveResponse(dataResponse);
	
		StreamCopier::copyStream(rs, ostr);
		free(rs);
		cout << url <<" get:"<< ostr.str() << endl;
		return ostr.str(); 
	}catch(Poco::Exception ex){
		cout << "error get:"<< ex.message() << endl;
		
	}
	return "";
}
//--------------------------------------------------------------
