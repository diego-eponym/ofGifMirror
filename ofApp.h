#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"


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
//    Screen Variables
//--------------------------------------------------------------
    
    bool bFullscreen;
    int screenW;
    int screenH;
    
//--------------------------------------------------------------
//    Video Capture Variables
//--------------------------------------------------------------
    
    ofVideoGrabber vid;

    
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
    
    string gifName;
    
    ofxGifEncoder gifEncoder;
    
//  Load GIF

    ofVideoPlayer previousGif;
    
    
//--------------------------------------------------------------
//    UI Variables
//--------------------------------------------------------------

    
    void displayInstructions();
    
    string gifStatusUI[2];
    string onScreenInst;
    
    ofTrueTypeFont baskervilleOldFace30;
    ofTrueTypeFont proximaNova12;
    
    ofRectangle subHeadType;
    ofRectangle headType;
    
    
};