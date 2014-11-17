#include "ofApp.h"

// MISSING
// Working on waitScreen();

//--------------------------------------------------------------
void ofApp::setup(){
    
//  SIZE SETUP
    screenW = 1200; // SCREEN SIZE
    screenH = 1920;
    
    frameW  = 1920; // VIDEO
    frameH  = 1080;
    
    gifW = 2*frameH/10; // GIF
    gifH = 2*frameW/10;
    
//  Sketch Setup
    ofBackground(0, 0, 0);
    ofSetFrameRate(30);

    
//  GIF Setup
    nFrames = 0;
    maxFrames = 5; // Total number of frames for the GIF - Limit
    currentFrame = 0;
    currentGif = 0;
    checkGif = 0;
    waitTime = 1000;

    
// Capture Setup
    
    //we can now get back a list of devices.
    devices = vid.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }
    
    selectCam = 0; // Change webcam here
    
    vid.setDeviceID(selectCam);
    vid.initGrabber(frameW,frameH);

    gifSize.allocate(gifW, gifH);

    
//    Center Video
    
    horizCenter = screenW - (screenW - vid.getHeight())/2;

    
//GIF Capture setup
    gifEncoder.setup(gifW, gifH, .25, 256);
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
    
    waitOpacity = 0;
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

    
    
    
   
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofPushMatrix();
    
    ofTranslate(0,0,0);
    
    ofRotateZ(90); // angle you want to rotate
    
    vid.draw(0, frameH-horizCenter, frameW, -frameH); // your video feed from the webcom

    ofPopMatrix();
    
    ofSetColor(255, 255, 255);
    
    displayInstructions();
    
    waitScreen();
    
    
    if (checkGif != currentGif) {
        
        // Need a better way to wait till the GIF is done saving before loading a it. Perhaps an intemediate UI screen saying "Saving Gif".
//        Current Issue, for some reason, calling     waitScreen(); does not actually display anything.
    
        
        cout << "There's a new GIF" << endl;
        previousGif.loadMovie(gifName);
        cout << "Loaded to video: " + gifName << endl;
        previousGif.play();
        
        checkGif = currentGif;
    }
    
    previousGif.update();
    
//    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);
    if(!bFullscreen){
        ofDrawBitmapString("press f to enter fullscreen", 10, 15);
        ofDrawBitmapString("window is normal", 10, 25);
    } else {
        
    }
    
}

//--------------------------------------------------------------
//  CUSTOM METHODS
//--------------------------------------------------------------


// ofxGifEncoder - Event - Gif Saved

void ofApp::onGifSaved(string &fileName) {
    
    gifEncoder.reset();
    cout << "Reset Gif" << endl;
    
}


// ofxGifEncoder -  Add new frame

void ofApp::captureFrame() {

    
    gifSize.setFromPixels(vid.getPixels(), frameW, frameH);
    gifSize.mirror(0, 1);
    
    gifSize.resize(frameW, frameW);
    gifSize.rotate(90, frameW/2, frameW/2);
    gifSize.resize(gifW, gifH);
    
    gifEncoder.addFrame(
                        
                        
                        gifSize.getPixels(),
                        gifSize.getWidth(),
                        gifSize.getHeight(),
                        gifSize.getPixelsRef().getBitsPerPixel(),
                        .1f
                        );
    
    
    nFrames++;
}



// UI - Instructions & Status

void ofApp::displayInstructions(){
    
    if (currentFrame == 0) {
        subHeadType = proximaNova12.getStringBoundingBox(gifStatusUI[0], 0, 0);
        proximaNova12.drawString(gifStatusUI[0], screenW/2 - subHeadType.width/2, screenH - subHeadType.height/2 - 40);
        
        previousGif.draw(screenW/2 - gifW/2, screenH - gifH - 80, gifW, gifH);
        
    } else {
        
        subHeadType = proximaNova12.getStringBoundingBox(gifStatusUI[1], 0, 0);
        proximaNova12.drawString(gifStatusUI[1],  screenW/2 - subHeadType.width/2, screenH - subHeadType.height/2 - 40);
        
        headType = baskervilleOldFace30.getStringBoundingBox(onScreenInst, 0, 0);
        baskervilleOldFace30.drawString(onScreenInst, screenW/2 - headType.width/2, screenH - 250);
    }
}


//--------------------------------------------------------------
void ofApp::waitScreen() {
    
    if (waitOpacity != 0) {
        for (int i = 0; i< 4; i++) {
             waitOpacity--;
        }
       
    }
    
    ofEnableAlphaBlending();
//    cout << "wait screen active" << endl;
    ofSetColor(0, 0, 0, waitOpacity);
    ofFill();
    ofRect(0, 0, screenW, screenH);
    
    ofSetColor(255, 255, 255, waitOpacity);
    subHeadType = proximaNova12.getStringBoundingBox("Saving", 0, 0);
    proximaNova12.drawString("Saving", screenW/2 - subHeadType.width/2, screenH - subHeadType.height/2 - 40);
    ofDisableAlphaBlending();
    
    if (checkGif != currentGif) {
        
        ofSleepMillis(waitTime);
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
    
    if(key == 'c'){
        
        if(selectCam < devices.size()-1){
        selectCam++;
            vid.close();
            vid.setDeviceID(selectCam); // Change webcam here
            vid.initGrabber(frameW,frameH);
        } else {
            selectCam = 0;
            vid.close();
            vid.setDeviceID(selectCam); // Change webcam here
            vid.initGrabber(frameW,frameH);
        }
        
        
       
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case ' ':
            if (currentFrame == maxFrames -1){
                
                captureFrame();
                waitOpacity = 255;
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