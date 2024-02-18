#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //note: this detector needs a fairly clean background to work well
	// bLiveVideo = true;
	
	// if( bLiveVideo ){
	// 	vidGrabber.setVerbose(true);
	// 	vidGrabber.setup(640, 480);
		
	// 	colorImg.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	// }else{
	// 	vidPlayer.load("people.mp4");
	// 	vidPlayer.play();
	// 	vidPlayer.setLoopState(OF_LOOP_NORMAL);

	// 	colorImg.allocate(vidPlayer.getWidth(),vidPlayer.getHeight());
	// }
	
	int numberOfParticles = 20;
	
	// cout << vidGrabber.listDevices() << endl;
	// vidGrabber.setDeviceID(2); 
	vidGrabber.setVerbose(true);
	// vidGrabber.setup(640, 480);
	vidGrabber.setup(640*2, 480*2);

	colorImgWebCam.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());

	vidPlayer.load("IMG_0496.mov");
	// vidPlayer.load("people.mp4");

	
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL);

	colorImVideo.allocate(vidPlayer.getWidth(),vidPlayer.getHeight());
	

	//just loads the detector
	detector.setup();
	
	//we resize the image down to 320 width to get better performance
	detector.setResizeWidth(320);
	
	//this should be the minimum dimensions a person could be in the input image
	//needs to be a multiple of 8
	detector.setMinPersonSize(64, 128);


	//gui 
	gui.setup();
	gui.add(bUsingWebCam.setup("Using WebCam", true));
	gui.add(bShowEyes.setup("show eyes", true));
    gui.add(bColorDot.setup("show Color Dot", false));
	gui.add(bisRepel.setup("isRepel", false));
	gui.add(overallSpeed.setup("speed", 0.3, 0, 3));
    gui.add(noise.setup("noise", 1, 0, 3));
    gui.add(trail.setup("trail", 6, 0, 200));
    gui.add(eyeSize.setup("eye size", 35, 0, 200));
	gui.add(distanceSlider.setup("distance Slider", 3000, 0, 3000));
	gui.add(pushingPower.setup("pushingPower", 0.0015, 0, 0.002));


	//particles
	particles.assign(numberOfParticles, Particle());

    for (int i = 0; i < particles.size(); ++i) {
        particles[i].setup();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(30, 30, 30);

	bool bNewFrame = false;

	if( bUsingWebCam ){
		vidGrabber.update();
		bNewFrame = vidGrabber.isFrameNew();
		if( bNewFrame ){
			// colorImg.setFromPixels(vidGrabber.getPixels());
			colorImgWebCam.setFromPixels(vidGrabber.getPixels());
		}
	}else{
		vidPlayer.update();
		bNewFrame = vidPlayer.isFrameNew();
		if( bNewFrame ){
			// colorImg.setFromPixels(vidPlayer.getPixels());
			
			colorImVideo.setFromPixels(vidPlayer.getPixels());
		}
	}

	if (bNewFrame){
		//can be a ofCvColorImage or a ofxCvGrayscaleImage
		// cv::Mat frame = cv::cvarrToMat(colorImg.getCvImage());
		cv::Mat frame; 
		if (bUsingWebCam) {
			frame = cv::cvarrToMat(colorImgWebCam.getCvImage());
		} else {
			frame = cv::cvarrToMat(colorImVideo.getCvImage());
		}
		
		
		vector<ofVec2f> points;

		//get back the people detected as a vector of ofRectangle
		peopleRects = detector.detect(frame, points);
		// cout << points[0] << endl;


		// vector<ofVec2f> blobPts;

		// //contourFinder.nBlobs get the size of the contourFinder blobs
		// for (int i = 0; i < contourFinder.nBlobs; ++i) {
		// 	// contourFinder.blobs[i].pts.size() find the size of each blob
		// 	for (int j = 0; j < contourFinder.blobs[i].pts.size(); ++j) {
		// 		// need to scale the cam/video resolution to the size of screen by * ofGetWidth() / <sizeofCam>
		// 		blobPts.push_back(contourFinder.blobs[i].pts[j] * ofGetWidth() / webCam.getWidth() ) ;
		// 	}
		// }

		for (int i = 0; i < particles.size(); ++i) {
			particles[i].repel(points, distanceSlider, pushingPower);
			particles[i].update(overallSpeed, noise, bisRepel);
		}
	}

	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 0, 0, trail);

    ofPushMatrix();
	ofTranslate(20, 20, 0);

	ofSetColor(255, 255, 255);
	if (bUsingWebCam) {
		// colorImgWebCam.draw(0, 0);
		colorImgWebCam.draw(0, 0, ofGetWidth(), ofGetHeight());
	} else {
		colorImVideo.draw(0, 0);
	}
	
	ofNoFill();
	ofSetColor(200, 20, 240);
	for( auto & rect : peopleRects ){
		ofDrawRectangle(rect);
	}
	
	ofPopMatrix();


	if (bShowEyes) {
        ofSetColor(255, 255, 255);
        for (int i = 0; i < particles.size(); ++i) {
            particles[i].draw(eyeSize);
        }
    } else {
        // ofSetColor(255, 255, 255);
        for (int i = 0; i < particles.size(); ++i) {
            particles[i].draw(1, bColorDot);
        }
    }

	// gui
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
