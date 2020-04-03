#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    manager.randomCreate();
    
    ofxSubscribeOsc(OF_PORT, "/cam/position", [&](ofVec3f pos) {
        cam.setPosition(pos);
        cam.lookAt(lookat);
    });

    ofxSubscribeOsc(OF_PORT, "/cam/lookat", [&](float a, float b, float c) {
        lookat = glm::vec3(a,b,c);
        cam.lookAt(lookat);
    });

    ofxSubscribeOsc(OF_PORT, "/cam/rotate", [&](const float rad, ofVec3f v) {
        cam.rotateRad(rad, v);
    });
}

//--------------------------------------------------------------
void ofApp::update(){
    manager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    manager.draw();
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        manager.activeFromName("daito");
    }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
