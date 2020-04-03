#include "Man.hpp"
#include "Manager.hpp"

Man::Man(Manager& manager_ref) : manager(manager_ref) {
    const float p = ofRandom(-PI,PI), t = ofRandom(-PI,PI);
    position = glm::vec3(sin(p) * cos(t), sin(p) * sin(t), cos(p)) * manager.stage_radius * cbrt(ofRandom(1.0));
}

void Man::update() {
    
        // update position
//        position += glm::vec3(ofNoise(noise_seed.x) * 0.5, ofNoise(noise_seed.y) * 0.5, ofNoise(noise_seed.z) * 0.5);
    position += velocity * (manager.getCurrentTime() - manager.getBeforeUpdatedAt()) * 10.;

    // WIP
    if (length(position) > manager.stage_radius) {
        velocity *= -1.;
    }


    if (state == State::Infected) {
        // infect other man
        for (auto& m : manager.getMen()) {

            if (m.state == State::Susceptible) {
            
                
                if (glm::length(position - m.position) < radius * 10 ) {
                    
                    if (ofRandom(1) < manager.infection_rate) {
                        ofLogNotice() << "Infect!";
                        m.setState(State::Infected);
                    }
                
                    
                }
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
