#include "Man.hpp"
#include "Manager.hpp"

Man::Man(Manager& manager_ref, const string name) : manager(manager_ref), name(name) {
    const float p = ofRandom(-PI,PI), t = ofRandom(-PI,PI);
    position = glm::vec3(sin(p) * cos(t), sin(p) * sin(t), cos(p)) * manager.stage_radius * cbrt(ofRandom(1.0));
}

void Man::update() {
    
    // update position
//    position = glm::vec3(ofNoise(noise_seed.x, manager.getCurrentTime() * .01) * 0.5, ofNoise(noise_seed.y, manager.getCurrentTime() * 0.01) * 0.5, ofNoise(noise_seed.z, manager.getCurrentTime() * 0.01) * 0.5) * 100;
    velocity += glm::vec3(ofNoise(noise_seed.x, manager.getCurrentTime() * .01), ofNoise(noise_seed.y, manager.getCurrentTime() * 0.01), ofNoise(noise_seed.z, manager.getCurrentTime() * 0.01)) * 0.001 - glm::vec3(0.0005);
    position += velocity * (manager.getCurrentTime() - manager.getBeforeUpdatedAt()) * 10.;

    // WIP
    if (length(position) > manager.stage_radius) {
        velocity *= -1.;
    }


    if (state == State::Infected) {
        // infect other man
        for (auto& m : manager.getMen()) {
            if (m.state == State::Susceptible &&
                glm::length(position - m.position) < radius * 10 &&
                ofRandom(1) < manager.infection_rate) {
                    m.setState(State::Infected);
            }
        }
        
        // recover
        if ((manager.getCurrentTime() - state_update_at + ofRandom(-2,2)) * manager.recovery_rate > 1) {
            setState(State::Recovered);
        }
        
    } else if (state == State::Recovered) {
        if ((manager.getCurrentTime() - state_update_at + ofRandom(-2,2)) * manager.immunity_rate > 1) {
            setState(State::Susceptible);
        }
    }
}

void Man::draw() {
    ofPushMatrix();
    
    if (state == State::Infected) {
        ofSetColor(255, 0, 0);
    } else if (state == State::Recovered) {
        ofSetColor(0, 255, 0);
    } else {
        ofSetColor(0, 0, 255);
    }
    
    
    ofDrawSphere(position, radius);
    
    ofPopMatrix();
};

void Man::setState(State g_state) {
    state = g_state;
    ofGetElapsedTimef();
    state_update_at = manager.getCurrentTime();

}

const string Man::getName() {
    return name;
}
