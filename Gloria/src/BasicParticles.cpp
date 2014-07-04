//
//  BasicParticles.cpp
//  Gloria
//
//  Created by vibber on 02/07/14.
//
//

#include "BasicParticles.h"

void BasicParticle::setup() {
    SetVelocity(1);
    angle = ofRandomf()*TWO_PI;
    age = 0.0;
    SetSize(20);
    fadeWithAge = 1;
}

void BasicParticle::SetVelocity(float baseVelocity) {
    vel.x = baseVelocity * ofRandomf();
    vel.y = baseVelocity * ofRandomf();
}

void BasicParticle::SetSize(float size) {
    radius = ofRandomf() * size;
}

void BasicParticle::draw() {
    int mapFactor = 20;
    ofSetColor(color,ofMap(age*fadeWithAge,0,mapFactor,255,0,true));
    
    ofFill();
    ofCircle(pos.x,pos.y,radius);
}

void BasicParticle::update() {
    angle += ofSignedNoise(pos.x, pos.y)*TWO_PI;
    vel.rotate(angle);
    oldpos = pos;
    pos += vel;
    age++;
    if (age > 10000)
        age = 0;
}

///////////////////

void BasicParticles::setup(){
    name = "BasicParticles";
    oscAddress = "/basicparticles";
    
    myfbo.allocate(OUTWIDTH/10, OUTHEIGHT/10, GL_RGBA);
    sceneFbo.allocate(OUTWIDTH, OUTHEIGHT, GL_RGBA);

    //sceneFbo.begin();
    //ofClear(0,0,0);
    //sceneFbo.end();
    
    pspeed = 5;
    psize = 20;
    pkill = 10;
    totalCount = 10000;
    fade = 5;
    pFadeWithAge = 0.03;
    
    particles.reserve(totalCount);
    iterate = 0;
}

void BasicParticles::update(){
 
    for (int i=0; i<particles.size(); i++) {
        particles[i].update();
    }
  
}

void BasicParticles::draw(){;
    float lineWidth = 5;
    
    //read syphon fbo
    myfbo.readToPixels(pixels);
    
    sceneFbo.begin();
    
    ofSetColor(255, 255, 255, 255);
    
    if (!trace) {
        ofClear(0,0,0,255);
    }

    //Draw particles
    for (int i=0; i<particles.size(); i++) {
        particles[i].draw();
    }
    
    //Create new particles
    while (particles.size()<totalCount) {
        createParticle();
    }
    
    //Give new settings to some of the particles
    for (int i=0; i<pkill; i++) {
        reassignParticle();
    }
    
    // Erase particles
    while (particles.size()>totalCount) {
       particles.pop_back();
        if (iterate >= particles.size())
            iterate = 0;
    }

    
    if (trace) {
        //Fade out the old stuff
        ofSetColor(0,0,0,fade);
        ofFill();
        ofRect(0,0,OUTWIDTH,OUTHEIGHT);
    }
    
    sceneFbo.end();
    
    //Syphon fbo
    myfbo.begin();
    ofClear(0);
    ofClearAlpha();
    ofSetColor(255, 255, 255, 255);
    syphonIn->draw(0, 0, OUTWIDTH/10,OUTHEIGHT/10);
    myfbo.end();
    
    sceneFbo.draw(0,0);
    
    //myfbo.draw(0,0);
}

void BasicParticles::setGui(){
    
    gui->addSlider("/size/x", 5, 50, &psize);
    gui->addSlider("/speed/x", 0.1, 50, &pspeed);
    gui->addSlider("/kill/x", 10, 1000, &pkill);
    gui->addSlider("/totalcount/x", 500, 40000, &totalCount);
    gui->addSlider("/fadeparticle/x", 0, 1, &pFadeWithAge);
    gui->addSlider("/fade/x", 0, 10, &fade);
    gui->addToggle("/trace/x", &trace);
}

void BasicParticles::createParticle() {
    BasicParticle p;

    updateParticleSettings(p);
    
    particles.push_back(p);
}

void BasicParticles::reassignParticle() {
    
    //Increment the particle pointer
    if (iterate >= particles.size())
        iterate = 0;
    else
        ++iterate;
    
    updateParticleSettings(particles[iterate]);
}

void BasicParticles::updateParticleSettings(BasicParticle& p) {
    //cout << "debug particle age" << p.age << endl;
    p.setup();
    p.fadeWithAge = pFadeWithAge;
    p.SetVelocity(pspeed);
    p.SetSize(psize);
    p.pos.set(OUTWIDTH * ofRandomf(), OUTHEIGHT * ofRandomf());
    
    if(pixels.getWidth() > p.pos.x/10 && pixels.getHeight() > p.pos.y/10 && p.pos.y >= 0 && p.pos.x >= 0){
        p.color = pixels.getColor(p.pos.x/10,p.pos.y/10);
    } else {
        p.color = ofColor(0);
    }
}