#include "ofApp.h"
//#include "ofGlProgrammableRenderer.h"

//--------------------------------------------------------------
int main(){
    //ofSetupOpenGL(1600, 800, OF_WINDOW);
    
	ofSetupOpenGL(1400,1200, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp()); // start the app
}
