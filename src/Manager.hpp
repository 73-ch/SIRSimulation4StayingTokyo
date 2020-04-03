#ifndef Manager_hpp
#define Manager_hpp

#include <stdio.h>

#include "ofMain.h"

class Man;

class Manager {
    vector<Man> men;
    float current_time = 0.;
    float before_updated_at = 0.;
    int people_count = 100;

public:

    const float infection_rate = 0.001;
    const float recovery_rate = 0.1;
//    const glm::vec3 stage_size = glm::vec3();
    
    void setup();
    
    void randomCreate();
    
    const vector<Man>& getMen() const;
    
    float getCurrentTime() const;
    
    float getBeforeUpdatedAt() const;
    
    void update();
    
    void draw();
};

#endif /* Manager_hpp */
