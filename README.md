#ofxCoreImageDetector

ofxCoreImageDetector allows you to use apple's [CIDetector](https://developer.apple.com/library/ios/documentation/CoreImage/Reference/CIDetector_Ref/Reference/Reference.html#//apple_ref/occ/instm/CIDetector/featuresInImage:options:) to detect/track features of an image or video stream,inside openframeworks.

## Features

* Detects and tracks faces,eyes,mouths,smiles,closed eyes,and face angle

##How to use 

####Step 1 Change source files to objective c++

Every source file in which you include "ofxCI.h", must be marked as objective c++. To do this select the file, open the file inspector (option+command + 1) and select objective c++ as the type. Some people might say to change the extension from .cpp to .mm, but this does not always work(Better to do both). 

#### step 2 Create and setup a detector

```
ofxCIDetector detector;
```

```
detector.setup(OFX_ACCURACY_HIGH, false,.1);
```
The first parameter specifies the accuracy of detection. Choose between OFX_ACCURACY_HIGH or OFX_ACCURACY_LOW. High is more accurate but Low is faster. 

The second parameter specifies weather or not you want to track faces over multiple frames. 

The thrid specifies the minimum size that the detector will recognize as a feature.The value ranges from 0.0 through 1.0 that represents a fraction of the minor dimension of the image.



#### step 3 Create an array of shared pointers to ofxCIFaceFeature

```
    vector<shared_ptr<ofxCIFaceFeature> > detectedFaces;

```

#### step 4 DetectFeatures

Use the array created in step 5 to store the results from `ofxCIDetector::detectFaceFeatures`

```
   detectedFaces = detector.detectFaceFeatures(myImage, false, false);

```
The first paramaeter is the the image you want to examine.

The second parameter specifies whether or not you want to detect smiles.

The third parameter specifies  whether or not you want to detect closed eyes.

#### step 5 extract info from each feature 
loop through the array created in step 5 to get info for each feature detected, for example

```
for (int i = 0; i < detectedFaces.size(); i++) {
        shared_ptr<ofxCIFaceFeature> &f = detectedFaces[i];
        ofRectangle bounds  = f->getBounds;
        // do something with bounds
        if (f->hasLeftEyePosition()) {
           ofVec2f pos = f->getLeftEyePosition();
           // do something with pos
        }
        if (f->hasFaceAngle) {
           float faceAng = f->getFaceAngle();
           // do someething with faceAng
        }
}

```

For a full list of availabe info take a look at the file "ofxCIFaceFeature.h" or see [CIFaceFeautre](https://developer.apple.com/library/mac/documentation/CoreImage/Reference/CIFaceFeature/Reference/Reference.html)
