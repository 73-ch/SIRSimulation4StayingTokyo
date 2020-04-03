#ifndef Man_hpp
#define Man_hpp

#include "ofMain.h"

const float contact_distance = 100.;
const float radius = 10.;

class Manager;

struct Man {
    enum State {
        Susceptible,
        Infected,
        Recovered,
    };
    

private:
    const Manager& manager;
    State state;
    float infected_at = 0.;
    glm::vec3 position;
    glm::vec3 velocity = glm::vec3(ofRandom(-1,1.),ofRandom(-1,1.),ofRandom(-1,1.));
    
    const glm::vec3 noise_seed = glm::vec3(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0));

public:
    Man(const Manager& manager_ref);

    void update();
    void draw();
    void setState(State g_state);

};

#endif /* Man_hpp */
