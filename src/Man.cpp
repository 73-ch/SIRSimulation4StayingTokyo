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
                ofRandom(1) < manager.getInfectionRate()) {
                    m.setState(State::Exposed);
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
        if ((manager.getCurrentTime() - state_update_at + ofRandom(-2,2)) * manager.getRecoveryRate() > 1) {
            setState(State::Recovered);
        }
        
    } else if (state == State::Exposed) {
        if (manager.getCurrentTime() - state_update_at > exposedSpan && ofRandom(1) < manager.getIncidenceRate()) {
            setState(State::Infected);
        }
    } else if (state == State::Recovered) {
        if ((manager.getCurrentTime() - state_update_at + ofRandom(-2,2)) * manager.getImmunityRate() > 1) {
            setState(State::Susceptible);
        }
    }
}

glm::vec3 Man::formatAcceleration(glm::vec3 before) const {
    return limit(glm::normalize(before) * manager.getMaxSpeed() - velocity, manager.getMaxForce());
}

void Man::updateVel() {
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
    
    
    glm::vec3 acceleration = glm::length(separation_sum) > 0 ? formatAcceleration(separation_sum) * manager.getSeparationForce() : glm::vec3(0);
    acceleration += alignment_count > 0 ? formatAcceleration(alignment_sum / (float)alignment_count) * manager.getAlignmentForce() : glm::vec3(0);
    acceleration += cohesion_count > 0 ? formatAcceleration(cohesion_sum / (float)cohesion_count - position) * manager.getCohesionForce() : glm::vec3(0);
    
    acceleration += manager.getNoiseForce() * glm::vec3(ofNoise(noiseSeed.x, manager.getCurrentTime()) - 0.5, ofNoise(noiseSeed.y, manager.getCurrentTime()) - 0.5, ofNoise(noiseSeed.z, manager.getCurrentTime()) - 0.5);
    

    velocity = limit(velocity + acceleration, manager.getMaxSpeed() * (state == State::Infected ? manager.infectionSlowdownRate : 1.0));
    
    // WIP
    velocity += glm::normalize(-position) * exp((glm::length(position) - manager.stage_radius) * 0.1);
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
    } else if(state == State::Exposed) {
        ofSetColor(255, 127, 0);
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
    state_update_at = manager.getCurrentTime();
    exposedSpan = manager.getExposedSpan();
}

const string Man::getName() {
    return name;
}

const string Man::getId() {
    return id;
}


void Man::addComment(const string comment) {
    comments.push_back(comment);
}
