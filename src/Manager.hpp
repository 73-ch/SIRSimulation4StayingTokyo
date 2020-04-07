#ifndef Manager_hpp
#define Manager_hpp

#include "settings.h"

class Man;

class Manager {
    vector<Man> men;
    float current_time = 0.;
    float before_updated_at = 0.;
    float time_scale = 1.0;
    
    Man& searchFromId(const string id);

public:

    float infection_rate = 1.0;
    float recovery_rate = 0.1;
    float immunity_rate = 0.04;
    const float stage_radius = 150.;
    
    

    Manager();
    
    void setup();
    void randomCreate();
    
    vector<Man>& getMen();
    float getCurrentTime() const;
    float getBeforeUpdatedAt() const;
    void activeFromId(const string id);
    
    void update();
    void draw();
};

#endif /* Manager_hpp */
