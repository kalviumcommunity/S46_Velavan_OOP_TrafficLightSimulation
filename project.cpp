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
    
    public:
    TrafficLight(string name, string state){
        this->state = state;
        this->name = name; 
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
};

class Intersection{
    private:
    vector<TrafficLight> lights;

    public:

    void addLight(TrafficLight& light) {
        lights.push_back(light);
    }

    void displayStates(){
        for(int i = 0; i < lights.size(); i++){
            lights[i].displayState();
        }
    }
};

int main(){

    TrafficLight trafficLights[] = {
        TrafficLight("North-South", "red"),
        TrafficLight("East-West", "green")
    };

    Intersection intersection;

    for (int i = 0; i < 2; i++) {
        intersection.addLight(trafficLights[i]);
    }

    intersection.displayStates();

    return 0;
}