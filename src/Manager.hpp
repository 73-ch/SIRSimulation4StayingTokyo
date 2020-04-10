#ifndef Manager_hpp
#define Manager_hpp

#include "settings.h"

class Man;

class Manager {
    vector<Man> men;
    float current_time = 0.;
    float before_updated_at = 0.;
    float timeScale = 1.0;
    
    
    // Boids parameter
    float maxSpeed = 2.0;
    float maxForce = 0.03;
    float separationForce = 1.5;
    float alignmentForce = 1.0;
    float cohesionForce = 1.0;
    float noiseForce = 0.1;
    
    Man& searchFromId(const string id);

public:
    // SIR parameter
    float infection_rate = 1.0;
    float recovery_rate = 0.1;
    float immunity_rate = 0.04;
    const float stage_radius = 400.;
    
    float infectionSlowdownRate = 0.2;
    
    // Boids parameter
    const float separation_distance = 30.;
    const float alignment_distance = 80.;
    const float cohesion_distance = 100.;
    

    Manager();
    
    void setup();
    void randomCreate();
    
    vector<Man>& getMen();
    float getCurrentTime() const;
    float getBeforeUpdatedAt() const;
    float getMaxSpeed() const;
    float getMaxForce() const;
    float getSeparationForce() const;
    float getAlignmentForce() const;
    float getCohesionForce() const;
    float getNoiseForce() const;
    
    
    void activeFromId(const string id);
    
    void update();
    void draw();
};

#endif /* Manager_hpp */
