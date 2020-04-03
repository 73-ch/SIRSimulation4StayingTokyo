#ifndef Manager_hpp
#define Manager_hpp

#include <stdio.h>

#include "ofMain.h"

class Man;

class Manager {
    vector<Man> men;
    float current_time = 0.;
    float before_updated_at = 0.;
    int people_count = 1000;
    
    Man& searchFromName(const string name);

public:

    const float infection_rate = 0.8;
    const float recovery_rate = 0.05;
    const float immunity_rate = 0.025;
    const float stage_radius = 150.;

    Manager();
    
    void setup();
    void randomCreate();
    
    vector<Man>& getMen();
    float getCurrentTime() const;
    float getBeforeUpdatedAt() const;
    void activeFromName(const string name);
    
    void update();
    void draw();
};

#endif /* Manager_hpp */
