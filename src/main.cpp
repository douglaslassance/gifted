#include "ofMain.h"
#include "gifMasher.h"

int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);
	ofRunApp(new gifMasher());
}
