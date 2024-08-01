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
    TrafficLight(string name){
        this->name = name; 
        state = "red";
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
    Intersection(){
        lights.push_back(TrafficLight("North-South"));
        lights.push_back(TrafficLight("East-West"));
    }

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

    TrafficLight nsLight("North-South");
    TrafficLight ewLight("East-West");

    Intersection intersection;

    return 0;
}