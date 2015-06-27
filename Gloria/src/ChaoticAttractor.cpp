//
//  ChaoticAttractor.cpp
//  Gloria
//
//  Created by Johan Bichel Lindegaard on 6/18/15.
//
//

#include "ChaoticAttractor.h"


void ChaoticAttractor::setup(){
    
    name = "Chaotic";
    oscAddress = "/cha";
    
    searchChaos = true;
    //fbo.allocate(OUTWIDTH, OUTHEIGHT);
    
    //params.add(speed.set("speed", ofVec2f(0, 0), ofVec2f(-1,-1),ofVec2f(1,1)));
    //params.add(scatter.set("scatter", ofVec2f(0, 0), ofVec2f(0,0),ofVec2f(1,1)));
    
    
    params.add(drawLines.set("drawLines", false));
    params.add(iterate.set("iterate", false));
    
}

void ChaoticAttractor::update(){
    
    if( /*!attractor.drawIt*/ attractor.I > 4000) {
        //cout<<attractor.type<<endl;
        //if(searchChaos)
        attractor = Attractor();
    }
    
    for(int i=0; i<1000; i++) {
        
        attractor.iterate();
        
        /*if (attractor.type == "chaotic") {
            i+=100;
        }*/
        
        /*if(attractor.I % 200 == 0 && attractor.I > 40000) {
         mesh.clear();
         for(int i=0; i<attractor.d.size(); i++){
         float x = ofGetWidth() * (attractor.d[i].x - attractor.xmin) / (attractor.xmax-attractor.xmin);
         float y = ofGetHeight() * (attractor.d[i].y - attractor.ymin) / (attractor.ymax-attractor.ymin);
         mesh.addVertex(ofVec2f(x,y));
         }
         
         }*/
        
        
        // if(attractor.I > 100 && attractor.drawIt) {
        
        //   if(mesh.getNumVertices() > attractor.I) {
        //     mesh.clear();
        // }
        
        /*float x = ofGetWidth() * (attractor.d[i].x - attractor.xmin) / (attractor.xmax-attractor.xmin);
         float y = ofGetHeight() * (attractor.d[i].y - attractor.ymin) / (attractor.ymax-attractor.ymin);
         */
        
        // mesh.addVertex(attractor.d[attractor.I]);
        
        //}
        
        

        
        if(attractor.type == "chaotic") {
            //searchChaos = false;
        }
    }
}

void ChaoticAttractor::draw(){;
    
    ofClear(0,0,0,0);
    
    //fbo.begin();
    ofBackground(255,255,255);
    ofSetColor(255,255,255,255);
    
    ofPushMatrix();
    ofTranslate(OUTWIDTH/2, OUTHEIGHT/2);
    ofScale(OUTWIDTH,OUTHEIGHT);
    
    if(drawLines) {
        attractor.mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    } else {
        attractor.mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    attractor.draw();
    
    ofPopMatrix();
    
    //ofDrawBitmapString(ofToString(attractor.I) + " " + attractor.type + " " + ofToString(attractor.seed), 20,20);
    //fbo.end();
    
    ofSetColor(255,255,255,255);
    //fbo.draw(0,0,OUTWIDTH,OUTHEIGHT);

 
}

