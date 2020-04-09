#ifndef Man_hpp
#define Man_hpp

#include "settings.h"

const float contact_distance = 100.;
const float radius = 1.;

class Manager;

struct Man {
    enum State {
        Susceptible,
        Infected,
        Recovered,
    };
    

private:
    Manager& manager;
    const string name;
    const string id;
    State state = State::Susceptible;
    float state_update_at = 0.;
    glm::vec3 position;
    glm::vec3 velocity = glm::vec3(ofRandom(-1,1.),ofRandom(-1,1.),ofRandom(-1,1.));
    glm::vec3 bias = glm::vec3(1.);
    
    const glm::vec3 noise_seed = glm::vec3(ofRandom(128.0),ofRandom(128.0),ofRandom(128.0));
    
    vector<string> comments;
    
    float maxSpeed = 2.0;
    float maxForce = 0.03;
    float separationForce = 1.5;
    float alignmentForce = 1.0;
    float cohesionForce = 1.0;
    
    glm::vec3 formatAcceleration(glm::vec3) const;
    void updateState();
    void updateVel();

public:
    Man(Manager& manager_ref, const string id = ofToString(ofRandom(100)), const string name = ofToString(ofRandom(100)), const string comment = "hello world");

    void update(const float delta_t);
    void draw();
    void setState(State g_state);
    const string getId();
    const string getName();
    
    void addComment(const string comment);
};

#endif /* Man_hpp */
