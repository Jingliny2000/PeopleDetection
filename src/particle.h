#ifndef PARTICLE
#define PARTICLE

#include <ofMain.h>

class Particle {

    public:
        Particle();
        void setup();
        void update();
        void update(float speed, float noise, bool bisRepel);
        void draw(float sizeDot, bool bColorDot);
        void draw(float eyeSize);

        void repel(vector<ofVec2f> repelPt, int distance, double power);

        ofVec2f pos;
        ofVec2f vel;
        ofVec2f force;
        float drag;
        
        ofVec2f uniqueVal;
        float size;

        ofVec2f repelForce;

        ofImage eye;
        
        int r;
        int g;
        int b;
};

#endif
