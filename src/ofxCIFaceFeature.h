#pragma once
#include "ofMain.h"
#import <QuartzCore/QuartzCore.h>

class ofxCIFaceFeature {
    
public:
    ofRectangle getBounds() const{
        return _bounds;
    }
    ofVec2f getLeftEyePosition()const{
        return _leftEyePosition;
    }
    ofVec2f getRightEyePosition()const{
        return _rightEyePosition;
    }
    
    ofVec2f getMouthPosition()const{
        return _mouthPosition;
    }
    
    // I believe this only works in the 64 bit verision
    // But you can also get the angle by looking at the  left and right eye positions
    // take the arcTan of (REye.y-LEye.y)/(REye.x-LEye.x)
    float getFaceAngle() const{
        return _faceAngle;
    }
    
    // only valid if you told detector to detect closed eyes
    // left eye is relative to viewer
    bool isLeftEyeClosed()const{
        return _leftEyeClosed;
    }
    
    // only valid told you detector to detect closed eyes
    bool isRightEyeClosed()const{
        return _rightEyeClosed;
    }
    
    bool hasFaceAngle()const{
        return _hasFaceAngle;
    }
    
    bool hasLeftEyePosition()const{
        return _hasLeftEyePosition;
    }
    
    bool hasRightEyePosition()const{
        return _hasRightEyePosition;
    }
    
    bool hasMouthPosition()const{
        return _hasMouthPosition;
    }
    
    // only valid told you detector to detect smiles
    bool hasSmile()const{
        return _hasSmile;
    }
    
    bool hasTrackingID()const{
        return _hasTrackingID;
    }
    
    bool hasTrackingFrameCount()const{
        return _hasTrackingFrameCount;
    }
    
    int getTrackingID() const{
        return _trackingID;
    }
    
    int getTrackingFrameCount() const{
        return _trackingFrameCount;
    }
    
private:
    void setup(CIFaceFeature *faceFeature){
        _bounds = ofRectangle(faceFeature.bounds.origin.x,faceFeature.bounds.origin.y,faceFeature.bounds.size.width,faceFeature.bounds.size.height);
        _leftEyePosition = ofVec2f(faceFeature.leftEyePosition.x,faceFeature.leftEyePosition.y);
        _rightEyePosition = ofVec2f(faceFeature.rightEyePosition.x,faceFeature.rightEyePosition.y);
        _mouthPosition = ofVec2f(faceFeature.mouthPosition.x,faceFeature.mouthPosition.y);
        _faceAngle = faceFeature.faceAngle;
        _leftEyeClosed = faceFeature.leftEyeClosed;
        _rightEyeClosed = faceFeature.rightEyeClosed;
        _hasFaceAngle = faceFeature.hasFaceAngle;
        _hasLeftEyePosition = faceFeature.hasLeftEyePosition;
        _hasRightEyePosition = faceFeature.hasRightEyePosition;
        _hasMouthPosition = faceFeature.hasMouthPosition;
        _hasSmile = faceFeature.hasSmile;
        _hasTrackingID = faceFeature.hasTrackingID;
        _hasTrackingFrameCount = faceFeature.hasTrackingFrameCount;
        _trackingFrameCount = faceFeature.trackingFrameCount;
        _trackingID = faceFeature.trackingID;
    }
    friend class ofxCIDetector;
    
private:
    ofRectangle _bounds;
    ofVec2f _leftEyePosition;
    ofVec2f _rightEyePosition;
    ofVec2f _mouthPosition;
    float _faceAngle;
    bool _leftEyeClosed;
    bool _rightEyeClosed;
    bool _hasFaceAngle;
    bool _hasLeftEyePosition;
    bool _hasRightEyePosition;
    bool _hasMouthPosition;
    bool _hasSmile;
    bool _hasTrackingID;
    bool _hasTrackingFrameCount;
    int _trackingID;
    int _trackingFrameCount;
};
