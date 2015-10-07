#include "ofxCIDetector.h"

CGColorSpaceRef ofxCIDetector::_colorSpace = nil;




CIImage* ofxCIDetector::CIImageFrom(const ofImage &img){
    ofImage srcImage = img;
    srcImage.setImageType(OF_IMAGE_COLOR_ALPHA);
    convertToARGB(srcImage);
    srcImage.mirror(true, false);
    NSUInteger length = srcImage.getPixelsRef().size();
    NSUInteger bbp = 4;
    NSUInteger bpr = srcImage.getWidth() * 4;
    CGSize size = CGSizeMake(srcImage.getWidth(), srcImage.getHeight());
    NSData *bitmapData = [NSData dataWithBytes:srcImage.getPixels() length:length];
    CIImage *dst = [CIImage imageWithBitmapData:bitmapData bytesPerRow:bpr size:size format:kCIFormatARGB8 colorSpace:_colorSpace];
    return dst;
}

void ofxCIDetector::convertToARGB(ofImage &image){
    unsigned char *data = image.getPixels();
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


void ofxCIDetector::createContext(){
    const NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFAAccelerated,
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize,8,
        NSOpenGLPFAOpenGLProfile,NSOpenGLProfileVersionLegacy,
        0
    };
    colorSpace_ = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
    pf_ = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    glContext_ = [[NSOpenGLContext alloc] initWithFormat:pf_ shareContext:nil];
    CGLPixelFormatObj pfo = (CGLPixelFormatObj)[pf_ CGLPixelFormatObj];
    CGLContextObj gclco = (CGLContextObj)[glContext_ CGLContextObj];
    context_ = [CIContext contextWithCGLContext:gclco pixelFormat:pfo colorSpace:colorSpace_
                                        options:@{kCIContextUseSoftwareRenderer: [NSNumber numberWithBool:NO]}];
    if (glContext_ == nil) {
        ofLogError("ofxCI") << "could not create context for Core Image";
        exit(1);
    }
    [context_ retain];
    NSOpenGLContext* previousContext = [NSOpenGLContext currentContext];
    [glContext_ makeCurrentContext];
    glClearColor(0, 0, 0, 1.0);
    //[previousContext makeCurrentContext];
}

void ofxCIDetector::setup(OFX_DETECTOR_ACCURACY accuracy, bool tracking, float minFeatureSize,bool threaded){
    if (!threaded) {
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
        
    }else{
        if (minFeatureSize <=0 || minFeatureSize >=1) {
            ofLogError("ofxCIDetector") << "minFeatureSize must be between 0-1.0 exclusive";
            return;
        }
        createContext();
        isSetup = true;
        NSString *accuracyString;
        if (accuracy == OFX_ACCURACY_LOW) {
            accuracyString = CIDetectorAccuracyLow;
        }else{
            accuracyString = CIDetectorAccuracyHigh;
        }
        _detector = [CIDetector detectorOfType:CIDetectorTypeFace context:context_ options:@{CIDetectorAccuracy: accuracyString,
                                                                                        CIDetectorTracking:[NSNumber numberWithBool:tracking],
                                                                                        CIDetectorMinFeatureSize:[NSNumber numberWithFloat:minFeatureSize]}];
    }
   
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
            shared_ptr<ofxCIFaceFeature> faceFeature(new ofxCIFaceFeature());
            faceFeature->setup(f);
            faceFeatures.push_back(faceFeature);
        }
    }
    return faceFeatures;
}


ofxCIDetector::ofxCIDetector(){
    isSetup = false;
    _detector = nil;
    context_ = nil;
    glContext_ = nil;
    pf_ = nil;
}

ofxCIDetector::~ofxCIDetector(){
    [_detector release];
    [context_ release];
    [glContext_ release];
    [pf_ release];
    CGColorSpaceRelease(colorSpace_);
}






