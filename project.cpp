#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <utility>
using namespace std;

class TrafficLight {
    protected:
    string name;
    string state;
    static int totalLights; 
    static string defaultState;

    public:
    TrafficLight(string name, string state = defaultState) {
        this->state = state;
        this->name = name;
        totalLights++; 
    }

    virtual ~TrafficLight() {
        totalLights--;
    }

    // Virtual function to demonstrate polymorphism
    virtual void changeState() {
        if(state == "red"){
            state = "green";
        } else if (state == "green"){
            state = "yellow";
        } else {
            state = "red";
        }
    }

    virtual void displayState() {
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

// Derived class
class SmartTrafficLight : public TrafficLight {
    public:
    SmartTrafficLight(string name, string state = defaultState) : TrafficLight(name, state) {}

    // Overriding changeState function to demonstrate polymorphism
    void changeState() override {
        if(state == "red"){
            state = "green";
        } else if (state == "green"){
            state = "red";  // Skipping yellow for "smart" light
        } 
    }

    void displayState() override {
        cout << "Smart Traffic Light " << name << " is " << state << endl;
    }
};

class Intersection {
    private:
    vector<TrafficLight*> lights;

    public:
    // Destructor
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

    void changeAllStates(){
        for(int i = 0; i < lights.size(); i++){
            lights[i]->changeState();
        }
    }
};

int main() {

    TrafficLight* nsLight = new TrafficLight("North-South", "red");
    SmartTrafficLight* smartLight = new SmartTrafficLight("Smart-East-West", "red");

    Intersection* intersection = new Intersection();

    intersection->addLight(nsLight);
    intersection->addLight(smartLight);  

    cout << "Before changing states:" << endl;
    intersection->displayStates();

    cout << "\nAfter changing states:" << endl;
    intersection->changeAllStates();  
    intersection->displayStates();

    cout << "Total Traffic Lights created: " << TrafficLight::getTotalLights() << endl;
    
    delete intersection;

    return 0;
}