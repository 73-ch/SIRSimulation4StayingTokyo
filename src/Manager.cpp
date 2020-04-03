#include "Manager.hpp"
#include "Man.hpp"

void Manager::setup() {
        men.clear();
    
    }

void Manager::randomCreate() {
    for (int i = 0; i < people_count; i++) {
        Man man(*this);
        
        man.setState(ofRandom(1) > 0.99 ? Man::State::Infected : Man::State::Susceptible);
    }
}

const vector<Man>& Manager::getMen() const {
    return men;
}

float Manager::getCurrentTime() const {
    return current_time;
}

float Manager::getBeforeUpdatedAt() const {
    return before_updated_at;
}

void Manager::update() {
    before_updated_at = current_time;
    current_time = ofGetElapsedTimef();
    
    for (auto& m : men) {
        m.update();
    }
}

void Manager::draw() {
    for (auto& m : men) {
        m.draw();
    }
}
