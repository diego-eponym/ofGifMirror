#include "ofApp.h"



// THIS IS A TEST FOR GIT - this should change


//--------------------------------------------------------------
void ofApp::setup(){
    
    
    screenW = ofGetScreenWidth();
    screenH = ofGetScreenHeight();
    ofSetWindowPosition(screenW/2-300/2, screenH/2-300/2);
    
    
    ofBackground(0, 0, 0);
    ofSetFrameRate(30);

    
    nFrames = 0;
    frameW  = 1200; // Window size
    frameH  = 3*frameW/4;
    maxFrames = 5; // Total number of frames for the GIF - Limit
    currentFrame = 0;
    currentGif = 0;
    checkGif = 0;
    
    // vid.setVerbose(true);
    vid.listDevices();
    vid.setDeviceID(0);
    vid.initGrabber(frameW,frameH);
    
    gifEncoder.setup(frameW, frameH, .85, 256);
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &ofApp::onGifSaved);
    
    //    UI Setup
    
    baskervilleOldFace30.loadFont("baskerville.ttf", 70, true, true);
    baskervilleOldFace30.setLineHeight(900.0f);
    baskervilleOldFace30.setLetterSpacing(1.037);
    
    proximaNova12.loadFont("proxima.ttf", 10, true, true);
    proximaNova12.setLineHeight(20.0f);
    proximaNova12.setLetterSpacing(1.037);
    
    gifStatusUI[0] = "PRESS BUTTON TO START";
    gifStatusUI[1] = "PRESS BUTTON TO CAPTURE NEW FRAME";
    onScreenInst = ofToString(currentFrame) + "of" + ofToString(maxFrames);
    
    previousGif.loadMovie("testGif.gif");
    previousGif.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(bFullscreen){
        ofHideCursor();
    }else{
        ofShowCursor();
    }
    
    vid.update();
    onScreenInst = ofToString(currentFrame) + "/" + ofToString(maxFrames);

    if (checkGif != currentGif) {
        
        ofSleepMillis(1500);
        cout << "There's a new GIF" << endl;
        previousGif.loadMovie(gifName);
        cout << "Loaded to video: " + gifName << endl;
        previousGif.play();
        
        checkGif = currentGif;
    }
    
    previousGif.update();
    
    
    if(!bFullscreen){
        proximaNova12.drawString("press f to enter fullscreen", -140 + ofGetWidth()/2, ofGetHeight()/2);
        proximaNova12.drawString("window is normal", -100 + ofGetWidth()/2, ofGetHeight() - 10);
    } else {
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetupScreen();
    
    vid.draw(0, 0);

//    Working on Cropping the video feed through the ofPixel::crop() method, need to find an example.
//    ofPixelsRef pixelRef = vid.getPixelsRef();
    
    
    
    ofSetColor(255, 255, 255);
    
    displayInstructions();
    
}

//--------------------------------------------------------------
//  CUSTOM METHODS
//--------------------------------------------------------------


// ofxGifEncoder - Event - Gif Saved

void ofApp::onGifSaved(string &fileName) {
    
    gifEncoder.reset();
    cout << "Reset Gif" << endl;

//    previousGif.play();
    
}


// ofxGifEncoder -  Add new frame

void ofApp::captureFrame() {

    
    gifEncoder.addFrame(
                        
                        
                        vid.getPixels(),
                        vid.getWidth(),
                        vid.getHeight(),
                        vid.getPixelsRef().getBitsPerPixel(),
                        .1f
                        );
    
    
    nFrames++;
}



// UI - Instructions & Status

void ofApp::displayInstructions(){
    
    //    I'm currently figuring out how to center text accurately and only once. Perhaps do thi in the setup and define custom variables for this stuff.
    
    if (currentFrame == 0) {
        subHeadType = proximaNova12.getStringBoundingBox(gifStatusUI[0], 0, 0);
        proximaNova12.drawString(gifStatusUI[0], frameW/2 - subHeadType.width/2, frameH + 30);
        
        previousGif.draw(frameW/2-80, frameH+100, 160, 120);
        
    } else {
        
        subHeadType = proximaNova12.getStringBoundingBox(gifStatusUI[1], 0, 0);
        proximaNova12.drawString(gifStatusUI[1], frameW/2 - subHeadType.width/2, frameH + 30);
        
        headType = baskervilleOldFace30.getStringBoundingBox(onScreenInst, 0, 0);
        baskervilleOldFace30.drawString(onScreenInst, frameW/2 - headType.width/2, frameH + 250);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'f'){
        
        bFullscreen = !bFullscreen;
        
        if(!bFullscreen){
            ofSetWindowShape(frameW,frameH);
            ofSetFullscreen(false);
            // figure out how to put the window in the center:
            int screenW = ofGetScreenWidth();
            int screenH = ofGetScreenHeight();
            ofSetWindowPosition(screenW/2-frameW/2, screenH/2-frameH/2);
        } else if(bFullscreen == 1){
            ofSetFullscreen(true);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case ' ':
            if (maxFrames <= currentFrame){
                gifName = "images/CS-Gif" + ofToString(currentGif) + ".gif";
                gifEncoder.save(gifName);
                cout << "Saved: " + gifName << endl;
                
                currentFrame = 0;
                currentGif++;
                
                
                break;
            }
            captureFrame();
            currentFrame++;
            cout << "Added Frame" << endl;
            
    }
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

//--------------------------------------------------------------
void ofApp::exit(){
    gifEncoder.exit();
}