#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Abstract base class for state-changing behavior
class StateChangeStrategy {
public:
    virtual ~StateChangeStrategy() {}
    virtual string getNextState(const string& currentState) const = 0;
};

// Default state change behavior (red -> green -> yellow -> red)
class DefaultStateChange : public StateChangeStrategy {
public:
    string getNextState(const string& currentState) const override {
        if (currentState == "red") return "yellow";
        if (currentState == "yellow") return "green";
        return "red";
    }
};

// Custom state change behavior (red -> yellow -> green -> red)
class CustomStateChange : public StateChangeStrategy {
public:
    string getNextState(const string& currentState) const override {
        if (currentState == "red") return "green";
        if (currentState == "green") return "yellow";
        return "red";
    }
};

// Class to manage a single traffic light
class TrafficLight {
protected:
    string name;
    string state;
    StateChangeStrategy* stateChanger;

public:
    TrafficLight(string name, StateChangeStrategy* strategy, string state = "red")
        : name(name), state(state), stateChanger(strategy) {}

    virtual ~TrafficLight() {
        delete stateChanger; // Free dynamically allocated strategy
    }

    virtual void changeState() {
        state = stateChanger->getNextState(state);
    }

    string getState() const {
        return state;
    }

    string getName() const {
        return name;
    }

    virtual void displayState() const {
        cout << "Traffic Light " << name << " is " << state << endl;
    }
};

// Specialized traffic light for pedestrians
class PedestrianTrafficLight : public TrafficLight {
private:
    string pedestrianSignal; // E.g., "Walk" or "Don't Walk"

public:
    PedestrianTrafficLight(string name, StateChangeStrategy* strategy, string state = "red", string pedestrianSignal = "Don't Walk")
        : TrafficLight(name, strategy, state), pedestrianSignal(pedestrianSignal) {}

    void changeState() override {
        TrafficLight::changeState(); // Change the main light state
        if (state == "red") {
            pedestrianSignal = "Walk";
        } else {
            pedestrianSignal = "Don't Walk";
        }
    }

    void displayState() const override {
        TrafficLight::displayState();
        cout << "Pedestrian Signal: " << pedestrianSignal << endl;
    }
};

// Class to manage the collection of traffic lights
class Intersection {
private:
    vector<TrafficLight*> lights;

public:
    ~Intersection() {
        for (auto light : lights) {
            delete light;
        }
    }

    void addLight(TrafficLight* light) {
        lights.push_back(light);
    }

    void displayStates() {
        for (auto light : lights) {
            light->displayState();
        }
    }

    void changeAllStates() {
        for (auto light : lights) {
            light->changeState();
        }
    }
};

// Class to log traffic light states
class TrafficLightLogger {
public:
    static void logTrafficLightState(const TrafficLight& light) {
        cout << "[LOG] Traffic Light " << light.getName() << " is currently " << light.getState() << endl;
    }
};

int main() {
    // Creating traffic lights with different state-change strategies
    TrafficLight* nsLight = new TrafficLight("North-South", new DefaultStateChange());
    TrafficLight* ewLight = new TrafficLight("East-West", new CustomStateChange());
    TrafficLight* pedestrianLight = new PedestrianTrafficLight("Pedestrian-Crossing", new DefaultStateChange());

    // Creating an intersection and adding lights
    Intersection* intersection = new Intersection();
    intersection->addLight(nsLight);
    intersection->addLight(ewLight);
    intersection->addLight(pedestrianLight);

    // Displaying initial states
    intersection->displayStates();

    // Changing states and displaying again
    intersection->changeAllStates();
    intersection->displayStates();

    // Logging states
    TrafficLightLogger::logTrafficLightState(*nsLight);
    TrafficLightLogger::logTrafficLightState(*ewLight);
    TrafficLightLogger::logTrafficLightState(*pedestrianLight);

    delete intersection;

    return 0;
}