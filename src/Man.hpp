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
    string name;
    State state = State::Susceptible;
    float state_update_at = 0.;
    glm::vec3 position;
    glm::vec3 velocity = glm::vec3(ofRandom(-1,1.),ofRandom(-1,1.),ofRandom(-1,1.));
    glm::vec3 bias = glm::vec3(1.);
    
    const glm::vec3 noise_seed = glm::vec3(ofRandom(128.0),ofRandom(128.0),ofRandom(128.0));

public:
    Man(Manager& manager_ref, const string name = ofToString(ofRandom(100)));

    void update();
    void draw();
    void setState(State g_state);
    const string getName();

};

#endif /* Man_hpp */
