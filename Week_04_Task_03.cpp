#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <string> 
#include <random> 
using namespace std; 

  
// Define the Control struct 

struct Control { 

    int id; 

    string type; // "button" or "slider" 

    string state; // "visible", "invisible", "disabled" 

  

    // Default constructor 

    Control() : id(0), type(""), state("") {} 

  

    // Parameterized constructor 

    Control(int i, const string& t, const string& s) : id(i), type(t), state(s) {} 

}; 

  
// Helper function to print control details 

void printControl(const Control& control) { 

    cout << "ID: " << control.id << ", Type: " << control.type << ", State: " << control.state << endl; 

} 

  
void printControls(const vector<Control>& controls) { 

    for_each(controls.begin(), controls.end(), printControl); 

    cout << endl; 

} 


string generateRandomState() { 

    random_device rd; 

    mt19937 gen(rd()); 

    uniform_int_distribution<> dis(0, 2); 

    switch (dis(gen)) { 

    case 0: return "visible"; 

    case 1: return "invisible"; 

    case 2: return "disabled"; 

    } 

    return "visible"; // default case 

} 


int main() { 

    // Populate the Control List 

    vector<Control> controls = { 

        {1, "button", "visible"}, 

        {2, "slider", "invisible"}, 

        {3, "button", "disabled"}, 

        {4, "slider", "visible"}, 

        {5, "button", "visible"}, 

        {6, "slider", "visible"}, 

        {7, "button", "invisible"}, 

        {8, "slider", "disabled"}, 

        {9, "button", "visible"}, 

        {10, "slider", "visible"} 

    }; 


    // Manipulate Control States 

    // Step 1: Use std::copy to create a backup of the control list 

    vector<Control> backupControls(controls.size()); 

    copy(controls.begin(), controls.end(), backupControls.begin()); 

    cout << "Backup of control list:" << endl; 

    printControls(backupControls); 


    // Step 2: Use std::fill to set all states to "disabled" temporarily 

    fill(controls.begin(), controls.end(), Control(0, "", "disabled")); 

    cout << "All controls set to 'disabled':" << endl; 

    printControls(controls); 


    // Restore the original controls for further operations 

    controls = backupControls; 


    // Step 3: Use std::generate to generate random states for testing 

    generate(controls.begin(), controls.end(), []() { 

        static int id = 1; 

        return Control(id++, "slider", generateRandomState()); 

        }); 

    cout << "Controls with generated random states:" << endl; 

    printControls(controls); 


    // Apply Transformations 

    // Step 4: Use std::transform to change the state of all sliders to "invisible" 

    transform(controls.begin(), controls.end(), controls.begin(), [](Control& c) { 

        if (c.type == "slider") { 

            c.state = "invisible"; 

        } 

        return c; 

        }); 

    cout << "All sliders set to 'invisible':" << endl; 

    printControls(controls); 


    // Step 5: Use std::replace to replace "disabled" with "enabled" for testing 

    replace_if(controls.begin(), controls.end(), [](const Control& c) { return c.state == "disabled"; }, Control(0, "", "enabled")); 

    cout << "Replaced 'disabled' with 'enabled':" << endl; 

    printControls(controls); 

  
    // Step 6: Use std::remove_if to filter out invisible controls from the list 

    auto newEnd = remove_if(controls.begin(), controls.end(), [](const Control& c) { return c.state == "invisible"; }); 

    controls.erase(newEnd, controls.end()); 

    cout << "Removed 'invisible' controls:" << endl; 

    printControls(controls); 


    // Other Operations 

    // Step 7: Use std::reverse to reverse the control order 

    reverse(controls.begin(), controls.end()); 

    cout << "Reversed control order:" << endl; 

    printControls(controls); 

    // Step 8: Use std::partition to group visible controls together 

    partition(controls.begin(), controls.end(), [](const Control& c) { return c.state == "visible"; }); 

    cout << "Partitioned controls to group 'visible' together:" << endl; 

    printControls(controls); 

  

    return 0; 

} 

 