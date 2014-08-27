#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.initGrabber(640, 480);
    smiley.loadImage("smiley.jpg");
    font.loadFont("verdana.ttf", 20);
    detector.setup(OFX_ACCURACY_HIGH, false, .2);
    ofSetFrameRate(30.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if (cam.isFrameNew()) {
        image.setFromPixels(cam.getPixelsRef());
        detectedFaces = detector.detectFaceFeatures(image, true, false);
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
        if (f->hasSmile()) {
            smiley.draw(700, 20);
        }
        ofSetColor(ofColor::yellow);
        if (f->hasLeftEyePosition()) {
            ofCircle(f->getLeftEyePosition(), 10);
        }
        if (f->hasRightEyePosition()) {
            ofCircle(f->getRightEyePosition(), 10);
        }
        if (f->hasMouthPosition()) {
            ofCircle(f->getMouthPosition(), 15);
        }
        ofSetColor(ofColor::green);
        ofRect(f->getBounds());
        
    }
    ofSetColor(0);
    font.drawString("Smile to detect smiles", 30, 600);
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
