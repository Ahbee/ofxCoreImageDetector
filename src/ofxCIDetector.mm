#include "ofxCIDetector.h"

CGColorSpaceRef ofxCIDetector::_colorSpace = nil;

CIImage* ofxCIDetector::CIImageFrom(const ofImage &img){
    ofImage srcImage = img;
    srcImage.setImageType(OF_IMAGE_COLOR_ALPHA);
    convertToARGB(srcImage);
    srcImage.mirror(true, false);
    NSUInteger length = srcImage.getPixels().size();
    NSUInteger bbp = 4;
    NSUInteger bpr = srcImage.getWidth() * 4;
    CGSize size = CGSizeMake(srcImage.getWidth(), srcImage.getHeight());
    NSData *bitmapData = [NSData dataWithBytes:srcImage.getPixels().getData() length:length];
    CIImage *dst = [CIImage imageWithBitmapData:bitmapData bytesPerRow:bpr size:size format:kCIFormatARGB8 colorSpace:_colorSpace];
    return dst;
}

void ofxCIDetector::convertToARGB(ofImage &image){
    unsigned char *data = image.getPixels().getData();
    int size = image.getWidth() * image.getHeight() * 4;
    for (int i = 0; i < size; i+=4) {
        unsigned char r = data[i];
        unsigned char g = data[i+1];
        unsigned char b = data[i+2];
        unsigned char a = data[i+3];
        data[i] = a;
        data[i+1] = r;
        data[i+2] = g;
        data[i+3] = b;
    }
}

void ofxCIDetector::setup(OFX_DETECTOR_ACCURACY accuracy, bool tracking, float minFeatureSize){
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);  
    });
    if (minFeatureSize <=0 || minFeatureSize >=1) {
        ofLogError("ofxCIDetector") << "minFeatureSize must be between 0-1.0 exclusive";
        return;
    }
    isSetup = true;
    NSString *accuracyString;
    if (accuracy == OFX_ACCURACY_LOW) {
        accuracyString = CIDetectorAccuracyLow;
    }else{
        accuracyString = CIDetectorAccuracyHigh;
    }
    _detector = [CIDetector detectorOfType:CIDetectorTypeFace context:nil options:@{CIDetectorAccuracy: accuracyString,
                                                                                        CIDetectorTracking:[NSNumber numberWithBool:tracking],
                                                                                        CIDetectorMinFeatureSize:[NSNumber numberWithFloat:minFeatureSize]}];
    [_detector retain];
}

vector<shared_ptr<ofxCIFaceFeature> > ofxCIDetector::detectFaceFeatures(const ofImage &img, bool detectSmiles, bool detectClosedEyes,OFX_IMAGE_ORIENTATION imageOrientation)const{
    if (!isSetup) {
        ofLogError("ofxCIDetector") << " cannot call detectFaceFeatures without setting up the detector";
        return vector<shared_ptr<ofxCIFaceFeature> >();
    }
    
    NSDictionary *options = @{CIDetectorSmile: [NSNumber numberWithBool:detectSmiles],
                              CIDetectorImageOrientation:[NSNumber numberWithInt:imageOrientation],
                              CIDetectorEyeBlink:[NSNumber numberWithBool:detectClosedEyes]};
    
    CIImage *image = CIImageFrom(img);
    NSArray *features = [_detector featuresInImage:image options:options];
    vector<shared_ptr<ofxCIFaceFeature> > faceFeatures;
    for (CIFaceFeature *f in features){
        if ([f.type isEqualToString:CIFeatureTypeFace]) {
            shared_ptr<ofxCIFaceFeature> faceFeature(new ofxCIFaceFeature);
            faceFeature->setup(f);
            faceFeatures.push_back(faceFeature);
        }
    }
    return faceFeatures;
}


ofxCIDetector::ofxCIDetector(){
    isSetup = false;
    _detector = nil;
}

ofxCIDetector::~ofxCIDetector(){
    [_detector release];
}






