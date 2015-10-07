#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.initGrabber(640, 480);
    font.loadFont("verdana.ttf", 20);
    detector.setup(OFX_ACCURACY_HIGH, true, .05,false);
    ofSetFrameRate(30.0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if (cam.isFrameNew()) {
        image.setFromPixels(cam.getPixelsRef());
        detectedFaces = detector.detectFaceFeatures(image, false, false);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetLineWidth(3.0);
    ofNoFill();
    ofSetColor(ofColor::white);
    image.draw(0, 0);
    for (int i = 0; i < detectedFaces.size(); i++) {
        shared_ptr<ofxCIFaceFeature> &f = detectedFaces[i];
        ofSetColor(ofColor::green);
        ofRect(f->getBounds());
        // for some reason the first face detected is not tracked but evrything else is.
        // this bug might be fixed in the 64 bit version
        if (f->hasTrackingID()) {
            ofSetColor(ofColor::pink);
            font.drawString(ofToString(f->getTrackingID()), f->getBounds().getCenter().x,f->getBounds().getCenter().y);
        }
        if (f->hasFaceAngle()) {
            ofLog() << f->getFaceAngle();
        }
    }
    ofSetColor(0);
    string instructions = "For some reason the first face detected is not tracked\nso first move out of screen and then back in to start tracking";
    font.drawString(instructions, 30, 600);
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
