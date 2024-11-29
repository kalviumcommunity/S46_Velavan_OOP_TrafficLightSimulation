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
class  CustomStateChange : public StateChangeStrategy {
public:
    string getNextState(const string& currentState) const override {
        if (currentState == "red") return "green";
        if (currentState == "green") return "yellow";
        return "red";
    }
};

// Class to manage a single traffic light
class TrafficLight {
private:
    string name;
    string state;
    StateChangeStrategy* stateChanger;

public:
    TrafficLight(string name, StateChangeStrategy* strategy, string state = "red")
        : name(name), state(state), stateChanger(strategy) {}

    ~TrafficLight() {
        delete stateChanger; // Free dynamically allocated strategy
    }

    void changeState() {
        state = stateChanger->getNextState(state);
    }

    string getState() const {
        return state;
    }

    string getName() const {
        return name;
    }

    void displayState() const {
        cout << "Traffic Light " << name << " is " << state << endl;
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

    // Creating an intersection and adding lights
    Intersection* intersection = new Intersection();
    intersection->addLight(nsLight);
    intersection->addLight(ewLight);

    // Displaying initial states
    intersection->displayStates();

    // Changing states and displaying again
    intersection->changeAllStates();
    intersection->displayStates();

    // Logging states
    TrafficLightLogger::logTrafficLightState(*nsLight);
    TrafficLightLogger::logTrafficLightState(*ewLight);

    delete intersection;

    return 0;
}