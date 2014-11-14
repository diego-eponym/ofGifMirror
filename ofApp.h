#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "ofxOpenCv.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

//--------------------------------------------------------------
//    Video Variables
//--------------------------------------------------------------
    
    ofVideoGrabber vid;
    
    ofxCvColorImage gifSize;
    
    int horizCenter;

    vector<ofVideoDevice> devices;
    
    int selectCam;
    
//--------------------------------------------------------------
//    GIF Variables
//--------------------------------------------------------------

//    ofxGifEncoder - Write
    
    void onGifSaved(string & fileName);
    void exit();
    void captureFrame();
    
    vector <ofTexture *> txs; // for previewing
    vector <ofxGifFrame *> pxs;
    
    int frameW, frameH;
    int nFrames;
    int maxFrames;
    int currentFrame;
    int currentGif;
    int checkGif;
    
    int gifW, gifH;
    
    string gifName;
    
       ofxGifEncoder gifEncoder;
    
//  Load GIF

    ofVideoPlayer previousGif;
    int waitTime;
    
    
//--------------------------------------------------------------
//    UI Variables
//--------------------------------------------------------------

    bool  	bFullscreen;
    int screenW;
    int screenH;
    
    void displayInstructions();
    void waitScreen();
    
    string gifStatusUI[2];
    string onScreenInst;
    
    ofTrueTypeFont baskervilleOldFace30;
    ofTrueTypeFont proximaNova12;
    
    ofRectangle subHeadType;
    ofRectangle headType;
    
    
};