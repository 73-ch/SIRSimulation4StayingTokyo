#include "Manager.hpp"
#include "Man.hpp"

Manager::Manager() {
}

void Manager::setup() {
    
}

void Manager::randomCreate() {
    
    for (int i = 0; i < people_count; i++) {
        Man man(*this);
        men.push_back(man);
    }
    
    for (int i = 0; i < 2; i++) {
        men[int(ofRandom(men.size()))].setState(Man::State::Infected);
    }
    
    men.push_back(Man(*this, "daito"));
}

Man& Manager::searchFromName(const string name) {
    for (auto& m : men) {
        if (m.getName() == name) {
            return m;
        }
    }
    
    throw "no men";
}

vector<Man>& Manager::getMen() {
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
    current_time = ofGetElapsedTimef() * 4.0;
    
    for (auto& m : men) {
        m.update();
    }
}

void Manager::draw() {
    for (auto& m : men) {
        m.draw();
    }
}

void Manager::activeFromName(const string name) {
    try {
        searchFromName(name).setState(Man::State::Infected);
    } catch(...) {
        ofLogError() << "not found man : " + name;
    }
}
