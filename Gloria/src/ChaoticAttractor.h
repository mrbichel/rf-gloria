//
//  ChaoticAttractor.h
//  Gloria
//
//  Created by Johan Bichel Lindegaard on 6/18/15.
//
//

#pragma once

#include "ofMain.h"
#include "ContentScene.h"
#include "mapping.h"

#include <math.h>

#define dimensions 2

struct dat {
    dat(double _x, double _y) {
        x = _x;
        y = _y;
    }
    
    double x, y;
};


class Attractor {
public:
    
    Attractor() {
        // set the seed
        
        I = 1;
        
        //dimensions = 2;
        
        seed = ofGetElapsedTimeMicros();
        ofSeedRandom(seed);
        //cout<<"Seed: "<<seed<<endl;
        
        // calculate initial random
        
        lyapunov = 0;
        
        drawIt = true;
        
        xmin= 1e32;
        xmax=-1e32;
        ymin= 1e32;
        ymax=-1e32;
        
        for (int i=0; i< 6; i++) {
            ax.push_back(ofRandom(-2, 2));
            ay.push_back(ofRandom(-2, 2));
        }
        
        
        // calculate the attractor
        // first two random values
        x = ofRandom(-0.5, 0.5);
        y = ofRandom(-0.5, 0.5);
        
        a(x,y);
        
        
        d0 = -1;
        while(d0 <= 0) {
            xe = d[0].x + ofRandom(-0.5,0.5) / 1000.0;
            ye = d[0].y + ofRandom(-0.5,0.5) / 1000.0;
            dx = d[0].x - xe;
            dy = d[0].y - ye;
            
            d0 = sqrt(dx*dx+dy*dy);
        }

        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    void iterate() {
        
        double nx = ax[0] +
        ax[1] * d[I-1].x +
        ax[2] * d[I-1].x * d[I-1].x +
        ax[3] * d[I-1].x * d[I-1].y +
        ax[4] * d[I-1].y +
        ax[5] * d[I-1].y * d[I-1].y;
        
        double ny = ay[0] +
        ay[1] * d[I-1].x +
        ay[2] * d[I-1].x * d[I-1].x +
        ay[3] * d[I-1].x * d[I-1].y +
        ay[4] * d[I-1].y +
        ay[5] * d[I-1].y * d[I-1].y;
        a(nx,ny);
        
        xenew = ax[0] +
        ax[1] * xe +
        ax[2] * xe * xe +
        ax[3] * xe * ye +
        ax[4] * ye +
        ax[5] * ye * ye;
        
        yenew = ay[0] +
        ay[1] * xe + ay[2] * xe * xe +
        ay[3] * xe * ye +
        ay[4] * ye +
        ay[5] * ye * ye;
        
        // Update the bounds
        xmin = min(xmin,d[I].x);
        ymin = min(ymin,d[I].y);
        xmax = max(xmax,d[I].x);
        ymax = max(ymax,d[I].y);
        
        
        classify();
        
        
        
        /* float xm = ofGetWidth() * (nx - xmin) / (xmax-attractor.xmin);
         float ym = ofGetHeight() * (ny - ymin) / (attractor.ymax-attractor.ymin);
         
         mesh.addVertex(ofVec2f(x,y));
         */
        
        I++;
    }
    
    
    void draw() {
        glPointSize(4);
        
        mesh.drawVertices();
    }
    
    
    void classify() {
        
        // Does the series tend to infinity
        if (xmin < -1e10 || ymin < -1e10 || xmax > 1e10 || ymax > 1e10) {
            drawIt = false;
            type = "infinite attractor";
        }
        
        // Does the series tend to a point
        dx = d[I].x - d[I-1].x;
        dy = d[I].y - d[I-1].y;
        if (abs(dx) < 1e-10 && abs(dy) < 1e-10) {
            drawIt = false;
            type = "point attractor";
        }
        
        // Calculate the lyapunov exponents
        if (I > 1000) {
            dx = d[I].x - xenew;
            dy = d[I].y - yenew;
            double dd = sqrt(dx * dx + dy * dy);
            lyapunov += log(fabs(dd / d0));
            xe = d[I].x + d0 * dx / dd;
            ye = d[I].y + d0 * dy / dd;
            
            if (drawIt) {
                if (abs(lyapunov) < 10) {
                    drawIt = false;
                    type = "neutrally stable";
                } else if(lyapunov < 0) {
                    drawIt = false;
                    type = "periodic";
                } else {
                    type = "chaotic";
                }
            }
        }
    }
    
    int I;
    
    // todo: int dimensions;
    
    double xenew, yenew;
    
    double xmin, ymin, xmax, ymax;
    int initialIterations;
    int totalIterations;
    double lyapunov;
    int seed;
    
    double xe, ye, dx, dy, d0;
    
    double x, y;
    vector<double> ax;
    vector<double> ay;
    
    bool drawIt;
    
    // add a point to our data
    void a(double x, double y) {
        d.push_back(dat(x,y));
        mesh.addVertex(ofVec2f(x,y));
        mesh.addColor(ofColor(0,0,0,255));
    }
    
    // dimensions
    // vector<dimension> d;
    vector<dat> d; // this is the data
    
    string type;
    ofMesh mesh;
};



class ChaoticAttractor : public ContentScene {
    
public:
    
    
    void setup();
    void draw();
    void debugDraw();
    void update();
    
    //ofParameter<float> frequency;
    //float lineWidth;
    //ofParameter<bool> crazySpeed;
    //ofParameter<bool> reverse;
    
    //ofParameter<ofVec2f> speed;
    //ofParameter<ofVec2f> scatter;
    //ofVec2f time;
    
    
    
    
    
    Attractor attractor;
    ofMesh mesh;
    
    ofParameter<bool> searchChaos;
    ofParameter<bool> iterate;
    
    ofParameter<bool> drawLines;
    
    // draw lines
    // search speed
    
    // show discarded
    
    // freeze
    
    // zoom
    // offset
    
    
    ofFbo fbo;
    
    
    
};