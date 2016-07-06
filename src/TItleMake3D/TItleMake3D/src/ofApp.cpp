#include "ofApp.h"

//--------------------------------------------------------------
// see http://www.slideshare.net/tado/media-art-ii-2013
void ofApp::setup(){
    ofSetWindowShape(1900, 1068);
    ofSetWindowPosition(20, 40);
    ofSetCircleResolution(50);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofSetSmoothLighting(true);
    
    string path = "/Users/hamaantama/Developpers/ArtWorks/of_v0.8.4_osx_release/apps/myApps/TitleMake3D/bin/data/delaunay_top_sample_30000_1.csv";
    printf("load csv start\n");
    surf = loadCsvToSurface(path, -20, 1620, -20, 1044);
    
    printf("make mesh start!\n");
    meshMain.setMode(OF_PRIMITIVE_TRIANGLES);
    meshLine.setMode(OF_PRIMITIVE_TRIANGLES);
    
    for(int i=0; i<surf.points.size(); i++){
        ofVec3f p = surf.points.at(i);
        p.z = -ofMap(surf.colors.at(i).getSaturation(),
                    0, 255, 0, 200);
        
        meshMain.addVertex(p);
        meshLine.addVertex(p);
        
        meshMain.addColor(surf.colors.at(i));
        //meshMain.addColor(ofColor(211, 53, 111));
        //meshLine.addColor(ofColor(211,53,111));
        meshLine.addColor(surf.colors.at(i));
    }
    
    for(int i=0; i<surf.triangles.size(); i++){
        vector<int> is = surf.triangles.at(i);
        int i0 = is.at(0);
        int i1 = is.at(1);
        int i2 = is.at(2);
        
        meshMain.addTriangle(i0,i1,i2);
        
        meshLine.addIndex(i0);
        meshLine.addIndex(i1);
        meshLine.addIndex(i2);
    }
    
    // settings for light
    light.enable();
    //light.setSpotlight();
    light.setPosition(ofGetWidth()*0.5, ofGetHeight(),1000.0);
    light.setAmbientColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess(64);
    hasSaved = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor centerColor = ofColor(245, 248, 250);
    ofColor edgeColor = ofColor(153,170,181);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    
    ofEnableLighting();
    light.enable();
    material.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    //ofTranslate(0,0,0);
    //meshMain.draw();
    //meshMain.drawFaces();
    meshLine.drawWireframe();
    ofPopMatrix();
    material.end();
    ofDisableLighting();
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        ofImage image;
        image.grabScreen(0,0,ofGetWidth(), ofGetHeight());
        image.saveImage("login_image.png", OF_IMAGE_QUALITY_BEST);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //light.setPosition(x,y,1000);
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
