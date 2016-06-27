//
//  Gloria
//
//  Created by Johan Bichel Lindegaard on 02/07/2013.
//
//

#pragma once

#include "ofMain.h"
#include "ContentScene.h"
#include "mapping.h"

class PerlinWaves : public ContentScene {

public:
    
    ofParameter<ofVec2f> speed {"speed", ofVec2f(0, 0), ofVec2f(-1,-1),ofVec2f(1,1)};
    
    ofParameter<ofVec2f> scatter {"scatter", ofVec2f(0, 0), ofVec2f(0,0),ofVec2f(1,1)};
    
    ofVec2f time;
    
    ofParameterGroup params {"perlinwaves",
        enabled,
        speed,
        scatter
        
    };
    
    PerlinWaves() {
        ContentScene::params = params;
        
        time.x = 0;
        time.y = 0;
    }
    
    void setup();
    void draw();
    void debugDraw();
    void update();
    
    void parseOscMessage(ofxOscMessage * m);
    

    
    //ofParameter<float> rotation;
};
