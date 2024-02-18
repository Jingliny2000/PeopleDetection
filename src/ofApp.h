#ifndef OFAPPMAIN
#define OFAPPMAIN

#include "ofMain.h"
#include <ofxOpenCv.h>
#include "peopleDetector.h"
#include <ofxGui.h>
#include <particle.h>
#include <sstream>

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
		

		ofVideoGrabber vidGrabber;
		ofVideoPlayer vidPlayer;

		ofxCvColorImage	colorImgWebCam;
		ofxCvColorImage	colorImVideo;
		

		peopleDetector detector;
		vector <ofRectangle> peopleRects;

		bool bLiveVideo = false;


		ofxPanel gui;
		ofxToggle bUsingWebCam;

		ofxToggle bShowEyes;
		ofxToggle bColorDot;
		ofxToggle bisRepel;
		ofxFloatSlider overallSpeed;
		ofxFloatSlider noise;
		ofxFloatSlider trail;
		ofxIntSlider eyeSize;
		ofxIntSlider distanceSlider;
		ofxFloatSlider pushingPower;


		// particles;
		vector<Particle> particles;
		
		

};

#endif
