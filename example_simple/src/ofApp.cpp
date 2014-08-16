#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    family.loadImage("family.jpg");
    detector.setup(OFX_ACCURACY_HIGH, false,.1);
    faces = detector.detectFaceFeatures(family, false, false);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    family.draw(0, 0);
    ofSetColor(ofColor::green);
    ofSetLineWidth(3.0);
    ofNoFill();
    for (int i = 0; i < faces.size(); i++) {
        shared_ptr<ofxCIFaceFeature> &f = faces[i];
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
    ofSetColor(ofColor::white);
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
