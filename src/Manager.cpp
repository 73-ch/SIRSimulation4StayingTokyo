#include "Manager.hpp"
#include "Man.hpp"

Manager::Manager() {
    ofxSubscribeOsc(OF_PORT, "/manager/active", [&](const string id) {
        activeFromId(id);
    });
    
    ofxSubscribeOsc(OF_PORT, "/manager/incidence_rate", incidence_rate);
    ofxSubscribeOsc(OF_PORT, "/manager/infection_rate", infection_rate);
    ofxSubscribeOsc(OF_PORT, "/manager/recovery_rate", recovery_rate);
    ofxSubscribeOsc(OF_PORT, "/manager/immunity_rate", immunity_rate);
    ofxSubscribeOsc(OF_PORT, "/manager/timeScale", timeScale);
    
    ofxSubscribeOsc(OF_PORT, "/manager/reset", [&]() {
        infection_rate = 0.4;
        recovery_rate = 0.1;
        immunity_rate = 0.04;
        
        float timeScale = 1.0;
        float current_time = 0.;
        
        men.clear();
        
        randomCreate();
    });
    
    ofxSubscribeOsc(OF_PORT, "/manager/comment", [&](const string id, const string name, const string comment) {
        try {
            auto&m = searchFromId(id);
            m.addComment(comment);
            m.setState(Man::State::Infected);
        } catch(...) {
            men.push_back(Man(*this, id, name, comment));
        }
    });
    
    ofxSubscribeOsc(OF_PORT, "/man/maxSpeed", maxSpeed);
    ofxSubscribeOsc(OF_PORT, "/man/maxForce", maxForce);
    ofxSubscribeOsc(OF_PORT, "/man/separationForce", separationForce);
    ofxSubscribeOsc(OF_PORT, "/man/alignmentForce", alignmentForce);
    ofxSubscribeOsc(OF_PORT, "/man/cohesionForce", cohesionForce);
    ofxSubscribeOsc(OF_PORT, "/man/noiseForce", noiseForce);
    ofxSubscribeOsc(OF_PORT, "/manager/timeScale", timeScale);
    ofxSubscribeOsc(OF_PORT, "/manager/infectionSlowdownRate", infectionSlowdownRate);
    ofxSubscribeOsc(OF_PORT, "/manager/exposedSpan", exposedSpan);
    ofxSubscribeOsc(OF_PORT, "/manager/exposedSpanDiffMax", exposedSpanDiffMax);
}

void Manager::setup() {
    
}

void Manager::randomCreate() {
    for (int i = 0; i < 500; i++) {
        Man man(*this);
        men.push_back(man);
    }
    
    for (int i = 0; i < 2; i++) {
        men[int(ofRandom(men.size()))].setState(Man::State::Exposed);
    }
    
    men.push_back(Man(*this, "daito"));
}

Man& Manager::searchFromId(const string id) {
    for (auto& m : men) {
        if (m.getId() == id) {
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

float Manager::getIncidenceRate() const {
    return infection_rate;
}

float Manager::getInfectionRate() const {
    return infection_rate;
}

float Manager::getRecoveryRate() const {
    return recovery_rate;
}

float Manager::getImmunityRate() const {
    return immunity_rate;
}

float Manager::getExposedSpan() const {
    return exposedSpan + ofRandom(exposedSpanDiffMax);
}

float Manager::getMaxSpeed() const {
    return maxSpeed;
};
float Manager::getMaxForce() const {
    return maxForce;
};
float Manager::getSeparationForce() const {
    return separationForce;
};
float Manager::getAlignmentForce() const {
    return alignmentForce;
};
float Manager::getCohesionForce() const {
    return cohesionForce;
};
float Manager::getNoiseForce() const {
    return noiseForce;
};

void Manager::update() {
    const float elapsed_time = ofGetElapsedTimef();
    const float delta_t = elapsed_time - before_updated_at;
    
    current_time += delta_t * timeScale;
    
    for (auto& m : men) {
        m.update(delta_t * timeScale);
    }
    
    before_updated_at = elapsed_time;
}

void Manager::draw() {
    for (auto& m : men) {
        m.draw();
    }
}

void Manager::activeFromId(const string id) {
    try {
        searchFromId(id).setState(Man::State::Infected);
    } catch(...) {
        ofLogError() << "not found man : " + id;
    }
}
