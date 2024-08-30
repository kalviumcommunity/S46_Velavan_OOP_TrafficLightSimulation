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

    // Delete the intersection object, which calls its destructor, which in turn deletes all TrafficLight objects
    delete intersection;

    return 0;
}