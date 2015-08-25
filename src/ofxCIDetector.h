
#pragma once

#include "ofMain.h"
#include "ofxCIFaceFeature.h"

enum OFX_DETECTOR_ACCURACY {
    OFX_ACCURACY_LOW,
    OFX_ACCURACY_HIGH,
};

enum OFX_IMAGE_ORIENTATION{
    OFX_TOP_LEFT = 1,
    OFX_TOP_RIGHT,
    OFX_BOTTOM_RIGHT,
    OFX_BOTTOM_LEFT,
    OFX_LEFT_TOP,
    OFX_RIGHT_TOP,
    OFX_RIGHT,BOTTOM,
    OFX_LEFT_BOTTOM
};

class ofxCIDetector {

public:
    ofxCIDetector();
    ~ofxCIDetector();
    
    // accuracy, choose from either  OFX_ACCURACY_LOW or OFX_ACCURACY_HIGH, HIGH is more accurate, but slower
    // tracking, pass true if you want to track faces from a video feed
    // minFeatureSize, a number from 0-1 which tells the detector the minimum size that qualifies as a face
    // the number passed in represents a fraction of the minor dimension of the image.
    void setup(OFX_DETECTOR_ACCURACY accuracy,bool tracking,float minFeatureSize,bool threaded);
    
    // detects the facesFeatures of the given image
    // I dont completely understand the ImageOrientaion parameter, but has something to do with the orintation of the face you
    // are trying to detect,for example if you want detect upside down faces you set ImageOrientation to OFX_TOP_LEFT
    // the default is OFX_BOTTOM_LEFT which is what you want for most images. But if you need to detect faces at obsure angles
    // you might wanna try messing with the imageOrientation
    vector<shared_ptr<ofxCIFaceFeature> > detectFaceFeatures(const ofImage &image,bool detectSmiles,bool detectClosedEyes,OFX_IMAGE_ORIENTATION imageOrientation = OFX_BOTTOM_LEFT ) const;
    
private:
    CIDetector *_detector;
    BOOL isSetup;
    CIContext* context_;
    NSOpenGLContext *glContext_;
    CGColorSpaceRef colorSpace_;
    NSOpenGLPixelFormat *pf_;
void createContext();

private:
    static CGColorSpaceRef _colorSpace;
    static CIImage* CIImageFrom(const ofImage &img);
    static void convertToARGB(ofImage& image);
};