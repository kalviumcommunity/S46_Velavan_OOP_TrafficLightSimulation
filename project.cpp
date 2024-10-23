#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <utility>
using namespace std;

// Base Class: TrafficLight
class TrafficLight{
    protected:
    string name;
    string state;
    static int totalLights; 
    static string defaultState;

    public:
    TrafficLight(string name, string state = defaultState){
        this->state = state;
        this->name = name;
        totalLights++; 
    }

    ~TrafficLight() {
        totalLights--;
    }

    void changeState(){
        if(state == "red"){
            state = "green";
        }else if (state == "green"){
            state = "yellow";
        }else{
            state = "red";
        }
    }

    void displayState(){
        cout << "Traffic Light " << name << " is " << state << endl;
    }

    static int getTotalLights() {
        return totalLights;
    }

    static void setDefaultState(string state) {
        defaultState = state;
    }

    static string getDefaultState() {
        return defaultState;
    }
};

int TrafficLight::totalLights = 0;
string TrafficLight::defaultState = "red";

// Derived Class 1 : Single Inheritance from TrafficLight
class PedestrianLight : public TrafficLight {
    private:
    string walkSignal;

    public:
    PedestrianLight(string name, string state, string walkSignal)
        : TrafficLight(name, state), walkSignal(walkSignal) {}

    void displayState(){
        TrafficLight::displayState();
        cout << "Walk Signal: " << walkSignal << endl;
    }

    void changeSignal() {
        if (walkSignal == "Walk") {
            walkSignal = "Don't Walk";
        } else {
            walkSignal = "Walk";
        }
    }
};

// Derived Class 2 : Multilevel Inheritance from PedestrianLight
class SmartTrafficLight : public PedestrianLight {
    private:
    bool sensorStatus;

    public:
    SmartTrafficLight(string name, string state, string walkSignal, bool sensorStatus)
        : PedestrianLight(name, state, walkSignal), sensorStatus(sensorStatus) {}

    void displayState(){
        PedestrianLight::displayState();
        cout << "Sensor Status: " << (sensorStatus ? "Active" : "Inactive") << endl;
    }
};

class Intersection{
    private:
    vector<TrafficLight*> lights;

    public:

    ~Intersection() { 
        for (auto light : lights) {
            delete light; 
        }
        cout << "Intersection destroyed and all lights are deleted." << endl;
    }

    void addLight(TrafficLight* light) {
        lights.push_back(light);
    }

    void displayStates(){
        for(int i = 0; i < lights.size(); i++){
            lights[i]->displayState();
        }
    }
};

int main(){

    TrafficLight* nsLight = new TrafficLight("North-South", "red");
    SmartTrafficLight* smartLight = new SmartTrafficLight("Smart Light", "green", "Walk", true);
    
    Intersection* intersection = new Intersection();

    intersection->addLight(nsLight);
    intersection->addLight(smartLight);

    intersection->displayStates();

    cout << "Total Traffic Lights created: " << TrafficLight::getTotalLights() << endl;

    delete intersection;

    return 0;
}