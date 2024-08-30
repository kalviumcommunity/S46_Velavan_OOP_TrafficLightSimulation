#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <utility>
using namespace std;

class TrafficLight{
    private:
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

class Intersection{
    private:
    vector<TrafficLight*> lights;

    public:

    // A Deconstructor
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
    TrafficLight* ewLight = new TrafficLight("East-West", "green");

    Intersection* intersection = new Intersection();

    intersection->addLight(nsLight);
    intersection->addLight(ewLight);

    intersection->displayStates();

    cout << "Total Traffic Lights created: " << TrafficLight::getTotalLights() << endl;
    
    TrafficLight::setDefaultState("green");
    cout << "Default state for new Traffic Lights set to: " << TrafficLight::getDefaultState() << endl;

    delete intersection;

    return 0;
}