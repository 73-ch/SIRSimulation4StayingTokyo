#include "Man.hpp"
#include "Manager.hpp"

Man::Man(const Manager& manager_ref) : manager(manager_ref) {
    
}

void Man::update() {
    
        // update position
//        position += glm::vec3(ofNoise(noise_seed.x) * 0.5, ofNoise(noise_seed.y) * 0.5, ofNoise(noise_seed.z) * 0.5);
    position += velocity * (manager.getCurrentTime() - manager.getBeforeUpdatedAt());

    // WIP
    if (length(position) > 300) {
        velocity *= -1.;
    }


    if (state == State::Infected) {
        // infect other man
        for (auto& m : manager.getMen()) {
            if (state == State::Susceptible && glm::length(position - m.position) < 100. && ofRandom(1) < manager.infection_rate) {
                setState(State::Infected);
            }
        }
        
        // recover
        if ((manager.getCurrentTime() - infected_at + ofRandom(-2,2)) * manager.recovery_rate > 1) {
            setState(State::Recovered);
        }
        
    } else if (state == State::Recovered) {
        
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
    if (state == State::Infected) {
        infected_at = manager.getCurrentTime();
    }
}
