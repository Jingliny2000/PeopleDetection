#pragma once

#include <particle.h>

Particle::Particle()
{
}

void Particle::setup()
{
    pos.x = ofRandomWidth();
    pos.y = ofRandomHeight();

    vel.x = ofRandom(-4, 4);
    vel.y = ofRandom(-4, 4);

    force = ofVec2f(0, 0);

    uniqueVal.x = ofRandom(-1000, 1000);
    uniqueVal.y = ofRandom(-1000, 1000);
    
    size = ofRandom(3, 5);
    drag = ofRandom(0.97, 0.99);
    
    stringstream ss;
    ss << "eye" << (int)ofRandom(1,15) << ".gif";
    string fileName = ss.str();
    eye.load(fileName);

    r = (int)ofRandom(0,255);
    g = (int)ofRandom(0,255);
    b = (int)ofRandom(0,255);

}

void Particle::update()
{
    force.x = ofSignedNoise(uniqueVal.x, ofGetElapsedTimeMillis());
    force.y = ofSignedNoise(uniqueVal.y, ofGetElapsedTimeMillis());

    vel *= drag;
    
    vel += force;

    if (pos.x + vel.x > ofGetWidth()) {
        pos.x -= ofGetWidth();
    } else if (pos.x + vel.x < 0) {
        pos.x += ofGetWidth();
    }

    if (pos.y + vel.y > ofGetHeight()) {
        pos.y -= ofGetHeight();
    } else if (pos.y + vel.y < 0) {
        pos.y += ofGetHeight();
    }

    pos += vel;

}

void Particle::update(float speed, float noise, bool bisRepel)
{
    force.x = ofSignedNoise(uniqueVal.x, ofGetElapsedTimeMillis());
    force.y = ofSignedNoise(uniqueVal.y, ofGetElapsedTimeMillis());
    //using noise
    force *= noise;

    vel *= drag;
    
    // + is attraction
    // - is repel
    if (bisRepel) {
        vel -= repelForce; 
    } else {
        vel += repelForce; 
    }
    


    vel += force;

    if (pos.x + vel.x > ofGetWidth()) {
        vel.x *= -1;
        // pos.x -= ofGetWidth();
    } else if (pos.x + vel.x < 0) {
        // pos.x += ofGetWidth();
        vel.x *= -1;
    }

    if (pos.y + vel.y > ofGetHeight()) {
        // pos.y -= ofGetHeight();
        vel.y *= -1;
    } else if (pos.y + vel.y < 0) {
        // pos.y += ofGetHeight();
        vel.y *= -1;

    }
    //using speed
            pos += vel * speed;
    
}

void Particle::draw(float sizeDot, bool bColorDot)
{
    // ofSetColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
    if (bColorDot) {
        ofSetColor(r, g, b);
    }
    else {
        ofSetColor(255, 255,255);
    }
    ofDrawCircle(pos.x, pos.y, size * sizeDot);

}

void Particle::draw(float eyeSize)
{
    // ofSetColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
    // ofDrawCircle(pos.x, pos.y, size * sizeDot);
    
    eye.draw(pos.x, pos.y,  eyeSize / eye.getHeight() * eye.getWidth(),  eyeSize);

}

void Particle::repel(vector<ofVec2f> repelPt, int distance, double power)
{
    repelForce.set(0,0);

    for (int i = 0; i < repelPt.size(); ++i) {
        float dist = pos.distance(repelPt[i]);

        if (dist < distance) {
            ofVec2f newReplPt = repelPt[i] - pos;
            // repelForce += newReplPt * 0.0001;
            repelForce += newReplPt * power;

        }
    }

}
