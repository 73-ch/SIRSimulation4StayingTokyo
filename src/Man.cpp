#include "Man.hpp"
#include "Manager.hpp"

glm::vec3 limit(glm::vec3 target, float limit) {
    return glm::length(target) > limit ? glm::normalize(target) * limit : target;
}

Man::Man(Manager& manager_ref, const string id, const string name, const string comment) : manager(manager_ref), id(id) {
    const float p = ofRandom(-PI,PI), t = ofRandom(-PI,PI);
    position = glm::vec3(sin(p) * cos(t), sin(p) * sin(t), cos(p)) * manager.stage_radius * cbrt(ofRandom(1.0));
    comments.push_back(comment);
}

void Man::updateState() {
    if (state == State::Infected) {
        // infect other man
    
        for (auto& m : manager.getMen()) {
            const float dist = glm::length(position - m.position);
        
            if (m.state == State::Susceptible &&
                dist < radius * 10 &&
                ofRandom(1) < manager.infection_rate) {
                    m.setState(State::Infected);
            }
            
            // fordebug
//            if (m.state == State::Susceptible) {
//                ofLogNotice() << "hello";
//                if (glm::length(position - m.position) < radius * 10) {
//                    if (ofRandom(1) < manager.infection_rate) {
//                        m.setState(State::Infected);
//                    }
//                }
//            }
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

glm::vec3 Man::formatAcceleration(glm::vec3 before) const {
    return limit(glm::normalize(before) * maxSpeed - velocity, maxForce);
}

void Man::updateVel() {
    // update position
//    position = glm::vec3(ofNoise(noise_seed.x, manager.getCurrentTime() * .01) * 0.5, ofNoise(noise_seed.y, manager.getCurrentTime() * 0.01) * 0.5, ofNoise(noise_seed.z, manager.getCurrentTime() * 0.01) * 0.5) * 100;
//    velocity += glm::vec3(ofNoise(noise_seed.x, manager.getCurrentTime() * .01), ofNoise(noise_seed.y, manager.getCurrentTime() * 0.01), ofNoise(noise_seed.z, manager.getCurrentTime() * 0.01)) * 0.001 - glm::vec3(0.0005);
    int alignment_count, cohesion_count;
    glm::vec3 separation_sum, alignment_sum, cohesion_sum;
    
    
    // Boids
    for (auto& m : manager.getMen()) {
        const float dist = glm::length(position - m.position);
        const float angle = glm::acos(glm::dot(position, m.position - position) / (glm::length(position) * glm::length(m.position - position)));
        if (dist < manager.separation_distance) {
            separation_sum += glm::normalize(position - m.position) / dist;
        }
        if (dist < manager.alignment_distance) {
            alignment_sum += m.velocity;
            alignment_count++;
        }
        if (dist < manager.cohesion_distance) {
            cohesion_sum += m.position;
            cohesion_count++;
        }
    }
    
    glm::vec3 acceleration = glm::length(separation_sum) > 0 ? formatAcceleration(separation_sum) * separationForce : glm::vec3(0);
    acceleration += alignment_count > 0 ? formatAcceleration(alignment_sum / (float)alignment_count) * alignmentForce : glm::vec3(0);
    acceleration += cohesion_count > 0 ? formatAcceleration(cohesion_sum / (float)cohesion_count - position) * cohesionForce : glm::vec3(0);

    velocity = limit(velocity + acceleration, maxSpeed);
    
    // WIP
    velocity += glm::normalize(-position) * exp(glm::length(position) - manager.stage_radius);
}

void Man::update(const float delta_t) {
    updateVel();
    
    position += velocity * delta_t * 10.;
    
    updateState();
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

const string Man::getId() {
    return id;
}


void Man::addComment(const string comment) {

    comments.push_back(comment);
    ofLogNotice() << comments.size();
}
