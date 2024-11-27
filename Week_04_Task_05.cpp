#include <iostream> 
#include <vector>
#include <string> 
#include <memory> 
#include <list> 
#include <algorithm> 

  

using namespace std; 

  

// Forward declarations 

class RenderingStrategy; 

class Observer; 

  

// Singleton Pattern 

class HMISystem { 

private: 

    static HMISystem* instance; 

    string mode; // e.g., Day, Night 

    list<Observer*> observers; 

  

    // Private constructor to prevent instantiation 

    HMISystem() : mode("Day") {} 

  

public: 

    // Static method to get the single instance of the class 

    static HMISystem* getInstance() { 

        if (instance == nullptr) { 

            instance = new HMISystem(); 

        } 

        return instance; 

    } 

  

    void setMode(const string& newMode) { 

        mode = newMode; 

        notifyObservers(); 

    } 

  

    string getMode() const { 

        return mode; 

    } 

  

    void addObserver(Observer* observer) { 

        observers.push_back(observer); 

    } 

  

    void notifyObservers(); 

}; 

  

// Initialize the static member 

HMISystem* HMISystem::instance = nullptr; 

  

// Observer Pattern 

class Observer { 

public: 

    virtual void update(const string& mode) = 0; 

}; 

  

// Strategy Pattern 

class RenderingStrategy { 

public: 

    virtual void render() const = 0; 

}; 

  

class Render2D : public RenderingStrategy { 

public: 

    void render() const override { 

        cout << "Rendering in 2D" << endl; 

    } 

}; 

  

class Render3D : public RenderingStrategy { 

public: 

    void render() const override { 

        cout << "Rendering in 3D" << endl; 

    } 

}; 

  

// Widget class inheriting from Observer and implementing Strategy pattern 

class Widget : public Observer { 

private: 

    string name; 

    unique_ptr<RenderingStrategy> strategy; 

public: 

    Widget(const string& n, unique_ptr<RenderingStrategy> strat) 

        : name(n), strategy(move(strat)) {} 

  

    void setStrategy(unique_ptr<RenderingStrategy> strat) { 

        strategy = move(strat); 

    } 

  

    void render() const { 

        cout << "Widget " << name << ": "; 

        strategy->render(); 

    } 


    void update(const string& mode) override { 

        cout << "Widget " << name << " updated to " << mode << " mode." << endl; 

    } 

}; 


void HMISystem::notifyObservers() { 

    for (auto observer : observers) { 

        observer->update(mode); 

    } 

} 


// Factory Pattern 

class Control { 

public: 

    virtual void render() const = 0; 

}; 


class Button : public Control { 

public: 

    void render() const override { 

        cout << "Rendering Button" << endl; 

    } 

}; 


class Slider : public Control { 

public: 

    void render() const override { 

        cout << "Rendering Slider" << endl; 

    } 

}; 

  
class ControlFactory { 

public: 
    enum ControlType { BUTTON, SLIDER }; 
    static unique_ptr<Control> createControl(ControlType type) { 

        if (type == BUTTON) { 

            return make_unique<Button>(); 
        } 

        else if (type == SLIDER) { 

            return make_unique<Slider>(); 

        } 
        return nullptr; 

    } 

}; 


// Main Function 

int main() { 

    // Singleton pattern 

    HMISystem* system = HMISystem::getInstance(); 

    system->setMode("Night"); 

    // Factory pattern 

    auto button = ControlFactory::createControl(ControlFactory::BUTTON); 
    auto slider = ControlFactory::createControl(ControlFactory::SLIDER); 
    button->render(); 
    slider->render(); 

    // Observer pattern 
    Widget widget1("Widget1", make_unique<Render2D>()); 
    Widget widget2("Widget2", make_unique<Render2D>()); 
    system->addObserver(&widget1); 
    system->addObserver(&widget2); 
    system->setMode("Day"); 

    // Strategy pattern 

    Widget widget3("Widget3", make_unique<Render2D>()); 

    widget3.render(); 

    widget3.setStrategy(make_unique<Render3D>()); 

    widget3.render(); 

  

    return 0; 

} 

 