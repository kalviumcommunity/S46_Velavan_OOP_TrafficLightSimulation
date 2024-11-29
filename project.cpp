#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class to manage a single traffic light
class TrafficLight {
private:
    string name;
    string state;

public:
    TrafficLight(string name, string state = "red") : name(name), state(state) {}

    void changeState() {
        if (state == "red") {
            state = "green";
        } else if (state == "green") {
            state = "yellow";
        } else {
            state = "red";
        }
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
};

// Class to log traffic light states 
class TrafficLightLogger {
public:
    static void logTrafficLightState(const TrafficLight& light) {
        cout << "[LOG] Traffic Light " << light.getName() << " is currently " << light.getState() << endl;
    }
};

int main() {
    // Creating traffic lights
    TrafficLight* nsLight = new TrafficLight("North-South", "red");
    TrafficLight* ewLight = new TrafficLight("East-West", "green");

    // Creating intersection and add lights
    Intersection* intersection = new Intersection();
    intersection->addLight(nsLight);
    intersection->addLight(ewLight);

    // Display and log states
    intersection->displayStates();
    TrafficLightLogger::logTrafficLightState(*nsLight);
    TrafficLightLogger::logTrafficLightState(*ewLight);

    delete intersection;

    return 0;
}